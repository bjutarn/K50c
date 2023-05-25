/**
 * @file offb_node.cpp
 * @brief offboard example node, written with mavros version 0.14.2, px4 flight
 * stack and tested in Gazebo SITL
 */
#include<queue>
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/PositionTarget.h>
#include <math.h>
#include <mavros_msgs/OverrideRCIn.h>
#include <rosbag/bag.h>
#include <std_msgs/Header.h>
#include<ros/time.h>
#include <thread>
#include </home/orangepi/catkin_ws/src/offboard_node/include/offboard_node/offboard_control.h>
#include </home//orangepi/catkin_ws/devel/include/talkersrv/contrl.h>
using namespace std;


#define DEBUG 1


//遥控器和 模式以及解锁状态
mavros_msgs::OverrideRCIn rc;
mavros_msgs::SetMode offb_set_mode;
mavros_msgs::CommandBool arm_cmd;

queue <talkersrv::contrl> m;   

queue <talkersrv::contrl> n;     

queue <talkersrv::contrl> p;  

queue <talkersrv::contrl> q;
queue <talkersrv::contrl> k;                                    //队列                          
//日志记录标志位
unsigned int flag_pose_target=0;
unsigned int flag_pose_local=0;
unsigned int flag_px4_state=0;

static rosbag::Bag bag;  // 日志记录

unsigned mode_flag=0;  // 控制模式
unsigned thread1 =0;
unsigned thread2 =0;
//ned 坐标和角度信息
mavros_msgs::PositionTarget pose;

talkersrv::contrl target_pose;

//无人机状态
mavros_msgs::State current_state;
geometry_msgs::PoseStamped get_local_pose;

void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
    flag_px4_state=1;
}

//订阅服务器的控制信息
void pose_target(const talkersrv::contrl::ConstPtr & pose_target)
{

    if(pose_target->mode==1){

        m.push(*pose_target); 
        mode_flag=1;  //任务模式
    }
    else if(pose_target->mode==2){

        n.push(*pose_target); 
        mode_flag=2;  //任务模式
    }
    else  if(pose_target->mode==3){

        p.push(*pose_target); 
        mode_flag=3;  //任务模式
    }
    else  if(pose_target->mode==4){
        q.push(*pose_target); 
        mode_flag=4;  //任务模式
    }
    else if(pose_target->mode==5)
    {
         printf("mode_flag=5\n");
        mode_flag=5;   //trl
    }
    else if(pose_target->mode==6)
    {
        mode_flag=6;  //land
        pose=pose_target->pose;
    }
    else 
    {
        pose=pose_target->pose;
    }
    flag_pose_target=1;
}
//本地位置
void pose_callback(const geometry_msgs::PoseStamped::ConstPtr &get_pose)
{
    get_local_pose=*get_pose;
    flag_pose_local=1;
}

//void *offboard_ctorl(ros::NodeHandle & NH)
//{
//}

//日志循环写入
void *task2(ros::NodeHandle & NH)
{   
    if (!bag.isOpen())
    {
    bag.open("/home/orangepi/ROSBAG/px4_log.bag", rosbag::bagmode::Write);       //不好用的话再用追加
    }
    ros::Publisher rc_pub=NH.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override",10);
    rc.channels[2]=0;
    ros::Rate spine(20.0);
    while(ros::ok())
    {  
        if(flag_pose_local==1)
        {   
            bag.write("/mavros/local_position/pose", get_local_pose.header.stamp.now(),get_local_pose);
            flag_pose_local=0;
        }
        if(flag_px4_state==1)
        {
            bag.write("/mavros/state",current_state.header.stamp.now(),current_state);
            flag_px4_state=0;
        }

        if(flag_pose_target==1)
        {   
         bag.write("/mavros/setpoint_raw/local",pose.header.stamp.now(),pose); 
         flag_pose_target=0;
        }
            rc_pub.publish(rc);
            spine.sleep();
        if(thread2==1)
        {
            break;
        }
    } 
    ROS_INFO("EXIT TASK2");
    bag.close();
    thread1=1;
    return NULL;
}   


int main(int argc, char **argv)
{

    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;
   
    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
            ("/mavros/state", 10, state_cb);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
            ("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>
            ("mavros/set_mode"); 

	//获取无人机实时的位置信息
     ros::Subscriber get_pose = nh.subscribe<geometry_msgs::PoseStamped>
            ("mavros/local_position/pose", 20, pose_callback); 

     //接收从服务器传来的位姿数据
      ros::Subscriber get_srv_pose = nh.subscribe<talkersrv::contrl>
            ("chatter", 20, pose_target);

    //发布无人机位置和角度
      /*ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/setpoint_position/local", 10);*/
    ros::Publisher local_pos_pub = nh.advertise<mavros_msgs::PositionTarget>
            ("mavros/setpoint_raw/local", 10);
    
    //线程处理
    std::thread mythread(task2,ref(nh));
   // std::thread offboard_thread(offboard_ctorl,ref(nh));

    //使用位姿控制
     /*ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("/mavros/setpoint_attitude/attitude", 10);*/

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(15.0);

    // wait for FCU connection
    while(ros::ok() && current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }
   pose.coordinate_frame=1;
   pose.type_mask= mavros_msgs::PositionTarget::IGNORE_VX |
                        mavros_msgs::PositionTarget::IGNORE_VY |
                        mavros_msgs::PositionTarget::IGNORE_VZ |
                        mavros_msgs::PositionTarget::IGNORE_AFX |
                        mavros_msgs::PositionTarget::IGNORE_AFY |
                        mavros_msgs::PositionTarget::IGNORE_AFZ |
                        mavros_msgs::PositionTarget::FORCE |
                        mavros_msgs::PositionTarget::IGNORE_YAW_RATE;
	pose.position.x=0;
	pose.position.y=0;
    pose.position.z=0;
    arm_cmd.request.value = true;

    for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }

    offb_set_mode.request.custom_mode = "OFFBOARD";
    ros::Time last_request = ros::Time::now();

while(ros::ok())
{
	    if( current_state.mode != "OFFBOARD" && (ros::Time::now() - last_request > ros::Duration(5.0)))
        {
                if( set_mode_client.call(offb_set_mode) && offb_set_mode.response.mode_sent)
                {
                    ROS_INFO("Offboard enabled");		                                              //break;
                }
                last_request = ros::Time::now( );
        } 
        else
        {
            if( !current_state.armed && (ros::Time::now() - last_request > ros::Duration(5.0)))
            {
                if(arming_client.call(arm_cmd) && arm_cmd.response.success)
                {
                    ROS_INFO("Vehicle armed");
                }
                last_request = ros::Time::now();
            }
        }
	    if ( current_state.mode == "OFFBOARD"&&current_state.armed)
        {
             ROS_INFO("qiedao offboard");
             break;
        }
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
}
while(1)
{       
    if(mode_flag==1)
    {                                                                 //判断是否为空
            pose=m.front().pose;                              // 
            m.pop();
        if(m.empty())
        {
            mode_flag=0;    
        }                                          //切换航点
    }
      if(mode_flag==2)
    {                                                                 //判断是否为空
            pose=n.front().pose;                                      // 
            n.pop();
        if(n.empty())
        {
            mode_flag=0;    
        }                                                      //切换航点
    }                   
      if(mode_flag==3)
    {                                                                 //判断是否为空
            pose=p.front().pose;                              // 
            p.pop();
        if(p.empty())
        {
            mode_flag=0;    
        }                                                       //切换航点
    }
      if(mode_flag==4)
    {                                                                 //判断是否为空
                pose=q.front().pose;                              // 
                q.pop();
        if(q.empty())
        {
            mode_flag=0;    
        }                                          //切换航点
    }
    if(mode_flag==5)
    {                                                                 //判断是否为空
            offb_set_mode.request.custom_mode = "AUTO.RTL";
            if( set_mode_client.call(offb_set_mode) && offb_set_mode.response.mode_sent)
            {
                ROS_INFO("AUTO.RTL");                                    
            }                                                              
    }
    if(mode_flag==6)
    {
        offb_set_mode.request.custom_mode = "AUTO.LAND";
        if(get_local_pose.pose.position.z<3)
        {
            if( set_mode_client.call(offb_set_mode) && offb_set_mode.response.mode_sent)
            {
                ROS_INFO("auto.land");  
                break;                            
            }
        }
    }
    if(current_state.mode != "OFFBOARD"||thread1==1) 
    {    
        break;

    }
    local_pos_pub.publish(pose);
    
    ros::spinOnce();
    rate.sleep();
    }
    ROS_INFO("control publish  pose");
    thread2=1;

    mythread.join();
    return 0;
}