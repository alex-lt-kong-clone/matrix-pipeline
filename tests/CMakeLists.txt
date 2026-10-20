cmake_minimum_required(VERSION 3.24)
project(matrix_pipeline_tests LANGUAGES CXX)

enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
