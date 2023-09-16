cmake_minimum_required(VERSION 3.5.1)

project(hbt)


# 输出测试
message("hbt")

set(CMAKE_CXX_FLAGS "-fpermissive")


file(GLOB hbt_src "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/help/*.c"
    "${PROJECT_SOURCE_DIR}/src/common/*.c"
    "${PROJECT_SOURCE_DIR}/src/hex/*.c"
    "${PROJECT_SOURCE_DIR}/src/hex2bin/*.c"
)


#设定头文件路�?
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/help"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/common"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/hex"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/hex2bin"
)


add_executable(hbt ${hbt_src})

