cmake_minimum_required(VERSION 3.4.1)

add_library(
Algorithm SHARED
Algorithm.c
calculate_noConv.c
calculate_noConv_emxAPI.c
calculate_noConv_emxutil.c
calculate_noConv_initialize.c
calculate_noConv_terminate.c
calculate_noConv_types.h
rtwtypes.h
)
target_link_libraries(
Algorithm
android
log)