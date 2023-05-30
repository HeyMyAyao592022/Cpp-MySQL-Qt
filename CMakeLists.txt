cmake_minimum_required(VERSION 3.0.0)
project(sql_c++ VERSION 0.1.0)

include(CTest)
enable_testing()

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

add_executable(sql_c++ ${src_dirs})

target_link_libraries(sql_c++ ${PROJECT_SOURCE_DIR}/lib/libmysql.lib ${PROJECT_SOURCE_DIR}/lib/libmysql.dll)

if(WINDOWS)
    add_custom_command(TARGET sql_c++ POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/lib/libmysql.dll ${PROJECT_SOURCE_DIR}/build)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
