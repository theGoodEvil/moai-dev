cmake_minimum_required ( VERSION 2.8.5 )
project ( tge-exetnsions )

set ( TGE_EXTENSIONS_INCLUDES "${MOAI_ROOT}/src/;${MOAI_ROOT}/config/;${MOAI_ROOT}/src/config-default/;${MOAI_ROOT}/3rdparty/LuaJIT-2.0.3/src/;${MOAI_ROOT}/3rdparty/tinyxml/;${MOAI_ROOT}/3rdparty/expat-2.0.1/lib" CACHE INTERNAL "doc string" )

include_directories ( 
  ${MOAICORE_INCLUDES} 
  ${TGE_EXTENSIONS_INCLUDES} 
)

set ( CMAKE_CURRENT_SOURCE_DIR "${MOAI_ROOT}/src/tge-extensions/" )
file ( GLOB SRC_TGE_EXTENSIONS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )
add_library ( tge-extensions STATIC ${SRC_TGE_EXTENSIONS} )

target_include_directories (tge-extensions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
