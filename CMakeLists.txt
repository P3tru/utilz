### Set CMake
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(utilz)

### Set install directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
  message(STATUS "default install prefix set to: ${CMAKE_SOURCE_DIR}")
endif()

### Header-only install dir inside include/
set(CMAKE_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)

### Set lib dir
set(DIR_PLOT ${CMAKE_SOURCE_DIR}/plot)
set(DIR_GENE ${CMAKE_SOURCE_DIR}/generic)
set(DIR_MATH ${CMAKE_SOURCE_DIR}/math)

add_subdirectory(${DIR_PLOT})
add_subdirectory(${DIR_MATH})

### 
configure_file( this_utilz.sh.in this_utilz.sh )
