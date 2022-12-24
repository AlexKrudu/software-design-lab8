cmake_minimum_required(VERSION 3.21)
project(software_design_lab8)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(google_tests)
add_executable(software_design_lab8 main.cpp clock.h real_clock.h mockable_clock.h event_statistics.h event_statistics_impl.h event_statistics_impl.cpp)
