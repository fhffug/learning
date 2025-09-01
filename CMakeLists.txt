cmake_minimum_required(VERSION 3.31)
project(AIcpp VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # 禁用编译器扩展

# 设置构建类型
set(CMAKE_BUILD_TYPE Debug)

# 编译器特定设置
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMMON_WARNINGS
            -Wall -Wextra -Wpedantic
            -Wshadow -Wnon-virtual-dtor -Wold-style-cast
            -Wcast-align -Wunused -Woverloaded-virtual
            -Wconversion -Wsign-conversion
            -Wnull-dereference -Wdouble-promotion
            -Wformat=2 -Wimplicit-fallthrough
    )

    set(GCC_WARNINGS
            -Wlogical-op -Wuseless-cast -Wduplicated-cond
            -Wduplicated-branches -Wrestrict
    )

    # Debug 配置
    set(CMAKE_CXX_FLAGS_DEBUG
            "${CMAKE_CXX_FLAGS_DEBUG} -Og -g3"
    )

    # Release 配置
    set(CMAKE_CXX_FLAGS_RELEASE
            "-O3 -DNDEBUG"
    )

    # 添加警告选项
    add_compile_options(${COMMON_WARNINGS} ${GCC_WARNINGS})

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMMON_WARNINGS
            -Wall -Wextra -Wpedantic
            -Wshadow -Wnon-virtual-dtor -Wold-style-cast
            -Wcast-align -Wunused -Woverloaded-virtual
            -Wconversion -Wsign-conversion
            -Wnull-dereference -Wdouble-promotion
            -Wformat=2 -Wimplicit-fallthrough
    )

    set(CLANG_WARNINGS
            -Wmost -Wdocumentation -Wdocumentation-unknown-command
            -Wmissing-prototypes -Wimplicit-atomic-properties
    )

    # Debug 配置
    set(CMAKE_CXX_FLAGS_DEBUG
            "${CMAKE_CXX_FLAGS_DEBUG} -Og -g3"
    )

    # Release 配置
    set(CMAKE_CXX_FLAGS_RELEASE
            "-O3 -DNDEBUG"
    )

    # 添加警告选项
    add_compile_options(${COMMON_WARNINGS} ${CLANG_WARNINGS})

elseif (MSVC)
    set(MSVC_WARNINGS
            /W4  # 启用大多数警告
            /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296
            /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619
            /w14640 /w14826 /w14905 /w14906 /w14928
    )

    # Debug 配置
    set(CMAKE_CXX_FLAGS_DEBUG
            "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi"
    )

    # Release 配置
    set(CMAKE_CXX_FLAGS_RELEASE
            "/O2 /DNDEBUG"
    )

    # 添加警告选项
    add_compile_options(${MSVC_WARNINGS})
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
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})  # Ninja/Make并行任务数
endif ()

# 链接时优化
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)  # 默认关闭，可在Release中开启

# 添加子目录
add_subdirectory(DeepLearning)
#add_subdirectory(ChineseChess)

# 添加可执行文件
add_executable(Main main.cpp resources/app.o)

# 链接库
target_link_libraries(Main PUBLIC
        DeepLearning
        #        ChineseChess
)

# 设置可执行文件的运行目录
set_target_properties(Main PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 目标特定设置
target_compile_features(Main PRIVATE cxx_std_23)

# Release 特定配置
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(Main PROPERTIES
            INTERPROCEDURAL_OPTIMIZATION ON
    )
endif ()
