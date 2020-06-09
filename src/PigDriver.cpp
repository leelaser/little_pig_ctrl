#include <little_pig_ctrl/PigDriver.h>
#include <canopen_chain_node/ros_chain.h>
#include <controller_manager/controller_manager.h>
#include <controller_manager_msgs/ControllerState.h>

#include <string>
#include <std_srvs/Trigger.h>
#include <std_msgs/String.h>



PigDriver::PigDriver(const ros::NodeHandle &nh)
    : nh_{ros::NodeHandle(nh, "Piggy")}, initialized{true}
{
    bus_init_ = nh_.serviceClient<std_srvs::Trigger>("/driver/init");
    bus_switch_ = nh_.serviceClient<controller_manager_msgs::SwitchController>("/controller_manager/switch_controller");
    bus_load_ = nh_.serviceClient<controller_manager_msgs::LoadController>("/controller_manager/load_controller");
    bus_halt_ = nh_.serviceClient<std_srvs::Trigger>("/driver/halt");
    bus_shutdown_ = nh_.serviceClient<std_srvs::Trigger>("/driver/shutdown");
    bus_recover_ = nh_.serviceClient<std_srvs::Trigger>("/driver/recover");

    pig_init_ = nh_.advertiseService("initialize",&PigDriver::init, this);
    pig_shutdown_ = nh_.advertiseService("shutdown",&PigDriver::shutdown, this);
    pig_halt_ = nh_.advertiseService("halt",&PigDriver::halt, this);
    pig_reset_ = nh_.advertiseService("reset",&PigDriver::reset, this);
    pig_start_ = nh_.advertiseService("motor_start",&PigDriver::motor_start, this);
    pig_stop_ = nh_.advertiseService("motor_stop",&PigDriver::motor_stop, this);
    
    startService.request.start_controllers = {"ackermann_controller"};
    startService.request.stop_controllers = {};
    startService.request.strictness = 2;
    startService.request.start_asap = false;
    startService.request.timeout = 0.0;

    stopService.request.start_controllers = {};
    stopService.request.stop_controllers = {"ackermann_controller"};
    stopService.request.strictness = 2;
    stopService.request.start_asap = false;
    stopService.request.timeout = 0.0;

    loadService.request.name = "ackermann_controller";

    unloadService.request.name = "ackermann_controller";

    // startService.request = {
    //     .start_controllers = {"ackermann_controller"},
    //     .stop_controllers = {},
    //     .strictness = 2,
    //     .start_asap = false,
    //     .timeout = 0.0};

    // stopService.request = {
    //     .start_controllers = {},
    //     .stop_controllers = {"ackermann_controller"},
    //     .strictness = 2,
    //     .start_asap = false,
    //     .timeout = 0.0};
    
    // loadService = {

    // }

    bus_init_.waitForExistence();
    std_srvs::Trigger srv;
    bus_init_.call(srv);
    if(!srv.response.success)
    {
        ROS_ERROR("CAN did not initialize! MESSAGE: %s", srv.response.message.c_str());
        ROS_ERROR("ReAttempting!");
        bus_init_.call(srv);
        if(!srv.response.success)
        {
            ROS_ERROR("CAN failed to initialize on the second attempt");
        }
        else initialized = true;
    }
    else initialized = true;

    bus_load_.waitForExistence();
    bus_load_.call(loadService);
}

PigDriver::~PigDriver()
{
    // std_srvs::Trigger srv;
    // srv.
    // init_.
}

bool PigDriver::init(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res)
{
    std_srvs::Trigger srv;
    bus_init_.call(srv);

    res.success = srv.response.success;
    res.message = srv.response.message;

    if(!initialized && srv.response.success)
    {
        bus_load_.waitForExistence();
        bus_load_.call(loadService);
    }

    if(!res.success)
    {
        ROS_ERROR("CAN did not initialize! MESSAGE: %s", srv.response.message.c_str());
        initialized = false;
    }
    else
    {
        ROS_DEBUG("CAN init SUCCESSFUL!");
        initialized = true;
    }
    return true;
}

bool PigDriver::motor_start(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res)
{
    bus_switch_.call(startService);
    bus_switch_.call(stopService);
    bus_switch_.call(startService);
    res.success = startService.response.ok;
    //res.message = startService.response.message;
    return true;
}

bool PigDriver::motor_stop(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res)
{
    bus_switch_.call(stopService);
    res.success = stopService.response.ok;
    //res.message = stopService.response.message;
    return true;
}

bool PigDriver::halt(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res)
{
    std_srvs::Trigger srv;
    bus_halt_.call(srv);
    
    res.success = srv.response.success;
    res.message = srv.response.message;

    if(!res.success)
    {
        ROS_ERROR("CAN did not halt! MESSAGE: %s", srv.response.message.c_str());
    }
    else
    {
        ROS_DEBUG("CAN halt SUCCESSFUL!");       
    }
    return true;
}

bool PigDriver::shutdown(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res)
{
    std_srvs::Trigger srv;
    bus_shutdown_.call(srv);
    
    res.success = srv.response.success;
    res.message = srv.response.message;

    if(!res.success)
    {
        ROS_ERROR("CAN did not shutdown! MESSAGE: %s", srv.response.message.c_str());
        initialized = true;
    }
    else
    {
        ROS_DEBUG("CAN shutdown SUCCESSFUL!");
        initialized = false;
    }
    return true;
}

bool PigDriver::reset(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res)
{
    std_srvs::Trigger srv;
    //bus_switch_.call(stopService);
    motor_stop(srv.request, srv.response);
    shutdown(srv.request, srv.response);
    initialized = false;
    init(srv.request, srv.response);
    initialized = true;

    bus_load_.waitForExistence();
    bus_load_.call(loadService);

    motor_start(srv.request, srv.response);

    res.success = srv.response.success;
    res.message = srv.response.message;

    if(!res.success)
    {
        ROS_ERROR("CAN did not reset! MESSAGE: %s", srv.response.message.c_str());
        initialized = false;
    }
    else
    {
        ROS_DEBUG("CAN reset SUCCESSFUL!");
        initialized = true;
    }
    return true;
}