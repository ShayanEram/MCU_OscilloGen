cmake_minimum_required(VERSION 3.10)
project(UnitTests)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest
add_subdirectory(../../googletest googletest-build)

# Gather test sources and mocks
file(GLOB TEST_SOURCES "*.cpp")
file(GLOB MOCK_SOURCES "Mocks/*.cpp")
file(GLOB HEADER_FILES "../Project/Core++/*.hpp")

# Create test executable
add_executable(UnitTests ${TEST_SOURCES} ${MOCK_SOURCES} ${HEADER_FILES})

# Include directories for headers and mocks
target_include_directories(UnitTests
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Mocks
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../Project/Core++
)

# Link GoogleTest
target_link_libraries(UnitTests gtest gtest_main pthread)

enable_testing()
add_test(NAME UnitTests COMMAND UnitTests)