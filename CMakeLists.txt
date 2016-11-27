project(entropy)

cmake_minimum_required(VERSION 3.0)

ENABLE_TESTING()

cmake_policy(SET CMP0042 OLD)

set(EXECUTABLE_OUTPUT_PATH       ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH          ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_VERBOSE_MAKEFILE       OFF)

if(APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG        "-g")
  set(CMAKE_CXX_FLAGS_RELEASE      "-g")
  set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")
else(APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG        "-g  -fPIC")
  set(CMAKE_CXX_FLAGS_RELEASE      "-g  -fPIC")
  set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")
endif(APPLE)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

option(MATRIX_TESTS  "Compile test cases" OFF)

if(MATRIX_TESTS)
  add_subdirectory(test)
endif(MATRIX_TESTS)

set(SRC src/matrix/Matrix.cpp)

if(APPLE)
  add_library(Matrix SHARED ${SRC})
else(APPLE)
  add_library(Matrix STATIC ${SRC})
endif(APPLE)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/src/matrix
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/
  CONFIGURATIONS Release Debug
  PATTERN "*.cpp" EXCLUDE
  PATTERN "*.txt" EXCLUDE
  )

INSTALL(DIRECTORY ${PROJECT_BINARY_DIR}/lib
  CONFIGURATIONS Release Debug
  DESTINATION ${CMAKE_INSTALL_PREFIX}
  FILES_MATCHING PATTERN "lib*" 
  )

