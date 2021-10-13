### Set CMake
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(utilz)

### Set install directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
  message(STATUS "default install prefix set to: ${CMAKE_SOURCE_DIR}")
endif()

set(CMAKE_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)

### Concat headers into header-only lib
file(STRINGS "${CMAKE_SOURCE_DIR}/ZColors.hh" ZCOL_H)
file(STRINGS "${CMAKE_SOURCE_DIR}/DrawingUtils.hh" DRAW_H)

list(APPEND MY_LIBRARY_SINGLE
    "${ZCOL_H}"
    ""
    "${DRAW_H}"
)

file(REMOVE "${CMAKE_INSTALL_INCLUDE_DIR}/${PROJECT_NAME}.h")
foreach(LINE IN LISTS MY_LIBRARY_SINGLE)
    if(LINE MATCHES "#include \"")
        file(APPEND "${CMAKE_INSTALL_INCLUDE_DIR}/${PROJECT_NAME}.h" "// ${LINE}\n")
    else()
        file(APPEND "${CMAKE_INSTALL_INCLUDE_DIR}/${PROJECT_NAME}.h" "${LINE}\n")
    endif()
endforeach()

### 
configure_file( this_utilz.sh.in this_utilz.sh )
