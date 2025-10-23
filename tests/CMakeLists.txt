enable_testing()

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests PRIVATE translatorlib safechronolib GTest::gtest_main)

# Add LanguageTranslator source files to tests
target_sources(unit_tests PRIVATE 
    ../src/LanguageTranslator/src/LanguageTranslator.cpp
)

include(GoogleTest)
gtest_discover_tests(unit_tests)

