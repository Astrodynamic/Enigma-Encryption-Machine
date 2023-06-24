cmake_minimum_required(VERSION 3.5)

project(Enigma VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
  ${CMAKE_SOURCE_DIR}/ainterface
  ${CMAKE_SOURCE_DIR}/interface
  ${CMAKE_SOURCE_DIR}/primitive
  ${CMAKE_SOURCE_DIR}/reflector
  ${CMAKE_SOURCE_DIR}/machine
  ${CMAKE_SOURCE_DIR}/rotor
)

set(HEADERS
  ainterface/ainterface.h
  primitive/primitive.h
  reflector/reflector.h
  interface/interface.h
  machine/machine.h
  rotor/rotor.h
)

set(SOURCES
  ainterface/ainterface.cc
  primitive/primitive.cc
  reflector/reflector.cc
  interface/interface.cc
  machine/machine.cc
  rotor/rotor.cc
)

add_executable(
  ${PROJECT_NAME}
  ${HEADERS}
  ${SOURCES}
  main.cc
)

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE
  -Wall
  -Werror
  -Wextra
  -Wpedantic
  -fsanitize=address
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  -fsanitize=address
)