cmake_minimum_required(VERSION 3.5)
project(ColibriClient)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")

#include_directories(${MyProject_SOURCE_DIR}/include)
include_directories(./include)
include_directories(/usr/include)

link_directories(/usr/lib/x86_64-linux-gnu)

file(GLOB SOURCES "src/*.cpp")
file(GLOB ControllerSrc "src/Controller/*.cpp")
file(GLOB ModelSrc "src/Model/*.cpp")
file(GLOB ViewSrc "src/View/*.cpp")

add_executable(colibriClient ${SOURCES} ${ControllerSrc} ${ModelSrc} ${ViewSrc})

target_link_libraries(colibriClient SDL2 SDL2_ttf boost_system pthread)