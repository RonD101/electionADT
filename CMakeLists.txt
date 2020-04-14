cmake_minimum_required(VERSION 3.15)
project(electionADT C)

set(CMAKE_C_STANDARD 99)

add_executable(electionADT main.c election.h election.c mtm_map/map.h mtm_map/map.c)