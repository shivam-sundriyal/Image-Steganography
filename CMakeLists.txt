cmake_minimum_required(VERSION 3.0.0)
project(stegano VERSION 0.1.0)

include(CTest)
enable_testing()

find_package( OpenCV REQUIRED)

add_executable(stegano encoding.cpp)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(stegano ${OpenCV_LIBS} ${CMAKE_THREADS_LIBS_INIT})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
