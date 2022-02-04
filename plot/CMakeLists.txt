### Concat headers into header-only lib
file(STRINGS "ZColors.hh" ZCOL_H)
file(STRINGS "DrawingUtils.hh" DRAW_H)

list(APPEND MY_LIBRARY_SINGLE
    "${ZCOL_H}"
    ""
    "${DRAW_H}"
)

file(REMOVE "${CMAKE_INSTALL_INCLUDE_DIR}/DrawingUtils.h")
foreach(LINE IN LISTS MY_LIBRARY_SINGLE)
    if(LINE MATCHES "#include \"")
        file(APPEND "${CMAKE_INSTALL_INCLUDE_DIR}/DrawingUtils.h" "// ${LINE}\n")
    else()
        file(APPEND "${CMAKE_INSTALL_INCLUDE_DIR}/DrawingUtils.h" "${LINE}\n")
    endif()
endforeach()
