cmake_minimum_required(VERSION 4.0.0)
project(AUGE VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(PC      "${CMAKE_SOURCE_DIR}/PC")
set(SHARED  "${CMAKE_SOURCE_DIR}/shared")
set(ARDUINO "${CMAKE_SOURCE_DIR}/Arduino")

file(GLOB SOURCES
    "${PC}/src/*.cpp"
    "${SHARED}/src/*.cpp"
)

add_executable(AUGE ${SOURCES})

target_include_directories(AUGE PUBLIC 
    "${PC}/include"
    "${SHARED}/include"
)