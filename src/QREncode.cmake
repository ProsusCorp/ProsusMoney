
set(QRENCODE_LIB Qrencode)

file(GLOB QRENCODE_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} src/libqrencode/*.c)
list(REMOVE_ITEM QRENCODE_SOURCES src/libqrencode/qrenc.c)
file(GLOB QRENCODE_HEADERS src/libqrencode/*.h)

list(APPEND my_definitions "__STATIC=static")
list(APPEND my_definitions "STATIC_IN_RELEASE=static")
list(APPEND my_definitions "MAJOR_VERSION=3")
list(APPEND my_definitions "MINOR_VERSION=4")
list(APPEND my_definitions "MICRO_VERSION=0")
if(WIN32)
  list(APPEND my_definitions "inline=__inline")
endif(WIN32)
add_library(${QRENCODE_LIB} ${QRENCODE_SOURCES} ${QRENCODE_HEADERS})
set_target_properties(${QRENCODE_LIB} PROPERTIES COMPILE_DEFINITIONS "${my_definitions}")
