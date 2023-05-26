set(ENGINE_ROOT_DIR "${KRATOS_ROOT_DIR}/engine")
set(THIRD_PARTY_DIR  "${ENGINE_ROOT_DIR}/3rdparty")

set(DEVELOP_CONFIG_DIR "config/development")

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/MP")
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT KratosEditor)
endif()

add_subdirectory(3rdparty)
add_subdirectory(source/runtime)
add_subdirectory(source/editor)

set(CODEGEN_TARGET "KratosPreCompile")
include(source/precompile/precompile.cmake)
set_target_properties("${CODEGEN_TARGET}" PROPERTIES FOLDER "Engine" )

add_dependencies(KratosRuntime "${CODEGEN_TARGET}")