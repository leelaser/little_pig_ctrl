cmake_minimum_required(VERSION 2.8.3)

project(little_pig_ctrl)

find_package(catkin REQUIRED COMPONENTS rospy tf)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

catkin_install_python(PROGRAMS src/ackermann_controller DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
install(DIRECTORY config src DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

