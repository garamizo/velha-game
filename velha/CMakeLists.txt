cmake_minimum_required (VERSION 2.6)
project (Velha)

include_directories(
	include
)

## Declare a C++ library
add_library(velha_lib
  src/velha.cpp
)

add_executable(play src/play.cpp)
target_link_libraries(play
  velha_lib
)