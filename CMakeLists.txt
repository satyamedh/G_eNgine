cmake_minimum_required(VERSION 4.1)
project(G_eNgine)

cmake_policy(SET CMP0069 NEW) # for flto check_ipo_supported

include(CheckIPOSupported)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

add_executable(G_eNgine main.cpp
        events/EventHandler.h
        events/EventManager.cpp
        events/EventManager.h
        events/EventQueue.h
        events/EventType.h
        events/EventGlobals.cpp
        events/EventGlobals.h
        events/SDLEvents/SDLEvents.cpp
        events/SDLEvents/SDLEvents.h
        GameEngineGlobals.cpp
        GameEngineGlobals.h
)
TARGET_LINK_LIBRARIES(G_eNgine ${SDL2_LIBRARIES} spdlog::spdlog fmt::fmt)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(G_eNgine PRIVATE DEBUG=1)
endif()

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



