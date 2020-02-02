cmake_minimum_required(VERSION 2.8.3)
project(little_pig_ctrl)

find_package(catkin REQUIRED COMPONENTS
  rospy
  tf
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
