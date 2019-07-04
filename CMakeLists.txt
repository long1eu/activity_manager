cmake_minimum_required(VERSION 3.14)
project(activity_manager)

set(CMAKE_CXX_STANDARD 17)

add_executable(activity_manager main.cpp models/Process.cpp models/Process.h utils/constants.h utils/util.h models/ProcessParser.cpp models/ProcessParser.h models/ProcessContainer.cpp models/ProcessContainer.h models/SysInfo.cpp models/SysInfo.h)