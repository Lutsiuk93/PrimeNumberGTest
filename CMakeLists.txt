cmake_minimum_required(VERSION 3.14)

project(PrimeNumber LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GenerateExportHeader)
set(EXPORT_HEADER_DIR ${CMAKE_CURRENT_BINARY_DIR}/exports)
include_directories(${EXPORT_HEADER_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

include(FetchContent)
FetchContent_Declare(
  googletest
  googlemock
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
#FetchContent_MakeAvailable(googlemock)

add_subdirectory(PrimeNumber.Core)
add_subdirectory(PrimeNumber.UnitTests)
