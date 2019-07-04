cmake_minimum_required(VERSION 3.5)
project(activity_manager)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        activity_manager
        main.cpp
        models/Process.h
        models/ProcessParser.h
        models/ProcessContainer.h
        models/SysInfo.h
        utils/constants.h
        utils/util.h
)