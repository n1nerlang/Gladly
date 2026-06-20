cmake_minimum_required(VERSION 3.10)
project(GladlyEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(core/include)

# Source files for the engine library (excluding main test)
set(ENGINE_SOURCES
    core/src/Chunk.cpp
    core/src/ChunkFactory.cpp
    core/src/CloudGenerator.cpp
    core/src/WorldGenerator.cpp
)

add_library(gladly_engine ${ENGINE_SOURCES})

# Test application
add_executable(gladly_test core/src/main_test.cpp)
target_link_libraries(gladly_test gladly_engine)
