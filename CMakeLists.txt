# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project(boost)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(./asio DIR_SRCS)

# 添加头文件目录
#include_directories(D:\\ProgramTool\\boost_1_73_0)

# 添加需要链接的库文件目录
#link_directories(D:\\ProgramTool\\boost_1_73_0\\stage\\lib)

# 添加 math 子目录
# add_subdirectory(asio)

# 指定生成目标 
# add_executable(${PROJECT_NAME}.out asio/timer01.cpp)

# 指定可执行文件和lib文件目录
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

# If necessary, use the RELATIVE flag, otherwise each source file may be listed 
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
# file( GLOB APP_SOURCES RELATIVE app/*.cxx )
# get_filename_component(<var> <FileName> <mode> [CACHE])

file( GLOB APP_SOURCES RELATIVE_PATH SkipList/*.cpp)
foreach( testsourcefile ${APP_SOURCES} )
    # I used a simple string replace, to cut off .cpp.
    # string( REPLACE ".cpp" "" testname ${testsourcefile} )
    get_filename_component(testname ${testsourcefile} NAME_WE)
    add_executable( ${testname}.out ${testsourcefile} )
    # Make sure YourLib is linked to each app
    # 添加链接库
    # target_link_libraries(${testname}.out pthread)
    # target_link_libraries(${testname}.out boost_chrono)
endforeach( testsourcefile ${APP_SOURCES} )