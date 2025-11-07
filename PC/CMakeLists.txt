cmake_minimum_required(VERSION 4.0.0)
project(AUGE VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# OpenCV Pfad (falls nötig)
set(OpenCV_DIR "C:/Users/Joel/Documents/EGK-Projekt/dependencies/opencv")
find_package(OpenCV REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(AUGE ${SOURCES})

# MinGW: statische Standardbibliotheken

message("Includes: ${OpenCV_INCLUDE_DIRS}")

# Include-Verzeichnisse
target_include_directories(AUGE PUBLIC 
    src/include 
    ${OpenCV_INCLUDE_DIRS}
)

# Link Libraries
target_link_libraries(AUGE PUBLIC ${OpenCV_LIBS})