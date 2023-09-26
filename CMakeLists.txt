project(TareaTopicos)

cmake_minimum_required(VERSION 2.4)

set(CMAKE_BUILD_TYPE Debug)

include_directories(smhasher/src/)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_CFLAGS} -Og -g -ggdb3")

add_executable(
        proyecto1_topicos

        Sketch.h
        ElasticSketch.h

        CountMin.h
        CountMin.cpp

        CountMinCU.h
        CountMinCU.cpp
        ElasticSketch.cpp

        main.cpp
        smhasher/src/MurmurHash3.cpp
)

# target_link_libraries(proyecto1_topicos proyecto1_lib)

