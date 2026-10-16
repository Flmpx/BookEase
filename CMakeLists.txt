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
    GIT_TAG v0.2.1
)
FetchContent_MakeAvailable(flJson)


set(MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)      # 主程序入口
set(BASE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/base/base.cpp) # 基础类
set(MENU_SRC ${CMAKE_CURRENT_SOURCE_DIR}/menu/menu.cpp) # 菜单
file(GLOB TOOLS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/tools/src/*.cpp)    # 工具函数集合

set(PROCESS_LOGIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/process/login/login.cpp)      # 登录与注册
set(PROCESS_MAINPAGE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/process/mainpage/mainpage.cpp)  # 主界面
set(PROCESS_BUY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/process/buy/buy.cpp)        # 购买书籍
set(PROCESS_POST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/process/post/post.cpp)     # 发布书籍
set(PROCESS_MY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/process/my/my.cpp)           # 我的页
set(PROCESS_ABOUT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/process/about/about.cpp)  # 关于页
set(PROCESS_SETTINGS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/process/settings/settings.cpp)  # 设置

# 可执行文件输出到bin/目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Win32即使用Windows的窗口作为程序入口
add_executable(BookEase WIN32 ${MAIN_SRC} ${BASE_SRC} ${MENU_SRC} ${TOOLS_SRC} 
                              ${PROCESS_SAVELOAD_SRC} 
                              ${PROCESS_LOGIN_SRC} 
                              ${PROCESS_MAINPAGE_SRC}
                              ${PROCESS_MAINPAGE_SRC}
                              ${PROCESS_BUY_SRC}
                              ${PROCESS_POST_SRC}
                              ${PROCESS_MY_SRC}
                              ${PROCESS_ABOUT_SRC}
                              ${PROCESS_SETTINGS_SRC}
              )

# 链接EasyX
target_link_libraries(BookEase PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/easyx/lib/libeasyx.a")

# 链接flJson
target_link_libraries(BookEase PRIVATE flJson)

# 可以直接使用尖括号形式的EasyX的头文件
target_include_directories(BookEase PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/easyx/include")