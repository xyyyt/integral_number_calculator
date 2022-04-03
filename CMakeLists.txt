cmake_minimum_required(VERSION 3.0)
project(integral_number_calculator)

IF (${CMAKE_BUILD_TYPE} MATCHES "debug")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/debug)
  add_definitions(-g -W -Wall -Wextra -std=c++17)
ELSE ()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/release)
  add_definitions(-W -Wall -Wextra -std=c++17)
ENDIF()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/utils
  ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic)


# calculator executable

add_executable(calculator
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/arithmetic_expression_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/reverse_polish_notation.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/arithmetic_operation.cpp)


# test

set(RUNTIME_OUTPUT_DIRECTORY_TEST ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)

include(CTest)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test/utils)

## google-test
set(GTEST_ROOT "/usr/src/googletest/googletest")
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

## google-mock
set(GMOCK_LIBRARIES "/usr/lib/libgmock.a")
set(GMOCK_INCLUDE_DIRS "/usr/src/googletest/googlemock/include")
include_directories(${GMOCK_INCLUDE_DIRS})


## unit tests

### arithmetic_expression_parser_test executable

add_executable(arithmetic_expression_parser_test
  ${CMAKE_CURRENT_SOURCE_DIR}/test/src/arithmetic/arithmetic_expression_parser_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/arithmetic_expression_parser.cpp)

target_link_libraries(arithmetic_expression_parser_test
  ${GTEST_LIBRARIES}
  ${GMOCK_LIBRARIES}
  pthread)

set_target_properties(arithmetic_expression_parser_test
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_TEST})

add_test(NAME arithmetic_expression_parser_test
  COMMAND arithmetic_expression_parser_test
  WORKING_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_TEST})


### reverse_polish_notation_test executable

add_executable(reverse_polish_notation_test
  ${CMAKE_CURRENT_SOURCE_DIR}/test/src/arithmetic/reverse_polish_notation_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/reverse_polish_notation.cpp)

target_link_libraries(reverse_polish_notation_test
  ${GTEST_LIBRARIES}
  ${GMOCK_LIBRARIES}
  pthread)

set_target_properties(reverse_polish_notation_test
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_TEST})

add_test(NAME reverse_polish_notation_test
  COMMAND reverse_polish_notation_test
  WORKING_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_TEST})


### arithmetic_operation_test executable

add_executable(arithmetic_operation_test
  ${CMAKE_CURRENT_SOURCE_DIR}/test/src/arithmetic/arithmetic_operation_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/arithmetic_operation.cpp)

target_link_libraries(arithmetic_operation_test
  ${GTEST_LIBRARIES}
  ${GMOCK_LIBRARIES}
  pthread)

set_target_properties(arithmetic_operation_test
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_TEST})

add_test(NAME arithmetic_operation_test
  COMMAND arithmetic_operation_test
  WORKING_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_TEST})


## integration tests

### calculate_arithmetic_expression_test

add_executable(calculate_arithmetic_expression_test
  ${CMAKE_CURRENT_SOURCE_DIR}/test/integration/calculate_arithmetic_expression_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/arithmetic_expression_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/reverse_polish_notation.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/arithmetic_operation.cpp)

target_link_libraries(calculate_arithmetic_expression_test
  ${GTEST_LIBRARIES}
  ${GMOCK_LIBRARIES}
  pthread)

set_target_properties(calculate_arithmetic_expression_test
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_TEST})

add_test(NAME calculate_arithmetic_expression_test
  COMMAND calculate_arithmetic_expression_test
  WORKING_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY_TEST})
