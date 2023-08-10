#include <iostream>
#include <vector>
#include <stdio.h>
#include <sys/time.h>
#include <thread>
#include <queue>
#include <vector>
#define _BASETSD_H

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "detect.h"
#include "ThreadPool.hpp"

extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}
using namespace std;
using namespace cv;

unsigned long get_time(void)
{
	struct timeval ts;
	gettimeofday(&ts, NULL);
	return (ts.tv_sec * 1000 + ts.tv_usec / 1000);
}
static unsigned long lastTime;
 
int main() {
    const char* out_url = "rtmp://192.168.1.11/live/test";
    char *model_name = "/userdata/rk3588_Multithreading_yolov5/model/tarmac4.rknn";
    char *image_name = "/dev/video20";
 
    // 输出的数据结构
    AVFrame* yuv = NULL;
    Mat frame;
 
    //使用opencv 打开usb 摄像头
    VideoCapture cap;
    if (strlen(image_name) == 1)
    {
        cap.open((int)(image_name[0] - '0'));
        // 设置相机的FourCC码为MJPG
        int fourcc = VideoWriter::fourcc('M', 'J', 'P', 'G');
        cap.set(CAP_PROP_FOURCC, fourcc);
        cap.set(CAP_PROP_FPS, 30);
        cap.set(CAP_PROP_FRAME_WIDTH, 1920); // 设置相机分辨率为1920x1080
        cap.set(CAP_PROP_FRAME_HEIGHT, 1080);

    }  
    else
    {
        cap.open(image_name);
        // 设置相机的FourCC码为MJPG
        int fourcc = VideoWriter::fourcc('M', 'J', 'P', 'G');
        cap.set(CAP_PROP_FOURCC, fourcc);
        cap.set(CAP_PROP_FPS, 30);
        cap.set(CAP_PROP_FRAME_WIDTH, 1280); // 设置相机分辨率为1920x1080
        cap.set(CAP_PROP_FRAME_HEIGHT, 720);
    }

    // 设置线程数
    int n = 3, frames = 0;
    printf("线程数:\t%d\n", n);
    // 类似于多个rk模型的集合?
    vector<rknn_yolov5 *> rkpool;
    // 线程池
    dpool::ThreadPool pool(n);
    // 线程队列
    queue<std::future<int>> futs;

    //初始化
    for (int i = 0; i < n; i++)
    {
        rknn_yolov5 *ptr = new rknn_yolov5(model_name, i % 3);
        rkpool.push_back(ptr);
        cap >> ptr->ori_img;
        futs.push(pool.submit(&rknn_yolov5::interf, &(*ptr)));
    }

 
    int width = cap.get(CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CAP_PROP_FRAME_HEIGHT);
    int fps = cap.get(CAP_PROP_FPS);

    cout << "width:" << width << endl;
    cout << "height:" << height << endl;
    cout << "fps:" << fps << endl;
 
    // 初始化格式转换上下文
    SwsContext* sws_context = NULL;
    sws_context = sws_getCachedContext(sws_context,
        width,
        height,
        AV_PIX_FMT_BGR24,    // 源格式
        width,
        height,
        AV_PIX_FMT_YUV420P,  // 目标格式
        SWS_BICUBIC,    // 尺寸变化使用算法
        0, 0, 0);
 
    if (NULL == sws_context) {
        cout << "sws_getCachedContext error" << endl;
        return -1;
    }
 
    //初始化输出的数据结构
    yuv = av_frame_alloc();
    yuv->format = AV_PIX_FMT_YUV420P;
    yuv->width = width;
    yuv->height = height;
    yuv->pts = 0;
 
    // 分配yuv空间
    int ret_code = av_frame_get_buffer(yuv, 32);
    if (0 != ret_code) {
        cout << "  yuv init fail" << endl;
        return -1;
    }
 
    // 初始化编码上下文
    // const AVCodec* codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    const AVCodec* codec = avcodec_find_encoder_by_name("libx264");
    if (NULL == codec) {
        cout << "Can't find h264 encoder." << endl;
        return -1;
    }
 
    // 创建编码器上下文
    AVCodecContext* codec_context = avcodec_alloc_context3(codec);
    if (NULL == codec_context) {
        cout << "avcodec_alloc_context3 failed." << endl;
        return -1;
    }
 
    codec_context->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    codec_context->codec_id = codec->id;
    codec_context->thread_count = 8;
 
    codec_context->bit_rate = 4000 * 1024 ;
    codec_context->width = width;
    codec_context->height = height;
    codec_context->time_base = { 1, 15 };
    codec_context->framerate = { 15, 1 };
 
    codec_context->gop_size = 50;
    codec_context->max_b_frames = 0;
    codec_context->pix_fmt = AV_PIX_FMT_YUV420P;
    codec_context->qmin = 10;
    codec_context->qmax = 51;
 
    AVDictionary* codec_options = nullptr;
    av_dict_set(&codec_options, "profile", "baseline", 0);
    av_dict_set(&codec_options, "preset", "superfast", 0);
    av_dict_set(&codec_options, "tune", "zerolatency", 0);
 
    // 4打开编码器上下文
    ret_code = avcodec_open2(codec_context, codec, &codec_options);
    if (0 != ret_code) {
 
        return -1;
    }
    cout << "avcodec_open2 success!" << endl;
 
    AVFormatContext* format_context = nullptr;
    ret_code = avformat_alloc_output_context2(&format_context, 0, "flv", out_url);
    if (0 != ret_code) {
 
        return -1;
    }
 
    // 5.2添加视频流
    AVStream* vs = avformat_new_stream(format_context, NULL);
    if (NULL == vs) {
        cout << "avformat_new_stream failed." << endl;
        return -1;
    }
 
    vs->codecpar->codec_tag = 0;
    // 从编码器复制参数
    avcodec_parameters_from_context(vs->codecpar, codec_context);
    av_dump_format(format_context, 0, out_url, 1);
 
    // 打开rtmp 的网络输出IO
    ret_code = avio_open(&format_context->pb, out_url, AVIO_FLAG_WRITE);
    if (0 != ret_code) {
        cout << "avio_open failed." << endl;
        return -1;
    }
 
    // 写入封装头
    ret_code = avformat_write_header(format_context, NULL);
    if (0 != ret_code) {
        cout << "avformat_write_header failed." << endl;
        return -1;
    }
 
    AVPacket pack = {0};
    //memset(&pack, 0, sizeof(pack));
    int vpts = 0;
    uint8_t* in_data[AV_NUM_DATA_POINTERS] = { 0 };
 
    int in_size[AV_NUM_DATA_POINTERS] = { 0 };

    while (cap.isOpened())
    {
        if (futs.front().get() != 0)
            break;
        futs.pop();

        cv::imshow("Camera FPS", rkpool[frames % n]->ori_img);
        if (cv::waitKey(1) == 'q') // 延时1毫秒,按q键退出
        break;
        if(!cap.read(rkpool[frames % n]->ori_img))
        break;
        futs.push(pool.submit(&rknn_yolov5::interf, &(*rkpool[frames++ % n])));

        if (rkpool[frames % n]->ori_img.empty()) break;
        // cv::imshow("Camera", rkpool[frames % n]->ori_img);
        // char key = cv::waitKey(1);  // 等待按键，30毫秒
        // if (key == 27)  // 按下Esc键退出循环
        //     break;

        unsigned long currentTimestamp = get_time();
        double FPS = 1000/(currentTimestamp - lastTime);
        lastTime = currentTimestamp;

        std::cout << "Frames per second: " << FPS << std::endl;

        // rgb to yuv
        in_data[0] = rkpool[frames % n]->ori_img.data;
        in_size[0] = rkpool[frames % n]->ori_img.cols * rkpool[frames % n]->ori_img.elemSize();

        int h = sws_scale(sws_context,
            in_data, 
            in_size,
            0, 
            rkpool[frames % n]->ori_img.rows,
            yuv->data,
            yuv->linesize);
        if (h <= 0) { continue; }
 
        //av_packet_unref(&pack);
        // h264编码
        yuv->pts = vpts;
        vpts++;
       
        ret_code = avcodec_send_frame(codec_context, yuv);
        if (0 != ret_code) { continue; }
 
        ret_code = avcodec_receive_packet(codec_context, &pack);
 
        if (0 != ret_code ||pack.size<=0) {//
            cout << "avcodec_receive_packet." << endl;
            continue;
        }
 
        // 推流
        pack.pts = av_rescale_q(pack.pts, codec_context->time_base, vs->time_base);
        pack.dts = av_rescale_q(pack.dts, codec_context->time_base, vs->time_base);
        pack.duration = av_rescale_q(pack.duration,
            codec_context->time_base,
            vs->time_base);
        ret_code = av_interleaved_write_frame(format_context, &pack);
        if (0 != ret_code)
        {
            cout << "pack is error" << endl;
        }
       
        // rkpool[frames % n]->ori_img.release();
    }
    
    av_dict_free(&codec_options);
    avcodec_free_context(&codec_context);
    av_frame_free(&yuv);
    avio_close(format_context->pb);
    avformat_free_context(format_context);
    sws_freeContext(sws_context);


    // 释放剩下的资源
    while (!futs.empty())
    {
        if (futs.front().get())
        break;
        futs.pop();
    }
    for (int i = 0; i < n; i++)
        delete rkpool[i];
    cap.release();

    destroyAllWindows();
    return 0;
}











