#ifndef H_PIGDRIVER
#define H_PIGDRIVER

#include <ros/ros.h>
#include <std_srvs/Trigger.h>

//#include <controller_manager/controller_manager.h>
#include <controller_manager_msgs/LoadController.h>
#include <controller_manager_msgs/UnloadController.h>
#include <controller_manager_msgs/SwitchController.h>
//#include <diagnostic_updater/diagnostic_updater.h>

class PigDriver
{
private:

public:
    PigDriver(const ros::NodeHandle &nh);
    virtual ~PigDriver();

protected:
    ros::NodeHandle nh_;

    ros::ServiceClient bus_init_;
    ros::ServiceClient bus_switch_;
    ros::ServiceClient bus_load_;
    ros::ServiceClient bus_halt_;
    ros::ServiceClient bus_shutdown_;
    ros::ServiceClient bus_recover_;

    ros::ServiceServer pig_init_;
    ros::ServiceServer pig_start_;
    ros::ServiceServer pig_stop_;
    ros::ServiceServer pig_halt_;
    ros::ServiceServer pig_shutdown_;
    ros::ServiceServer pig_reset_;

    controller_manager_msgs::SwitchController startService;
    controller_manager_msgs::SwitchController stopService;
    controller_manager_msgs::LoadController loadService;
    controller_manager_msgs::UnloadController unloadService;

    bool initialized;   //Goes true when bus is running

    //diagnostic_updater::Updater diag_updater_;  //Maybe Unnecessary

    virtual bool init(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res);
    virtual bool motor_start(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res);
    virtual bool motor_stop(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res);
    virtual bool halt(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res);
    virtual bool shutdown(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res);
    virtual bool reset(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res);

};

#endif