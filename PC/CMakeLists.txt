cmake_minimum_required(VERSION 4.0.0)
project(AUGE VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp")

add_executable(AUGE ${SOURCES})

target_include_directories(AUGE PUBLIC 
    "${CMAKE_SOURCE_DIR}/src/include"
)