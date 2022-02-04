### Concat headers into header-only lib
file(STRINGS "BoxBnds.hh" BB_H)
file(STRINGS "CylBnds.hh" CB_H)
file(STRINGS "Fit.hh" FI_H)
file(STRINGS "Hist.hh" HI_H)
file(STRINGS "Matrix.hh" MA_H)
file(STRINGS "NLL.hh" NL_H)
file(STRINGS "Sensitivity.hh" SI_H)
file(STRINGS "TBnds.hh" TB_H)

file(STRINGS "MathUtils.hh" LIB_H)

list(APPEND MY_LIBRARY_SINGLE
    "${BB_H}"
    "${CB_H}"
    "${FI_H}"
    "${HI_H}"
    "${MA_H}"
    "${NL_H}"
    "${SI_H}"
    "${TB_H}"
    ""
    "${LIB_H}"
)

file(REMOVE "${CMAKE_INSTALL_INCLUDE_DIR}/MathUtils.h")
foreach(LINE IN LISTS MY_LIBRARY_SINGLE)
    if(LINE MATCHES "#include \"")
        file(APPEND "${CMAKE_INSTALL_INCLUDE_DIR}/MathUtils.h" "// ${LINE}\n")
    else()
        file(APPEND "${CMAKE_INSTALL_INCLUDE_DIR}/MathUtils.h" "${LINE}\n")
    endif()
endforeach()
