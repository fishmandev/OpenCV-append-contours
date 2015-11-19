cmake_minimum_required(VERSION 3.3)
project(append_contours)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES main.cpp)
add_executable(append_contours ${SOURCE_FILES})
target_link_libraries(append_contours ${OpenCV_LIBS})