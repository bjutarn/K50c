#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include<geometry_msgs/Point.h>
#include<geometry_msgs/Vector3.h>
#include<mavros_msgs/PositionTarget.h>
#include<geometry_msgs/PoseStamped.h>
#include"ros/ros.h"
#include "std_msgs/String.h"
#include <pthread.h>
#include<sensor_msgs/BatteryState.h>
#define N 12
unsigned char buff[N] = {0};

int sockfd;
 //创建服务器网络信息结构体
 struct sockaddr_in server_addr;
 //定义一个结构体，保存客户端的信息
struct sockaddr_in client_addr;

socklen_t clientaddrlen;

mavros_msgs::PositionTarget pose;
geometry_msgs::PoseStamped get_local_pose;


#define ERRLOG(errmsg) do{\
                perror(errmsg);\
                printf("%s--%s(%d)\n", __FILE__, __func__, __LINE__);\
                exit(-1);\
            }while(0)

//ros获取当前的位置信息

void pose_callback(const geometry_msgs::PoseStamped::ConstPtr &get_pose)
{	
get_local_pose=*get_pose;
/*ROS_INFO("position.x=%f\n",get_pose->pose.position.x);
ROS_INFO("position.y=%f\n",get_pose->pose.position.y);
ROS_INFO("position.z=%f\n",get_pose->pose.position.z);*/
}

void *task(void *arg)
{
      pose.coordinate_frame=1;
    //这是线程体
    //接收数据，如果想要给对方回应，就必须保存对方的网络信息结构体
        //如果不回应，后两个参数写 NULL 也行
    while(1)
	{
	memset(buff,0,N);
        if(-1 == recvfrom(sockfd, buff, N, 0, (struct sockaddr *)&client_addr, &clientaddrlen)){
            ERRLOG("recvfrom error");
        }
      else{
            printf("%s(%d):\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        //组装应答信息
      // strcat(buff, "--hqyj");
        if(-1 == sendto(sockfd, buff, N, 0, (struct sockaddr *)&client_addr, clientaddrlen))
            ERRLOG("sendto error");
        
	if(!((buff[0]==0XAA)&&(buff[1]==0XAA)))
	{
		printf("buff[0] frame error  please input:AA AA \n");
              //  goto again;

	}else if(!((buff[10]==0x55)&&(buff[11]==0x55)))
    	{
		printf("error buff[8]\n");
    	}

    printf("farme and end farme check success\n");
    
    float angle=buff[6]; //yaw
    float x=buff[7];   //x
    float y=buff[8]; //y
    float z=buff[9];    //z
    
         printf("buff[5]=%#x, *Angle=%f\n",buff[5],angle);

	if(buff[2]==0x1)//判断是否向上飞
	{
	pose.position.z=get_local_pose.pose.position.z+z; //向上飞几米
	printf("向上飞几米=%f\n",pose.position.z);
	}else if(buff[2]==0x2)//向下飞几米
	{   				
	 	pose.position.z=get_local_pose.pose.position.z-z;
		printf("向下飞几米=%f\n",pose.position.z);
	 	if(pose.position.z<1)
		{
		  pose.position.z=get_local_pose.pose.position.z; //小于一米 保持高度不动
		}
		
	}else{
		pose.position.z=get_local_pose.pose.position.z;  //保持当前高度不动
		}
	
	if(buff[3]==0x3)//判断是否向前飞
	{
		pose.position.x=get_local_pose.pose.position.x+x; //向前飞几米
		printf("向前飞几米=%f\n",pose.position.x);
	}else if(buff[3]==0x04)//向后飞几米
	{   		
		printf("向后飞几米=%f\n",pose.position.x);		
		pose.position.x=get_local_pose.pose.position.x-x;	 	
	}else{
		pose.position.x=get_local_pose.pose.position.x;// 保持当前前后位置不变
	
	}
	
//在左右问题上ros采用的是ENU坐标系 此时飞机正方向在左侧。但是mavros会将enu坐标系转换为ned坐标系。但是我们键入的时候还是应以enu键入
	if(buff[4]==0x05)//判断是否向左飞
	{
	 	pose.position.y=get_local_pose.pose.position.y+y; //向左飞几米
	 	printf("向左飞几米=%f\n",pose.position.y);
	}else if(buff[4]==0x06)//向右飞
	{   		
	 	printf("向右飞几米=%f\n",pose.position.y);		
	 	pose.position.y=get_local_pose.pose.position.y-y;	 	
	}else{
		pose.position.y=get_local_pose.pose.position.y;
		}
	
	
	if(buff[5]==0xCC){ //基于机头向左转
		pose.yaw=angle/57.295779;
		
	}else if(buff[5]==0xDD)// 基于机头向右转
	{ 
		pose.yaw=-angle/57.295779;
	}
     }
    }

}




int main(int argc, char *argv[]){
    /*if(3 != argc){
        printf("Usage : %s <ip> <port>\n", argv[0]);
        exit(-1);
    }*/
    //1.创建用户数据报式套接字
      sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(-1 == sockfd){
        ERRLOG("socket error");
    }

    //创建服务器网络信息结构体
    memset(&server_addr, 0, sizeof(server_addr));
  
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6789);
    server_addr.sin_addr.s_addr = inet_addr("192.168.64.141");
    socklen_t addrlen = sizeof(server_addr);


    //3.将套接字和网络信息结构体进行绑定
    if(-1 == bind(sockfd, (struct sockaddr *)&server_addr, addrlen)){
        ERRLOG("bind error");
    }
  memset(&server_addr, 0, sizeof(client_addr));    //清空
  clientaddrlen = sizeof(client_addr);

  
 //ros


//2.初始化ROS节点 定义节点名称
    ros::init(argc, argv, "talker" );
    //3.创建节点句柄
    ros::NodeHandle nh;
    //4.创建发布者对象
    ros::Publisher pub = nh.advertise<mavros_msgs::PositionTarget>("chatter",2);
    ros::Subscriber get_pose = nh.subscribe<geometry_msgs::PoseStamped>
            ("mavros/local_position/pose", 10, pose_callback);

	//电池状态
    ros::Subscriber battery_from_fcu=nh.subscribe<sensor_msgs::BatteryState>("/mavros/battery",10,);		
    //5.编写发布者逻辑并发布数据
    //创建被发布的消息

    
  
    //编写循环，循环发布数据
    //again:
    pthread_t tid;
    //注意:这里的tid不能用于接受返回值，因为返回值不是线程号
    //成功返回0，失败返回非零
    //tid只能通过形参来接收
    //if((tid = pthread_create(&tid,NULL,task,NULL))!=0){
    if((pthread_create(&tid,NULL,task,NULL))!=0){
        fprintf(stderr,"pthread create error\n");
        exit(EXIT_FAILURE);
    }
    pthread_detach(tid);

    ros::Rate rate(10.0);
    while (ros::ok())
    {
	ros::spinOnce();
        rate.sleep();
   

 
    pub.publish(pose);

    }

    //关闭套接字
    close(sockfd);
    return 0;
}
