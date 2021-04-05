#include <ros/ros.h>
#include <cstdlib>
#include <little_pig_ctrl/PigDriver.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Piggy");
    ros::NodeHandle nh;

    PigDriver driver(nh);

    ros::spin();
    return 0;
}