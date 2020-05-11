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

