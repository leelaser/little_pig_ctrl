# Little Pig Control - ROS Package

This repository is meant for all the control based code **only**. Example's of such:
- Mapping a game controller to the controls of the simulated/real little pig.

### Installation instructions

Heres a simple guide to get you started with Little Pig Control. Before continuing, be sure to have ROS Melodic installed.

- **Step 1.**
  - ```cd catkin_ws/src```
- **Step 2.**
  - ```git clone https://github.com/22arw/little_pig_ctrl.git```
  - If you don't have the other three packages you can run these lines also:
    - ```git clone https://github.com/22arw/little_pig_rviz.git```
    - ```git clone https://github.com/22arw/little_pig_description.git```
    - ```git clone https://github.com/22arw/little_pig_gazebo.git```

Your resulting directory should have this layout:

- catkin_ws/
  - src/
    - little_pig_ctrl/
    - little_pig_description/
    - little_pig_gazebo/
    - little_pig_rviz/

### Usage Instructions

Once you have this repo downloaded, run the following commands in the terminal:

- ```cd ..```
- ```catkin_make```

This should completed without failing. If it does fail, call Coach.
