cmake_minimum_required(VERSION 3.14)
project(sli_firmware_test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Ofast -Wno-dev)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include_directories(../Drivers/sl_i/Inc)
include_directories("${gtest_SOURCE_DIR}/include")
file(GLOB_RECURSE SOURCES "../Drivers/sl_i/Src/*.c" "./*.cc")
list(REMOVE_ITEM SOURCES "../Drivers/sl_i/Src/bsp.c")
add_executable(
  ${PROJECT_NAME}
  ${SOURCES}
)

target_link_libraries(
  ${PROJECT_NAME}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

