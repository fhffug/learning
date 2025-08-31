cmake_minimum_required(VERSION 3.31)
project(AIcpp VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # 禁用编译器扩展

# 添加可执行文件
add_executable(Main main.cpp)

# 指定 MyLibrary 的路径
add_subdirectory(DeepLearning)
add_subdirectory(ChineseChess)

# 链接 MyLibrary
target_link_libraries(Main PUBLIC
        DeepLearning
        ChineseChess
)

# 设置可执行文件的运行目录，以便找到 DLL
set_target_properties(Main PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 编译器优化
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    #    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
    #    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -mtune=native")
    #    set(CMAKE_C_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -march=native -mtune=native")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -mtune=native")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O3 -march=native -mtune=native")
    set(CMAKE_C_FLAGS_RELEASE "-O3 -march=native -mtune=native")
elseif (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /arch:AVX2")
    set(CMAKE_C_FLAGS_RELEASE "/O2")
endif ()

# 并行构建配置
if (MSVC)
    add_compile_options(/MP)  # 多核编译
    set(CMAKE_VS_BUILD_PARALLEL_LEVEL 8)  # 解决方案并行任务数
else ()
    # 并行构建
    include(ProcessorCount)
    ProcessorCount(N)
    if (N EQUAL 0)
        set(N 1)
    endif ()
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})    # Ninja/Make并行任务数
endif ()

# 链接时优化
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

# 链接器优化
#target_link_options(Main PRIVATE
#        -s  # 删除符号表（Release模式）
#)