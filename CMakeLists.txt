cmake_minimum_required(VERSION 3.5)
project(netgame VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
else ()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif ()

include(cmake/CPM.cmake)

add_executable(netgame
        src/main.cpp
        src/actor.h
        "src/game/card.cpp"
        "src/game/card.h"
        "src/networker.cpp"
        "src/networker.h" 
        "src/state.h" 
        "src/state.cpp" 
        "src/game.h"
        "src/game.cpp"
        "src/renderer.cpp"
        "src/renderer.h"
        "src/simplesock/socklib_generic.cpp"
        "src/simplesock/pool.cpp"
        "src/eventqueue.h" 
        "src/eventqueue.cpp"
        "src/lobby/nameentry.cpp"
        "src/lobby/nameentry.h"
        "src/input.h"
        "src/input.cpp"



)

if (WIN32)
    target_sources(netgame PRIVATE "src/simplesock/socklib_win32.cpp")
endif()

if (UNIX)
    target_sources(netgame PRIVATE "src/simplesock/socklib_posix.cpp")
endif()

set(BUILD_EXAMPLE "")
set(BUILD_EXAMPLES OFF)
add_subdirectory(external/raylib)

target_include_directories(netgame PUBLIC src/simplesock)

target_link_libraries(netgame PRIVATE raylib)

if (WIN32)
    file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/Debug/assets)
    add_custom_target(copy_assets
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/Debug/assets
    )
    add_dependencies(netgame copy_assets)
endif()

if (UNIX)
    file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/assets)
    add_custom_target(copy_assets
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
    )
    add_dependencies(netgame copy_assets)
endif()