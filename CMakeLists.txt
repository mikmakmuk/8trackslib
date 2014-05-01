project(8trackslib)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(8tracks SHARED src/api.cpp src/exception.cpp)

target_link_libraries(8tracks curlpp jsoncpp)

set_target_properties(8tracks PROPERTIES VERSION 0.0.1 SOVERSION 1)

install(TARGETS 8tracks LIBRARY DESTINATION lib)
install(FILES include/api.hpp include/exception.hpp DESTINATION include/8trackslib)