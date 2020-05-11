# Little Pig Control - ROS Package

This repository is meant for all the control based code **only**. Example's of such:
- Mapping a game controller to the controls of the simulated/real little pig.

### Using Teleop to drive Little Pig

#### In order to drive the vehicle with controller you must have "joy" and "teleop_twist_joy". If you do not have them run the following.

- sudo apt install ros-melodic-joy
- sudo apt install ros-melodic-teleop-twist-joy

#### If using wired the map is as follows
- param name="axis_angular" value="3"
- param name="enable_turbo_button" value="4"  THIS IS LB
- param name="enable_button" value="5"        THIS IS RB

#### If using bluetooth the map is as follows
- param name="axis_angular" value="2"
- param name="enable_turbo_button" value="6"  THIS IS LB
- param name="enable_button" value="7"        THIS IS RB

### Using CANopen 402

This node needs passed the robot name to search for robot description on param server  
  
This node needs passed a motor_driver.yaml file with the bus parameters as well as all specifics of the motors  
- This driver file can also handle dual motor drives as demonstrated in the yaml file
- This driver file needs a interval time to set update rate
- This driver file can also be given parameters to send out a heartbeat message
- List all difference CAN devices as nodes:
- Underneath nodes, designate a name and then also, you need to pass eds file and the ros package where it is located  
- Each motor needs passed the joint name and can set parameters for vel, pos, and eff to and from the device. These parameters can be designated using inline calculations


