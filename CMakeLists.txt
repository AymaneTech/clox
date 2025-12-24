cmake_minimum_required(VERSION 3.10)
project(clox C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter -g")

# Source files
set(CLOX_SOURCES
    src/scanner.c
    src/chunk.c
    src/compiler.c
    src/debug.c
    src/memory.c
    src/value.c
    src/vm.c
    src/object.c
    src/table.c
)

# Main executable
add_executable(clox src/main.c ${CLOX_SOURCES})
target_include_directories(clox PRIVATE ${CMAKE_SOURCE_DIR})

# Test executable
set(TEST_SOURCES
    tests/scanner_test.c
    tests/compiler_test.c
)

add_executable(test_runner ${TEST_SOURCES} ${CLOX_SOURCES})
target_include_directories(test_runner PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test_runner criterion)
