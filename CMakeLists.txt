project(TareaTopicos)

cmake_minimum_required(VERSION 2.4)

set(CMAKE_BUILD_TYPE Release)

include_directories(smhasher/src/ etl/include/)

add_executable(
  proyecto1_topicos
  main.cpp
  smhasher/src/MurmurHash3.cpp
)

