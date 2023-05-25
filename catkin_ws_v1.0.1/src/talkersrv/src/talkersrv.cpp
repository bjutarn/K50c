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
#include <math.h>
#include<geometry_msgs/Point.h>
#include<geometry_msgs/Vector3.h>
#include<mavros_msgs/PositionTarget.h>
#include<geometry_msgs/PoseStamped.h>
#include"ros/ros.h"
#include "std_msgs/String.h"
#include <pthread.h>
#include <rosbag/bag.h>
#include <mavros_msgs/State.h>
#define N 14

#include </home//orangepi/catkin_ws/src/offboard_node/include/offboard_node/offboard_control.h>
#include </home//orangepi/catkin_ws/devel/include/talkersrv/contrl.h>


int flag_num=0;

double radius = 10.0;   // 圆形轨迹半径
double height = 2.0;   // 飞行高度
double speed = 2.0;    // 飞行速度

// 圆形轨迹参数
double cx = 0.0;       // 圆心x坐标
double cy = 0.0;       // 圆心y坐标
double cz = height;    // 圆心z坐标
double theta = 0.0;    // 当前角度
double dtheta = 0.01;  // 每次增加的角度值



unsigned char buff[N] = {0};
int sockfd;
 //创建服务器网络信息结构体
struct sockaddr_in server_addr;
 //定义一个结构体，保存客户端的信息
struct sockaddr_in client_addr;
socklen_t clientaddrlen;

talkersrv::contrl pose;   //发送的目标信息

geometry_msgs::PoseStamped get_local_pose;  //获取到的本地信息

#define ERRLOG(errmsg) do{\
                perror(errmsg);\
                printf("%s--%s(%d)\n", __FILE__, __func__, __LINE__);\
                exit(-1);\
                }while(0)
//获取当前的位置信息
void pose_callback(const geometry_msgs::PoseStamped::ConstPtr &get_pose)
{	
 get_local_pose=*get_pose;
}
void *task(void *arg)
{
  while(1)
	{
        pose.pose.coordinate_frame=1;
	      memset(buff,0,N);
        if(-1 == recvfrom(sockfd, buff, N, 0, (struct sockaddr *)&client_addr, &clientaddrlen)){
            ERRLOG("recvfrom error");
        }
      else
            printf("%s(%d):\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        //组装应答信息
            if(-1 == sendto(sockfd, buff, N, 0, (struct sockaddr *)&client_addr, clientaddrlen))
            ERRLOG("sendto error");
        
	if(!((buff[0]==0XAA)&&(buff[1]==0XAA)))
	{
		printf("buff[0] frame error  please input:AA AA \n");
	}else if(!((buff[13]==0x55)&&(buff[12]==0x55)))
    	{
		printf("error buff[8]\n");
    }
     printf("farme and end farme check success\n");
  if(buff[11]==0X01)
  {  
     printf("buff[11]==0x1");
     flag_num=1;
     continue;          //飞矩形
  }
  else if(buff[11]==0X02)
  {
    flag_num=2;  
     printf("buff[11]==0x2");
     continue;          //逆时针圆形
  }
  else if(buff[11]==0X03)
  {
    flag_num=3;   
     printf("buff[11]==0x3");
     continue;          //顺时针圆形
  }
   else if(buff[11]==0X04)
  {
    flag_num=4;   
    printf("buff[11]==0x4");
    cx=get_local_pose.pose.position.x;     //在当前位置的绕圆心运动
    cy=get_local_pose.pose.position.y;    
     continue;          //顺时针圆形
  }
  else if(buff[11]==0X05){
    flag_num=5;   
     printf("buff[11]==0x5");
     continue;  
  }
  else if(buff[11]==0X06){
    flag_num=6; 
     printf("buff[11]==0x6\n");
    continue;  
  }
  else 
  {
    flag_num=0;      
  }
    float angle=buff[6];    //yaw
    float x=buff[7];        //x
    float y=buff[8];        //y
    float z=(float)(buff[9]*256+buff[10])/100;
    printf("z==%f\n",z);
        //米
    printf("buff[5]=%#x, *Angle=%f\n",buff[5],angle);
	if(buff[2]==0x1)    //判断是否向上飞
	{
	    pose.pose.position.z=get_local_pose.pose.position.z+z; //向上飞几米
	    printf("向上飞几米=%f\n",pose.pose.position.z);
	}
  else if(buff[2]==0x2)//向下飞几米
	{   				
	 	  pose.pose.position.z=get_local_pose.pose.position.z-z;
		  printf("向下飞几米=%f\n",pose.pose.position.z);
	  	if(pose.pose.position.z<1)
	  	{
		     pose.pose.position.z=get_local_pose.pose.position.z; //小于一米 保持高度不动
		  }
	}
  else{
		pose.pose.position.z=get_local_pose.pose.position.z;  //保持当前高度不动
	}
	if(buff[3]==0x3)//判断是否向前飞
	{
		pose.pose.position.x=get_local_pose.pose.position.x+x; //向前飞几米
		printf("向前飞几米=%f\n",pose.pose.position.x);
	}else if(buff[3]==0x04)//向后飞几米
	{ 
		printf("向后飞几米=%f\n",pose.pose.position.x);		
		pose.pose.position.x=get_local_pose.pose.position.x-x;	 	
	}else{
		pose.pose.position.x=get_local_pose.pose.position.x;// 保持当前前后位置不变
	}
//在左右问题上ros采用的是ENU坐标系 此时飞机正方向在左侧。但是mavros会将enu坐标系转换为ned坐标系。但是我们键入的时候还是应以enu键入
if(buff[4]==0x05)   //判断是否向左飞
	{
	 	pose.pose.position.y=get_local_pose.pose.position.y+y;     //向左飞几米
	 	printf("向左飞几米=%f\n",pose.pose.position.y);
	}
  else if(buff[4]==0x06)                   //向右飞
	{   		
	 	printf("向右飞几米=%f\n",pose.pose.position.y);		
	 	pose.pose.position.y=get_local_pose.pose.position.y-y;	 	
	}else
  {
		pose.pose.position.y=get_local_pose.pose.position.y;
	}
	if(buff[5]==0xCC){                      //基于机头向左转
		pose.pose.yaw=angle/57.295779;
	}
  else if(buff[5]==0xDD)                  //基于机头向右转
	{ 
		pose.pose.yaw=-angle/57.295779;
	}
}
}
int main(int argc, char *argv[])
{
    //1.创建用户数据报式套接字
      sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(-1 == sockfd){
        ERRLOG("socket error");
    }
    //创建服务器网络信息结构体
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6789);
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.11");
    socklen_t addrlen = sizeof(server_addr);
    //3.将套接字和网络信息结构体进行绑定
    if(-1 == bind(sockfd, (struct sockaddr *)&server_addr, addrlen)){
        ERRLOG("bind error");
    }
    memset(&server_addr, 0, sizeof(client_addr));    //清空
    clientaddrlen = sizeof(client_addr);
    //2.初始化ROS节点 定义节点名称
    ros::init(argc, argv, "talker");
    //3.创建节点句柄
    ros::NodeHandle nh;
    //4.创建发布者对象
    ros::Publisher  pub = nh.advertise<talkersrv::contrl>("chatter",2);
    ros::Subscriber get_pose = nh.subscribe<geometry_msgs::PoseStamped>("mavros/local_position/pose", 10, pose_callback);
  // ros::Subscriber global=nh.subscribe<mavros_msgs::PositionTarget>("/mavros/setpoint_raw/target_local",10,raw_position_loop);
  // ros::Subscriber  battery_from_fcu=nh.subscribe<sensor_msgs::BatteryState>("/mavros/battery",10,) 电量信息
 //   ros::Subscriber  current_state=nh.subscribe<mavros_msgs::State>("/mavros/state",10,state_Callback);
//阻塞接受/发送位置信息
pthread_t tid;
    if((pthread_create(&tid,NULL,task,NULL))!=0){
        fprintf(stderr,"pthread create task error\n");
        exit(EXIT_FAILURE);
    }
    pthread_detach(tid);
    pose.pose.coordinate_frame=1;
    pose.pose.type_mask= mavros_msgs::PositionTarget::IGNORE_VX |
                        mavros_msgs::PositionTarget::IGNORE_VY |
                        mavros_msgs::PositionTarget::IGNORE_VZ |
                        mavros_msgs::PositionTarget::IGNORE_AFX |
                        mavros_msgs::PositionTarget::IGNORE_AFY |
                        mavros_msgs::PositionTarget::IGNORE_AFZ |
                        mavros_msgs::PositionTarget::FORCE |
                        mavros_msgs::PositionTarget::IGNORE_YAW_RATE;
	  pose.pose.position.x=0;
	  pose.pose.position.y=0;
    pose.pose.position.z=10;
    ros::Rate rate(20.0);
  ros::Time  last_request;
  int flag=1;
  while (ros::ok())
  {       
          if(flag_num==1)
          {
              if((flag == 1)  && (ros::Time::now() - last_request > ros::Duration(10.0)))
              { 
              ROS_INFO("position1(0 , 0,  5)");
                  pose.pose.coordinate_frame=1;
                  pose.pose.position.x = 0;
                  pose.pose.position.y = 0;
                  pose.pose.position.z = 15;
                  pose.mode=1;
                  last_request = ros::Time::now();
                  flag=2;
                        //local_pos_pub.publish(pose);
              }

            if((flag ==2) && (ros::Time::now() - last_request > ros::Duration(10.0)))
            {
              ROS_INFO("position2(5 , 0,  5)");
                          pose.pose.coordinate_frame=1;
                          pose.pose.position.x = 5.0;
                          pose.pose.position.y = 0.0;
                          pose.pose.position.z = 15;
                           pose.mode=1;
                        last_request = ros::Time::now();
                              flag=3;
              //local_pos_pub.publish(pose);
                        }
                              
            if((flag ==3) && (ros::Time::now() - last_request > ros::Duration(10.0)))
                        {
                                ROS_INFO("position3(5 , 5,  5)");
                                pose.pose.coordinate_frame=1;
                                pose.pose.position.x = 5.0;
                                pose.pose.position.y = 5.0;
                                pose.pose.position.z = 15;
                                 pose.mode=1;
                                 pose.pose.yaw=90.0/57.295779;
                                last_request = ros::Time::now();
                                  flag=4;
                                //local_pos_pub.publish(pose);
                        }

            if((flag ==4) && (ros::Time::now() - last_request > ros::Duration(10.0)))
                        {
                                ROS_INFO("position4(0 , 5,  5)");
                                pose.pose.coordinate_frame=1;
                                pose.pose.position.x = 0;
                                pose.pose.position.y = 5.0;
                                pose.pose.position.z = 15;
                                pose.mode=1;
                                 pose.pose.yaw=180.0/57.295779;
                                last_request = ros::Time::now();
                                flag=5;
                                //local_pos_pub.publish(pose);
                        }
            if((flag ==5) && (ros::Time::now() - last_request > ros::Duration(10.0)))
                        {
                                ROS_INFO("position5(0 ,0,  5)");
                                pose.pose.coordinate_frame=1;
                                pose.pose.position.x = 0;
                                pose.pose.position.y = 0;
                                pose.pose.position.z = 15;
                                pose.mode=1;
                                pose.pose.yaw=270.0/57.295779;
                                last_request = ros::Time::now();
                                flag=6;
                                //local_pos_pub.publish(pose);
                      }
            if((flag ==6) && (ros::Time::now() - last_request > ros::Duration(10.0)))          
            {
                                pose.pose.coordinate_frame=1;
                                pose.pose.position.x = 5;
                                pose.pose.position.y = 0;
                                pose.pose.position.z = 15;
                                 pose.mode=1;
                                pose.pose.yaw=0.0/57.295779;
                                last_request = ros::Time::now();
                                flag=7;


            }
            if((flag ==7) && (ros::Time::now() - last_request > ros::Duration(10.0)))         
            {
                                pose.pose.coordinate_frame=1;
                                pose.pose.position.x = 5;
                                pose.pose.position.y = 0;
                                pose.pose.position.z = 10; 
                                 pose.mode=1;  //模拟降落
                                last_request = ros::Time::now();
                                flag=8;
            }
            if((flag ==8) && (ros::Time::now() - last_request > ros::Duration(10.0)))          
            {
                                pose.pose.coordinate_frame=1;
                                pose.pose.position.x = 0;
                                pose.pose.position.y = 0;
                                pose.pose.position.z = 15;  
                                pose.mode=1;   //回到初始位置待命
                                last_request = ros::Time::now();
                                flag=9;
            }
           if((flag ==9) && (ros::Time::now() - last_request > ros::Duration(10.0)))   
            {
              flag_num=0;
            }
         }
        if(flag_num==2)
         {  //更新目标位置和姿态
          // radius=buff[11];
           pose.number=1;
           pose.pose.coordinate_frame=1;
          //pose.pose.header.stamp = ros::Time::now();
           pose.pose.position.x = cx + radius * cos(theta);
           pose.pose.position.y = cy + radius * sin(theta);
           pose.pose.yaw = atan2(pose.pose.position.y - cy, pose.pose.position.x - cx)+M_PI;  //机头向内  逆时针
            // 更新角度
            theta += dtheta;
            pose.mode=2;
            ROS_INFO("nihsizhen");
         }
          if(flag_num==3)
         {  //更新目标位置和姿态
          // radius=buff[11];
           pose.number=1;
           pose.pose.coordinate_frame=1;
          //pose.pose.header.stamp = ros::Time::now();
           pose.pose.position.x = cx + radius * cos(theta);
           pose.pose.position.y = cy + radius * sin(theta);
           pose.pose.yaw = atan2(pose.pose.position.y - cy, pose.pose.position.x - cx)+M_PI;  //机头向内  顺时针
            // 更新角度
            theta -= dtheta;
            pose.mode=3;
            ROS_INFO("shunshizhen ");
        }
         if(flag_num==4)
         {  //更新目标位置和姿态
          // radius=buff[11];
           pose.number=1;
           pose.pose.coordinate_frame=1;
          //pose.pose.header.stamp = ros::Time::now();
           pose.pose.position.x = cx + radius * cos(theta);
           pose.pose.position.y = cy + radius * sin(theta);
           pose.pose.yaw = atan2(pose.pose.position.y - cy, pose.pose.position.x - cx)+M_PI;  //机头向内  顺时针
            // 更新角度
            theta -= dtheta;
            pose.mode=4;
            ROS_INFO("shunshizhen ");
          }
          if(flag_num==5)
          {
            pose.mode=5;
          }
          if(flag_num==6)
          {
              pose.mode=6;
              pose.pose.coordinate_frame=1;
          }
        ros::spinOnce();
        rate.sleep();
        pub.publish(pose);
    }
    //关闭套接字
    close(sockfd);
    return 0;
}