/**
 * @file offb_node.cpp
 * @brief offboard example node, written with mavros version 0.14.2, px4 flight
 * stack and tested in Gazebo SITL
 */

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



//ned 坐标和角度信息
mavros_msgs::PositionTarget pose;
static rosbag::Bag baag;
//无人机状态
mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
    baag.write("/mavros/state", ros::Time::now(), *msg);
}
//四元数反推角度
/*struct Quaternion

{
    double w, x, y, z;
};
 
Quaternion ToQuaternion(double yaw, double pitch, double roll) // yaw (Z), pitch (Y), roll (X)
{
    // Abbreviations for the various angular functions
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);
 
    Quaternion q;
    q.w = cy * cp * cr + sy * sp * sr;
    q.x = cy * cp * sr - sy * sp * cr;
    q.y = sy * cp * sr + cy * sp * cr;
    q.z = sy * cp * cr - cy * sp * sr;
    return q;
}*/
//订阅服务器的控制信息
void pose_target(const mavros_msgs::PositionTarget::ConstPtr & pose_target)
{
	pose=*pose_target;
	//printf("from srv pose.x= %f\n",pose_target->position.x);
	//printf("from srv pose.y= %f\n",pose_target->position.y);
	//printf("from srv pose.z= %f\n",pose_target->position.z);
	//printf("from srv pose.yaw= %f\n",pose_target->yaw);
  
    baag.write("mavros/setpoint_raw/local", ros::Time::now(), *pose_target);
}


void pose_callback(const geometry_msgs::PoseStamped::ConstPtr &get_pose)
{	

    baag.write("mavros/local_position/pose", ros::Time::now(), *get_pose);
/*ROS_INFO("position.x=%f\n",get_pose->pose.position.x);
ROS_INFO("position.y=%f\n",get_pose->pose.position.y);
ROS_INFO("position.z=%f\n",get_pose->pose.position.z);*/

}

int main(int argc, char **argv)
{

    if (!baag.isOpen()) {
    baag.open("/home/orangepi/px4_log.bag", rosbag::bagmode::Write);
    }
    ROS_INFO("HELLO");
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
      ros::Subscriber get_srv_pose = nh.subscribe<mavros_msgs::PositionTarget>
            ("chatter", 20, pose_target);

     //发布无人机位置和角度
      /*    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/setpoint_position/local", 10);*/
       ros::Publisher local_pos_pub = nh.advertise<mavros_msgs::PositionTarget>
            ("mavros/setpoint_raw/local", 10);

    //RC
     ros::Publisher  rc_pub=nh.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override",10);
    
	

//使用位姿控制
     /*ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("/mavros/setpoint_attitude/attitude", 10);*/


    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);

    // wait for FCU connection
    while(ros::ok() && current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

	// 无人机的位置信息和角度信息
        // 四元数反推角度

   /*  geometry_msgs::PoseStamped pose;
        pose.pose.position.x = 5;
        pose.pose.position.y = 6;
        pose.pose.position.z = 6;
*/

//四元数
	/*Quaternion q=ToQuaternion(1.5,0,0);
	pose.pose.orientation.x=q.x;
    	pose.pose.orientation.y=q.y;
    	pose.pose.orientation.z=q.z;
   	pose.pose.orientation.w=q.w;*/


    pose.coordinate_frame=1;
	pose.position.x=0;
	pose.position.y=0;
	pose.position.z=3;
	pose.yaw=0;
    //send a few setpoints before starting

mavros_msgs::OverrideRCIn rc;
	//rc.channels[3]=0;	// xiangshangfei 

   /* for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }*/

    mavros_msgs::SetMode offb_set_mode;
    

    offb_set_mode.request.custom_mode = "MANUAL";//"OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    ros::Time last_request = ros::Time::now();
rc.channels[2]=0;
    while(ros::ok()){
	//mo ni  yaogan xiala
	
	rc_pub.publish(rc);     
        if( current_state.mode != "MANUAL"/*"OFFBOARD" */&&
            (ros::Time::now() - last_request > ros::Duration(5.0))){
            if( set_mode_client.call(offb_set_mode) &&
                offb_set_mode.response.mode_sent){
                ROS_INFO("MANUAL");
            }
            last_request = ros::Time::now();
        } 
        else {
            if( !current_state.armed &&
                (ros::Time::now() - last_request > ros::Duration(5.0))){
                if( arming_client.call(arm_cmd) &&
                    arm_cmd.response.success){
                    ROS_INFO("Vehicle armed");
                }
                last_request = ros::Time::now();
            }
 }

        // local_pos_pub.publish(pose);
        if(current_state.mode=="MANUAL"/*"OFFBOARD"*/&&current_state.armed)
       {
	    
            break;
        }
	
        ros::spinOnce();
        rate.sleep();
    }

//rc.channels[2]=00;

for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub.publish(pose);
	rc_pub.publish(rc);
        ros::spinOnce();
        rate.sleep();
    }

 offb_set_mode.request.custom_mode = "OFFBOARD";

    while(ros::ok())
    {
	if( current_state.mode != "OFFBOARD" &&
            (ros::Time::now() - last_request > ros::Duration(5.0))){
            if( set_mode_client.call(offb_set_mode) &&
                offb_set_mode.response.mode_sent){
                ROS_INFO("Offboard enabled");
		//break;
            }
            last_request = ros::Time::now( );
     	   } 

	//rc.channels[0]=1800;
	//rc.channels[1]=1800;
	//rc.channels[2]=1800;
	//rc.channels[3]=1800;
	
	rc_pub.publish(rc);
        local_pos_pub.publish(pose);
	   if(current_state.mode=="OFFBOARD"&&current_state.armed)
       {    
            break;
       }
       
        ros::spinOnce();
        rate.sleep();
    }

while(ros::ok())
{	

	if( current_state.mode != "OFFBOARD"){
	ROS_INFO(" exit offboard mode");

	break;
	}
 	local_pos_pub.publish(pose);
	rc_pub.publish(rc);
	ros::spinOnce();
    rate.sleep();
}

    baag.close();

    return 0;
}


