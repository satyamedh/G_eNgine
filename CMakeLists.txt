cmake_minimum_required(VERSION 4.1)
project(G_eNgine)

cmake_policy(SET CMP0069 NEW) # for flto check_ipo_supported

include(CheckIPOSupported)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(G_eNgine main.cpp)
TARGET_LINK_LIBRARIES(G_eNgine ${SDL2_LIBRARIES})


# Compiler options
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(G_eNgine PRIVATE -O3) # WE NEED ZE PERFORMANCE!

    # flto
    check_ipo_supported(RESULT lto_supported OUTPUT lto_error)
    if(lto_supported)
        set_property(TARGET G_eNgine PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(WARNING "LTO NOT SUPPORTED!: ${lto_error}")
    endif()
endif ()



