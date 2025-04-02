cmake_minimum_required(VERSION 3.22)
# cmake 最小版本

project(arpc)
# 项目名称
set(CMAKE_VERBOSE_MAKEFILE ON)
# 开启详细输出
set(CMAKE_CXX_FLAGS 
        "$ENV{CXXFLAGS} \
        -rdynamic \
        -O3 \
        -g \
        -std=c++11 \
        -lpthread \
        -Wall \
        -Wno-deprecated \
        -Werror \
        -Wno-dev \
        -Wno-unused-function"
        )
# -rdynamic: 将所有符号添加到动态符号表中，有助于调试
# -O3: 高级优化级别
# -g: 生成调试信息
# -std=c++11: 使用 C++11 标准
# -lpthread: 链接 pthread 库（注意：这应该放在 target_link_libraries 中而不是编译选项中）
# -Wall: 启用所有警告
# -Wno-deprecated: 不显示关于弃用特性的警告
# -Werror: 将警告视为错误
# -Wno-dev: 禁用开发者警告
# -Wno-unused-function: 不显示未使用函数的警告

set(LIB_SRC src/net/reactor.cc)
# 指定库源文件

add_library(arpc SHARED ${LIB_SRC})
# 创建一个叫做arpc的动态库

set(LIBS arpc)
# 定义变量 包含这个动态库

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
# 可执行文件或者库的输出路径