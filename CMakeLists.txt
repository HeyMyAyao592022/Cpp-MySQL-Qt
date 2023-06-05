cmake_minimum_required(VERSION 3.0.0)
project(sql_c++ VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_PREFIX_PATH "D:/Qt/5.14.2/mingw73_64")
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Concurrent)

# Check platforms
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src src_dirs)

add_executable(sql_c++ ${src_dirs} ${PROJECT_SOURCE_DIR}/include/mainwindow.h ${PROJECT_SOURCE_DIR}/src/mainwindow.ui)

target_link_libraries(sql_c++ PUBLIC ${PROJECT_SOURCE_DIR}/lib/libmysql.lib ${PROJECT_SOURCE_DIR}/lib/libmysql.dll 
 PRIVATE Qt5::Widgets Qt5::Core Qt5::Concurrent)

if(WINDOWS)
    add_custom_command(TARGET sql_c++ POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/lib/libmysql.dll ${PROJECT_SOURCE_DIR}/build)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
