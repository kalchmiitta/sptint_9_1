cmake_minimum_required(VERSION 3.21)
project(transport_cat)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(transport_cat
        geo.h
        input_reader.cpp
        input_reader.h
        main.cpp
        stat_reader.cpp
        stat_reader.h
        transport_catalogue.cpp
        transport_catalogue.h)
