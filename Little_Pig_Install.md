# Little Pig Installation Documentation

## Requirements

##### Environment for melodic development and execution
* **Ubuntu 18.04** 			
* **Bash as your shell** 	
* **sudo access**			 
* **Standard git command line application** 	


##### Repositories
* [ackermann_controller](https://github.com/22arw/ackermann_controller)
* [little_pig_ctrl](https://github.com/22arw/little_pig_ctrl)
* [little_pig_description](https://github.com/22arw/little_pig_description)
* [little_pig_gazebo](https://github.com/22arw/little_pig_gazebo)
* [little_pig_navigation](https://github.com/22arw/little_pig_navigation)
* [little_pig_rviz](https://github.com/22arw/little_pig_rviz)
* [gazebo_ros_control](https://github.com/22arw/gazebo_ros_control) -not listed in little pig repos on github


##### Additional packages
These are required for making packages in ROS
* python-rosdep
* python-rosinstall
* python-rosinstall-generator
* python-wstool
* build-essential
* ros-melodic-catkin
* cmake

These are installed in the final section and are required for running the robot in it's current state
* ros-melodic-gmapping
* ros-melodic-slam-gmapping
* ros-melodic-joy
* ros-melodic-static-tf
* ros-melodic-mavros
* ros-melodic-hector-gazebo-plugins
* ros-melodic-teleop-twist_joy
* ros-melodic-robot-localization
* ros-melodic-joint-state-publisher
* ros-melodic-robot-state-publisher

Most packages for ros melodic should follow the naming scheme `ros-melodic-<something>`
 
 
## Full install
This installation is separated into several parts. These are [installing the base repository](#ROS-component-install), [creating the workspace/pulling repos](#Workspace-Creation-and-Repos), and [installing additional packages](#Package-Installation).  The first of these is the same installation procedure you would find on the wiki.  The second of these involves setting up your workspace for first time usage and then pulling the necessary repos.  The final part this is the shortest and will cover installing additional packages.


##### Notes to remember
A variable shown as `<stuff_or_things>` is used periodically to signify a placeholder that could be different for each user. For example it could be a user account or a filename.  The most commone one you will see should be workspace. <br>
Seeing something as `echo $?` Will give you a return code for the last command run in your terminal.  This is useful for for any utility without standard output.

Any segments denoted as `code` can be pasted directly into your shell.  
```
This is also code that can be pasted directly into your shell or an example of what should be seen in your shell
```

### ROS component install
This part of the installation is what is covere on the ros wiki.  If you need additional information about what is happening in these steps it may be found ln the ros wiki.  If you have already installed the package *ros-melodic-desktop-full* , you may want to skip this section.


##### Set up keys and package repository for ubuntu
The simple explanation of what is being done with these commands is that you're telling your operating system where to look for packages and giving it identifying info to make sure they are transmitted securely.
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
```

If the ffirst of the two commands fails, you probably don't have root access.  If the second of the above commands fails, try either of the two below commands to try to give apt the information it needs.  If these too fail, there is a ubuntu issue. 
```
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
#or
curl -sSL 'http://keyserver.ubuntu.com/pks/lookup?op=get&search=0xC1CF6E31E6BADE8868B172B4F42ED6FBAB17C654' | sudo apt-key add -
```

##### Install the system
Once you have told your operating system where to look for packages, you can install the first of the packages you need.  As good practice you should run an update before you try to install this software.
```
sudo apt update
sudo apt-get install ros-melodic-desktop-full
```
You should also install some useful tools here too.  These are reccomended for package creation on the ros wiki.  To install them run
```
sudo apt-get install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential ros-melodic-catkin cmake git
#This should install
#python-rosdep
#python-rosinstall
#python-rosinstall-generator
#python-wstool
#build-essential
#ros-melodic-catkin
#cmake
```

### Workspace Creation and Repos
In this portion of the install, you are going to be creating a workspace for the little pig source files.  This will involve creating a workspace, and cloning repos into the workspace.

##### Set up workspace
Once you have the basic ROS tools installed you can create a workspace to work in.
<workspace> signifies the file location of your workspace.  As an example my workspace usually exists in `/home/vm1804/little_pig_workspace`.
```
mkdir -P <workspace>/src
cd <workspace>
source /opt/ros/melodic/setup.bash
catkin_make
```

##### Repo Installation in src
Cloning repos is a relatively straightforward task.  You simply use git clone to clone the repos we need into the src folder of your workspace.  An example of the commands with the 
```
cd <workspace>/src
git clone https://github.com/22arw/ackermann_controller
git clone https://github.com/22arw/little_pig_ctrl
git clone https://github.com/22arw/little_pig_description
git clone https://github.com/22arw/little_pig_gazebo
git clone https://github.com/22arw/little_pig_navigation
git clone https://github.com/22arw/little_pig_rviz
git clone https://github.com/22arw/gazebo_ros_control
```

##### Check before you move on
Check the full launch file that you will be running to make sure sime is set to true rather than to false.  This file should be located under the repo, little_pig_ctrl and its location can be obtained by using cd to enter your workspace and then running a find and passing that file name into an editor.  Here are 2 example of how those commands would be run.

<workspace> signifies the file location of your workspace.  As an example my workspace usually exists in `/home/vm1804/little_pig_workspace` but yours should be wherever you installed it previously.
```
#all in one
vi $(cd <workspace> ; find . | grep -E 'full.launch$')

#step by step
cd <workspace>
find . | grep -E 'full.launch'
vi <location_given_from_last_line>
```

### Package Installation
This part of the installation process is relatively simple.  Ths part is where you use apt-get to install the rest of the package dependencies that may have been missed earlier.

For each in this list run 
```
sudo apt-get install <package>
```

Based on the current code, the sequential commands for this would be as shown below.
```
sudo apt-get install ros-melodic-gmapping
sudo apt-get install ros-melodic-slam-gmapping
sudo apt-get install ros-melodic-joy
sudo apt-get install ros-melodic-static-tf
sudo apt-get install ros-melodic-mavros
sudo apt-get install ros-melodic-hector-gazebo-plugins
sudo apt-get install ros-melodic-teleop-twist_joy
sudo apt-get install ros-melodic-robot-localization
sudo apt-get install ros-melodic-joint-state-publisher
sudo apt-get install ros-melodic-robot-state-publisher
```
### Run the robot sim
In one terminal run 
```
source <workspace>/source/devel/setup.bash
roscore
```
Leave that running and in a separate terminal run
```
source <workspace>/source/devel/setup.bash
roslaunch little_pig_ctrl full.launch | tee ~/little_pig_sim_outfile
```
This should launch the little pig simuation. From there look for errors in the output file `~/little_pig_sim_outfile` that was tee'd off of the launch file.  The output file can get relatively large so if space is an issue, while you're not troubleshooting you may want to consider removing the pipe and tee at the end to save hardware space.

## Troubleshooting
Errors you may see in the output file or elsewhere

1. Most errors you will see in the output will be errors regarding launching nodes. You will see these appear as below.
```
ERROR: cannot launch node of type [teleoop_twist_joy/teleop_node]: joy
ROS path [0]=/opt/ros/melodic/share/ros
ROS path [1]=/home/vm1804/testws/src
ROS path [2]=/opt/ros/melodic/share
```
In this case, the package thaat is missing is teleop_twist joy. 
If you see any unfamiliar package, you can use the command
```
apt list | grep <string>
```
to search for any package containing a string of your choosing.

2. Rviz is another package that often doesn't work out of the box.  This issue mostly seems to appear on computers with no dedicated GPU.  These are processors such as any AMD APU and any Intel HD Graphics video adapter. In this case, in order to get the lasers to function correctly, you should remove the gpu notation from basic_laser_pig.gazebo.
```
#as an example
<sensor type="gpu_ray" name="head_hokuyo_sensor">
#should become
<sensor type="ray" name="head_hokuyo_sensor">
```
If this doesn't seem to fix the problem, use a recursive grep to find gpu within the repository.  It is easy to miss one.
```
#example grep
cd <workspace>
grep -ir "gpu" *
```

3. If your robot doesn't launch and the roslaunch terminal tells you anything about mavros, the sim is most likely set to false and you should change that boolean value in the full.launch file as described in the workspace creation section.

4. Joystick not working, you should install jstest-gtk and then look for the teleop launch file in the little_pig_ctrl and append the node with pkg joy with
```
<param name="dev" type="string" value="/dev/input/js1" />
```
js1 should be replaced with whatever js output jstest-gtk tells you the desired controller is on


