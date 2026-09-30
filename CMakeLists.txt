cmake_minimum_required(VERSION 3.28.3)

project(BookEase)

# 让VS Code的C/C++插件识别以便提供代码补全等功能
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BOOKEASE_USE_SSH_FOR_GIT OFF)

if(BOOKEASE_USE_SSH_FOR_GIT)
    set(FLJONS_USE_SSH_FOR_GIT ON)
    set(BOOKEASE_DEPEND_LINK "git@github.com:Flmpx/flJson.git")
else()
    set(BOOKEASE_DEPEND_LINK "https://github.com/Flmpx/flJson.git")    
endif()

# 使用flJson作为Json解析器
include(FetchContent)
FetchContent_Declare(
    flJson
    GIT_REPOSITORY ${BOOKEASE_DEPEND_LINK}
    GIT_TAG ea1ab1f8c3aa4b7c81a514cbbade7711e265bf05
)
FetchContent_MakeAvailable(flJson)


set(FUNCTIONS_SRC "function/function.cpp")	    # 调用工具函数
file(GLOB_RECURSE LIST_SRC "Lists/*.cpp")       # 链表
file(GLOB_RECURSE MENU_SRC "menu/*.cpp")        # 各级菜单
file(GLOB_RECURSE PROCESS_SRC "Process/*.cpp")  # 主要流程
set(SORT_CMP "sort/sort.cpp")                   #排序的比较函数 
set(BASE_SRC "base.cpp")                        # 基础功能
set(MAIN_SRC "main.cpp")                        # 程序入口

# 可执行文件输出到bin/目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Win32即使用Windows的窗口作为程序入口
add_executable(BookEase WIN32 ${FUNCTIONS_SRC} ${MENU_SRC} ${PROCESS_SRC} ${LIST_SRC} ${SORT_CMP} ${BASE_SRC} ${MAIN_SRC})

# 链接EasyX
target_link_libraries(BookEase PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/easyx/lib/libeasyx.a")

# 链接flJson
target_link_libraries(BookEase PRIVATE flJson)

# 可以直接使用尖括号形式的EasyX的头文件
target_include_directories(BookEase PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/easyx/include")