#include <wiringPi.h>
#include <unistd.h>
#include<stdio.h>
#include <math.h>
#include<ros/ros.h>
#include<std_msgs/UInt8MultiArray.h>

#define IN1 0  //定义管脚
#define IN2 1
#define IN3 2
#define IN4 5

std_msgs::UInt8MultiArray steps_data;
unsigned char base_steps=127;
//起始角度为0度

void backward(unsigned char steps);     
void forward(unsigned char steps);
void setStep(int a, int b, int c, int d) //设置步进电机的状态
{
    digitalWrite(IN1, a);
    digitalWrite(IN2, b);
    digitalWrite(IN3, c);
    digitalWrite(IN4, d);
}
void stepsCallback(const std_msgs::UInt8MultiArray::ConstPtr &msg) {
    // 获取步数值
    if(msg->data[0]==360)  // 向上校准
    {
        forward(1);
    }
    else if(msg->data[0]==270) // 向下校准
    {
       backward(1);
    }
    else{
        setStep(0,0,0,0);
    }    

    if(msg->data[1]>=base_steps)             //校准完成
    {   
       base_steps=msg->data[1]-base_steps;
       forward(base_steps);
    }else if(msg->data[1]<base_steps)
    {
        base_steps=base_steps-msg->data[1];
    }
 }
void forward(unsigned char steps)           //向前转动步进电机
{
    int i=0;
    for(i=0; i<steps; i++)
    {
        setStep(1,0,0,1);
        usleep(1000);
        setStep(1,0,0,0);
        usleep(1000);
        setStep(1,1,0,0);
        usleep(1000);
        setStep(0,1,0,0);
        usleep(1000);
        setStep(0,1,1,0);
        usleep(1000);
        setStep(0,0,1,0);
        usleep(1000);
        setStep(0,0,1,1);
        usleep(1000);
        setStep(0,0,0,1);
        usleep(1000);
    }
     setStep(0,0,0,0);
     usleep(1000);
}
void backward(unsigned char steps)                     //向后转动步进电机
{  
    for(int i=0; i<steps; i++)
    {
            setStep(0,0,0,1);
            usleep(1000);
            setStep(0,0,1,1);
            usleep(1000);
            setStep(0,0,1,0);
            usleep(1000);
            setStep(0,1,1,0);
            usleep(1000);
            setStep(0,1,0,0);
            usleep(1000);
            setStep(1,1,0,0);
            usleep(1000);
            setStep(1,0,0,0);
            usleep(1000);
            setStep(1,0,0,1);
            usleep(1000);
    }
    setStep(0,0,0,0);
    usleep(1000);
}
int main(int argc, char **argv)
{
 wiringPiSetup();         //初始化wiringPi库
    pinMode(IN1, OUTPUT);      //设置管脚为输出模式
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    ros::init(argc, argv, "motor_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<std_msgs::UInt8MultiArray>("steps", 10,stepsCallback);
    ros::Rate rate(20);
    while(1)
    {
        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}
