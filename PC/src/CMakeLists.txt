cmake_minimum_required(VERSION 3.15)

# Projektname und Sprache
project(MyOpenCVProject LANGUAGES CXX)

# C++-Standard (z. B. C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include-Verzeichnis (lokal)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Finde OpenCV (muss in PATH oder CMAKE_PREFIX_PATH liegen)
find_package(OpenCV REQUIRED)

# Quelle(n) angeben
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# OpenCV-Header und Libs verlinken
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

# Optional: Ausgabeordner festlegen
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)