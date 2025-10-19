enable_testing()

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests PRIVATE translatorlib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)

