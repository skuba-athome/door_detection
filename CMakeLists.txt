cmake_minimum_required(VERSION 2.8.3)
project(door_detection)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs sensor_msgs genmsg)

catkin_package()

###########
## Build ##
###########

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(door_detection_node src/door_detection_node.cpp)
target_link_libraries(door_detection_node ${catkin_LIBRARIES})
