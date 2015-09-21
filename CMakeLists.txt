cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
project(YAGUI CXX C)

message(status ${CMAKE_INCLUDE_PATH})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfatal-errors ")
set(CMAKE_CXX_FLAGS_RELEASE "")

if(PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
   message(FATAL_ERROR "In-tree build attempt detected, aborting. Set your build dir outside your source dir, delete CMakeCache.txt from source root and try again.")
endif()


if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR CMAKE_COMPILER_IS_GNUCXX)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag(-std=c++11 SUPPORTS_STD_CXX11)
    check_cxx_compiler_flag(-std=c++0x SUPPORTS_STD_CXX01)
    if(SUPPORTS_STD_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11")
    elseif(SUPPORTS_STD_CXX01)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++0x")
    else()
        message(ERROR "Compiler does not support -std=c++11 or -std=c++0x.")
    endif()
endif()

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})
set(CMAKE_BUILD_TYPE Release)




FIND_PACKAGE(OpenGL)
IF(OPENGL_FOUND)
  MESSAGE(STATUS "OpenGL render API found.")
  MESSAGE(STATUS "Detected OpenGL path is : ${OPENGL_LIBRARIES}")
ENDIF(OPENGL_FOUND)

FIND_PACKAGE(GLEW)
IF(GLEW_FOUND)
  MESSAGE(STATUS "GLEW found.")
  MESSAGE(STATUS "Detected GLEW path is : ${GLEW_LIBRARIES}")
ENDIF(GLEW_FOUND)


include_directories(include)


file(
        GLOB_RECURSE
        source_files
        source/*
        include/*
)



if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(ADDITIONAL_LIBS "mingw32")
endif()

add_library(YAGUI ${source_files})
target_link_libraries(YAGUI m ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${ADDITIONAL_LIBS} SDL2 SDL2main)
add_executable(YAGUI_Example example/main.cpp)
target_link_libraries(YAGUI_Example m ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${ADDITIONAL_LIBS} SDL2 SDL2main YAGUI)


set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)