cmake_minimum_required(VERSION 3.24)
project(matrix_pipeline_tests LANGUAGES CXX)

enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(mp_logic_tests statistics_test.cpp)
target_compile_features(mp_logic_tests PRIVATE cxx_std_17)
target_compile_definitions(mp_logic_tests PRIVATE _GLIBCXX_ASSERTIONS)
target_include_directories(mp_logic_tests PRIVATE ../src/matrix-pipeline)
target_link_libraries(mp_logic_tests PRIVATE GTest::gtest_main)

gtest_discover_tests(mp_logic_tests)
