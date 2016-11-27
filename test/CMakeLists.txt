include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(matrix-tests matrix_tests.cpp main.cpp)
target_link_libraries(matrix-tests Matrix cppunit)

include_directories(${PROJECT_BINARY_DIR})

ADD_TEST(matrix                     "${PROJECT_BINARY_DIR}/bin/matrix-tests")
