cmake_minimum_required(VERSION 2.8.3)

project(little_pig_ctrl)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(catkin REQUIRED
  COMPONENTS
    roscpp
    roslib
    std_msgs
    std_srvs
)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    canopen_ros_chain
  CATKIN_DEPENDS
    roscpp
    std_srvs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

# pig_driver
add_library(PigDriver
  src/PigDriver.cpp
)
target_link_libraries(PigDriver
  ${catkin_LIBRARIES}
)
add_dependencies(PigDriver
  ${catkin_EXPORTED_TARGETS}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)

# pig_driver_node
add_executable(pig_driver_node
  src/pig_driver_node.cpp
)
target_link_libraries(pig_driver_node
  canopen_ros_chain
  PigDriver
  ${catkin_LIBRARIES}
)

install(
  TARGETS
    pig_driver_node
    PigDriver
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(
  DIRECTORY
    include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)

install(
  DIRECTORY
    launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
