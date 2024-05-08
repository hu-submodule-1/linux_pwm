cmake_minimum_required(VERSION 3.10)

# 定义静态库
add_library(linux_pwm STATIC pwm.c)

# 添加头文件搜索路径
target_include_directories(linux_pwm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
