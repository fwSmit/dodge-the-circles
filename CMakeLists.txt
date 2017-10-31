cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project (dodge)

set (CMAKE_CXX_STANDARD 11)

set (dodge_SRC source.cpp functions.cpp PhysicsCircle.cpp)

option(IS_LIBRARY "Should dodge be compiled as library?")

if(IS_LIBRARY)
#when used as library
message("setting dodge up as library")
include_directories(${CMAKE_SOURCE_DIR}/dependencies/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/dodge-the-circles)
add_library(dodge SHARED ${dodge_SRC})
else()
#when used as standalone executable
message("setting dodge up as executable")
include_directories(${CMAKE_SOURCE_DIR})
add_executable(dodge ${dodge_SRC})
endif()



#armadillo library
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})


#include the necessary libraries
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(TGUI 0.7 REQUIRED)

if(NOT SFML_FOUND)
    message(FATAL_ERROR "Could not find SFML")
endif()

if(NOT TGUI_FOUND)
    message(FATAL_ERROR "Could not find TGUI")
endif()

include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(dodge ${SFML_LIBRARIES} ${TGUI_LIBRARY} ${ARMADILLO_LIBRARIES})
