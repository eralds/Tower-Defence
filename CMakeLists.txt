cmake_minimum_required(VERSION 3.11)
project(MyGame)
include_directories("src")
# Set the name of the executable to be produced
set(EXECUTABLE_NAME MyGame)
# Use C++ standard version 17
set(CMAKE_CXX_STANDARD 17)
# Add all .cpp - files under src/ directory
file(GLOB SOURCES src/*.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCES})
# Download and build SFML and box2d
set(BUILD_SHARED_LIBS FALSE)
include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(sfml)
# Link with the libraries
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-audio sfml-network sfml-system)