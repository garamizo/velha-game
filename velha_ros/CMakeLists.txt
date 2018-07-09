cmake_minimum_required(VERSION 2.8.3)
project(velha_ros)

# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  genmsg
  message_generation
)

add_service_files(
  FILES
  MakeMove.srv
)

generate_messages(
  DEPENDENCIES std_msgs  # Or other packages containing msgs
)

catkin_package(
 # INCLUDE_DIRS include
#  LIBRARIES velha
 CATKIN_DEPENDS message_runtime
  # DEPENDS 
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/../velha/include
)

## Declare a C++ library
add_library(velha
  ../velha/src/velha.cpp
)

add_executable(robot_player src/robot_player.cpp)

add_dependencies(robot_player ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(robot_player
  ${catkin_LIBRARIES}
  velha
)


add_executable(robot_server src/robot_server.cpp)

add_dependencies(robot_server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(robot_server
  ${catkin_LIBRARIES}
  velha
)
