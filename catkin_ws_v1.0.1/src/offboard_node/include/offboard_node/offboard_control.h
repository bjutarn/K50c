#ifndef OFFBOARD_H
#define OFFBOARD_H

#define MAX 128
class control2 
{
private:
    /* data */
public:
    control2(int i,int cont)
    {
    this->i=i;            //航点个数
    this->control=cont;   //控制模式
    }
    ~control2(){      
    }
    int i=1;            //航点个数
    int control=0;      //控制模式
    mavros_msgs::PositionTarget pose_target[MAX]; //航点
};

#endif