cmake_minimum_required(VERSION 3.28.3)

project(BookEase)

# 让VS Code的C/C++插件识别以便提供代码补全等功能
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 使用CXX20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BOOKEASE_USE_SSH_FOR_GIT OFF)

if(BOOKEASE_USE_SSH_FOR_GIT)
    set(FLJONS_USE_SSH_FOR_GIT ON CACHE BOOL "" FORCE)
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


set(MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)      # 主程序入口
set(BASE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/base/base.cpp) # 基础类
set(MENU_SRC ${CMAKE_CURRENT_SOURCE_DIR}/menu/menu.cpp) # 菜单
set(TOOLS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/tools/tools.cpp)  # 工具函数集合

set(PROCESS_SAVELOAD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/process/saveandload/saveandload.cpp)  # 文件持久化
set(PROCESS_LOGIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/process/login/login.cpp)      # 登录与注册

# 可执行文件输出到bin/目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Win32即使用Windows的窗口作为程序入口
add_executable(BookEase WIN32 ${MAIN_SRC} ${BASE_SRC} ${MENU_SRC} ${TOOLS_SRC} ${PROCESS_SAVELOAD_SRC} ${PROCESS_LOGIN_SRC})

# 链接EasyX
target_link_libraries(BookEase PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/easyx/lib/libeasyx.a")

# 链接flJson
target_link_libraries(BookEase PRIVATE flJson)

# 可以直接使用尖括号形式的EasyX的头文件
target_include_directories(BookEase PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/easyx/include")