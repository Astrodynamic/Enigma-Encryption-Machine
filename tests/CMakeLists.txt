cmake_minimum_required(VERSION 3.5)
project(TEST VERSION 1.0 LANGUAGES CXX)

#=============================================================== Setup CMake
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS --coverage)
set(CMAKE_EXE_LINKER_FLAGS --coverage)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(
  ${PROJECT_SOURCE_DIR}/../primitive
  ${PROJECT_SOURCE_DIR}/../reflector
  ${PROJECT_SOURCE_DIR}/../machine
  ${PROJECT_SOURCE_DIR}/../rotor
)

set(HEADERS
  ../primitive/primitive.h
  ../reflector/reflector.h
  ../machine/machine.h
  ../rotor/rotor.h
)

set(SOURCES
  ../primitive/primitive.cc
  ../reflector/reflector.cc
  ../machine/machine.cc
  ../rotor/rotor.cc
)

enable_testing()

add_executable(
  ${PROJECT_NAME}
  ${HEADERS}
  ${SOURCES}
  test.cc
)

configure_file(${CMAKE_SOURCE_DIR}/config ${CMAKE_BINARY_DIR}/config COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/file ${CMAKE_BINARY_DIR}/file COPYONLY)

target_link_libraries(${PROJECT_NAME}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})