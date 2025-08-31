# 查找源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEAD "include/*.hpp")

# 定义库
add_library(DeepLearning SHARED)

target_sources(DeepLearning PRIVATE
        ${SOURCES}
        ${HEAD}
)

# 在项目中启用 GenerateExportHeader
include(GenerateExportHeader)

# 生成导出头文件
generate_export_header(DeepLearning
        EXPORT_FILE_NAME "lib_export.h"
)

# 指定头文件的位置
target_include_directories(DeepLearning
        PUBLIC
        include
        "${CMAKE_CURRENT_BINARY_DIR}"
)

## 定义 MYLIB_EXPORTS 宏，用于导出符号
#target_compile_definitions(DeepLearning PUBLIC DeepLearning_API)
# 设置预编译头文件
target_precompile_headers(DeepLearning PUBLIC
        include/pch.h
)

# 设置库的输出目录（可选）
set_target_properties(DeepLearning PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(DeepLearning PUBLIC Eigen3::Eigen)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(DeepLearning PUBLIC nlohmann_json::nlohmann_json)
