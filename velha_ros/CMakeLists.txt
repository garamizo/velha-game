cmake_minimum_required(VERSION 2.8.3)
project(velha_ros)

# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

catkin_package(
 # INCLUDE_DIRS include
#  LIBRARIES velha
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
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

add_executable(robot_play src/robot_play.cpp)

add_dependencies(robot_play ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(robot_play
  ${catkin_LIBRARIES}
  velha
)
