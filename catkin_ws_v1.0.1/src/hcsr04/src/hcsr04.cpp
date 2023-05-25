#if 1
#include <iostream>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <thread>
#include <ros/ros.h>
#include<mutex>
#include</home/orangepi/catkin_ws/devel/include/hcsr04/distance.h>
#define MAX_EVENTS 10
#define BUFFER_SIZE 3

int down_fd;
int front_fd;
char wr=0xa0;	
int thread2=0;
int thread1=0;
hcsr04::distance dist;
hcsr04::distance dist1;
std::mutex mu;

bool g_quit = false;

void sigint_handler(int sig)
{

    (void)sig; // 防止编译器警告
    g_quit = true;
}
//串口通用初始化函数
int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;//定义结构体newtio和oldtio
	//将原串口的数据取到oldtio
	if  ( tcgetattr( fd,&oldtio)  !=  0) { 
		perror("SetupSerial 1");
		return -1;
	}
	//将newio清零和设置c_cflag
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD;//使能接收和忽略控制线
	newtio.c_cflag &= ~CSIZE;
	//设置数据位
	switch( nBits )
	{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
	}
	//设置校验位
	switch( nEvent )
	{
		//偶校验
		case 'O':
			newtio.c_cflag |= PARENB;//使能奇偶校验
			newtio.c_cflag |= PARODD;//偶校验
			newtio.c_iflag |= (INPCK | ISTRIP);//输入校验并忽略第八位
			break;
		case 'E': 
			newtio.c_iflag |= (INPCK | ISTRIP);
			newtio.c_cflag |= PARENB;
			newtio.c_cflag &= ~PARODD;//取消偶校验（置零偶校验位），开启奇校验
			break;
		case 'N':  
			newtio.c_cflag &= ~PARENB;//不进行奇偶校验
			break;
	}
	//设置波特率
	switch( nSpeed )
	{
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
			break;
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
			break;
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
			break;
		case 460800:
			cfsetispeed(&newtio, B460800);
			cfsetospeed(&newtio, B460800);
			break;
		default:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
	}
	//设置停止位
	if( nStop == 1 )
		newtio.c_cflag &=  ~CSTOPB;//一位停止位
	else if ( nStop == 2 )
		newtio.c_cflag |=  CSTOPB;//两位停止位

	newtio.c_cc[VTIME]  = 0;//不设置读取超时
	newtio.c_cc[VMIN] = 0;//读取最小字符数为0

	tcflush(fd,TCIFLUSH);//清空缓冲区
	
	//使配置生效
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
	//	printf("set done!\n\r");
	return 0;
}

void task1(ros::NodeHandle &NH)
{
	
	
	
	ros::Publisher  pub_distance = NH.advertise<hcsr04::distance>("distance",2);
    int b = 0;
    float c = 0;
    int m = 0;
    int nByte = 0;
    unsigned char buffer[BUFFER_SIZE]={0};
	unsigned char hc_buffer[BUFFER_SIZE]={0};
    while (true)
    {
	
        if ((b = write(front_fd, &wr, sizeof(wr))) < 0)
        {
            printf("hcsr.cpp error%s %d", __FILE__, __LINE__);
        }
        usleep(80000);
		memset(hc_buffer, 0, BUFFER_SIZE);
       
        if ((nByte = read(front_fd, buffer, 3))==3){

			hc_buffer[0]=buffer[0];
			hc_buffer[1]=buffer[1];
			hc_buffer[2]=buffer[2];
			memset(buffer, 0, BUFFER_SIZE);
		}
	tcflush(front_fd,TCIFLUSH);
		{
			std::lock_guard<std::mutex> lock(mu);
            m = ((unsigned int)hc_buffer[0]) << 16;
            b = ((unsigned int)hc_buffer[1]) << 8;
            c = (m + b + (float)hc_buffer[2]) / 1000000;
            dist.front = c;   // 前向距离
            dist.front_time = ros::Time::now();
			printf("前向距离=%f\n", dist.front);
			pub_distance.publish(dist);
			// thread2=0;
        }
		if(thread1 == 1)
			break;
    }
}

void task2( ros::NodeHandle & NH)
{
    int b = 0;
    float c = 0;
    int m = 0;
    int nByte = 0;
    unsigned char buffer[BUFFER_SIZE]={0};
	unsigned char hc_buffer[BUFFER_SIZE]={0};
	ros::Publisher  pub_distance = NH.advertise<hcsr04::distance>("distance",2);
    while (true)
    {	
      
        if ((b = write(down_fd, &wr, sizeof(wr))) < 0)
        {
            printf("hcsr.cpp error%s %d", __FILE__, __LINE__);
        }
        usleep(80000);
		
		memset(hc_buffer, 0, BUFFER_SIZE);
        if ((nByte = read(down_fd, buffer, 3))==3)
        {
			hc_buffer[0]=buffer[0];
			hc_buffer[1]=buffer[1];
			hc_buffer[2]=buffer[2];
			memset(buffer, 0, BUFFER_SIZE);
		}
			{  std::lock_guard<std::mutex> lock(mu); 
			// 	while(thread2!=0)
			// {	
			//             }
			// thread2=1;
            m = ((unsigned int)hc_buffer[0]) << 16;
            b = ((unsigned int)hc_buffer[1]) << 8;
            c = (m + b + (float)hc_buffer[2]) / 1000000;
            dist1.down = c;    // 下向距离
            dist1.down_time = ros::Time::now();
			printf("下向距离=%f\n", dist1.down);
            // fprintf(file_fd,"下向距离=%f\n", dist.down);
			// fflush(file_fd);
		    pub_distance.publish(dist1);
			// thread2=0;
        }
		tcflush(down_fd,TCIFLUSH);
		if(thread2 == 1)
			break;
    }
}

int main(int argc, char **argv){
    FILE* file_fd;
	int b=0;
    ros::init(argc, argv,"distance_node");
    ros::NodeHandle nh;
    ros::Publisher  pub_distance = nh.advertise<hcsr04::distance>("distance",2);
    ros::Rate rate(15.0);
    front_fd = open("/dev/ttyS1", O_RDWR | O_NOCTTY|O_NONBLOCK,0664);
    down_fd  = open("/dev/ttyS3", O_RDWR | O_NOCTTY|O_NONBLOCK,0664);
    file_fd= fopen("/home/orangepi/hello.txt","w+");
	
	set_opt(front_fd,9600,8,'N',1);
	set_opt(down_fd,9600,8,'N',1);
	signal(SIGINT, sigint_handler);
	std::thread mythread1(task1,std::ref(nh));
    std::thread mythread2(task2,std::ref(nh));

	while (ros::ok() && !g_quit) 
	{
    	ros::spinOnce();
    }

	thread1=1;
	thread2=1;
    mythread1.join();
	mythread2.join();
    close(front_fd);
    close(down_fd);
    return 0;
}

#else 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
int set_opt(int,int,int,char,int);




int main()
{	int fd2;
	int fd,nByte,byte;
	char bufferR[3];
	char buffer[3];
	char wr=0xa0;	
	memset(bufferR, 0, 3);
	memset(buffer, 0, 3);
	fd2 = open("/dev/ttyS1", O_RDWR | O_NOCTTY);
	if((fd=open("/dev/ttyS3",O_RDWR | O_NOCTTY | O_NONBLOCK,0664))<0)
	{
		perror("error :fail open filename\n");
	}
	else{
		printf("success\n");
		set_opt(fd, 9600, 8, 'N', 1); 
		set_opt(fd2, 9600, 8, 'N', 1); 
}
int s;
float  m=0;
float  p=0;
float  n=0;
float  a=0;
float  b=0;
float  c=0;
while(1){
            s=0;
	    if((s=write(fd,&wr,1))<0)
               {
                perror(" error\n");
               }
	
        usleep(80000);
		memset(bufferR,0, 3);
		memset(buffer,0, 3);
	         // printf("hello\n");
		if((nByte = read(fd, bufferR, 3)) == 3){      //MCU串口发送接收都是单字节(单字符)函数
                m=((unsigned int)bufferR[0])<<16;
                p=((unsigned int)bufferR[1])<<8;
                n=(m+p+(float)bufferR[2])/1000000;
			    printf("下方距离%f\n",n);				                                   //串口发送单字节（单字符）  buffer[0] = dat
				nByte = 0;
			  }
}
	close(fd);
	close(fd2);
}
//串口通用初始化函数
int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;//定义结构体newtio和oldtio
	//将原串口的数据取到oldtio
	if  ( tcgetattr( fd,&oldtio)  !=  0) { 
		perror("SetupSerial 1");
		return -1;
	}
	//将newio清零和设置c_cflag
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD;//使能接收和忽略控制线
	newtio.c_cflag &= ~CSIZE;
	//设置数据位
	switch( nBits )
	{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
	}
	//设置校验位
	switch( nEvent )
	{
		//偶校验
		case 'O':
			newtio.c_cflag |= PARENB;//使能奇偶校验
			newtio.c_cflag |= PARODD;//偶校验
			newtio.c_iflag |= (INPCK | ISTRIP);//输入校验并忽略第八位
			break;
		case 'E': 
			newtio.c_iflag |= (INPCK | ISTRIP);
			newtio.c_cflag |= PARENB;
			newtio.c_cflag &= ~PARODD;//取消偶校验（置零偶校验位），开启奇校验
			break;
		case 'N':  
			newtio.c_cflag &= ~PARENB;//不进行奇偶校验
			break;
	}
	//设置波特率
	switch( nSpeed )
	{
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
			break;
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
			break;
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
			break;
		case 460800:
			cfsetispeed(&newtio, B460800);
			cfsetospeed(&newtio, B460800);
			break;
		default:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
	}
	//设置停止位
	if( nStop == 1 )
		newtio.c_cflag &=  ~CSTOPB;//一位停止位
	else if ( nStop == 2 )
		newtio.c_cflag |=  CSTOPB;//两位停止位

	newtio.c_cc[VTIME]  = 0;//不设置读取超时
	newtio.c_cc[VMIN] = 0;//读取最小字符数为0

	tcflush(fd,TCIFLUSH);//清空缓冲区
	
	//使配置生效
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
	//	printf("set done!\n\r");
	return 0;
}



#endif