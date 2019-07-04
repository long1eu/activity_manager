cmake_minimum_required(VERSION 3.5)
project(activity_manager)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_LINK_FLAGS "-lncurses")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(
        activity_manager
        main.cpp
        models/Process.cpp
        models/Process.h
        models/ProcessParser.cpp
        models/ProcessParser.h
        models/ProcessContainer.cpp
        models/ProcessContainer.h
        models/SysInfo.cpp
        models/SysInfo.h
        utils/constants.h
        utils/Util.h
        utils/Util.cpp)

target_link_libraries(lncurses)