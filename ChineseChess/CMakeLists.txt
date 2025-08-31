# 查找源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEAD "include/*.hpp")

# 定义库
add_library(ChineseChess SHARED)

target_sources(ChineseChess PRIVATE
        ${SOURCES}
        ${HEAD}
)

# 在项目中启用 GenerateExportHeader
include(GenerateExportHeader)

# 生成导出头文件
generate_export_header(ChineseChess
        EXPORT_FILE_NAME "lib_export.h"
)

# 指定头文件的位置
target_include_directories(ChineseChess
        PUBLIC
        include
        "${CMAKE_CURRENT_BINARY_DIR}"
)

## 定义 MYLIB_EXPORTS 宏，用于导出符号
#target_compile_definitions(ChineseChess PUBLIC ChineseChess_API)

# 设置库的输出目录（可选）
set_target_properties(ChineseChess PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)