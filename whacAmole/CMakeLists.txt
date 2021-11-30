cmake_minimum_required(VERSION 3.20)
project(whacAmole)

set(OpenGlLinkers -lglut -lGLU -lGL)

add_executable(whacAmole main.cpp)

target_link_libraries(whacAmole ${OpenGlLinkers})
