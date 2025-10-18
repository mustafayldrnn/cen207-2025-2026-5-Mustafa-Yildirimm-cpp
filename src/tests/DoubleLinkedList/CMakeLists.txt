# DoubleLinkedList/CMakeLists.txt
set(ROOT src)
set(TESTNAME doublelinkedlist_tests)

message(STATUS "[${ROOT}/${TESTNAME}] Module Tests...")

# Collect test files
file(GLOB TEST_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

# Create test executable
add_executable(${TESTNAME} ${TEST_SOURCES})

# Link with GoogleTest and the library
target_link_libraries(${TESTNAME} 
    PRIVATE 
    gtest 
    gtest_main
    doublelinkedlist
    utility
)

# Include directories
target_include_directories(${TESTNAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../DoubleLinkedList/header
    ${CMAKE_CURRENT_SOURCE_DIR}/../../utility/header
)

# Add test to CTest
add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})

message(STATUS "[${ROOT}/${TESTNAME}] Added target: ${TESTNAME}")
