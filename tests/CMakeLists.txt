enable_testing()

# Derlenmeyen bazı ağır test dosyalarını hariç tutup, çalışan seti sabitliyoruz
set(TEST_SOURCES
    LanguageTranslator_test.cpp
    test_language_translator_comprehensive.cpp
    test_language_translator_extra.cpp
    test_translator_additional.cpp
    test_safe_chrono_calculator.cpp
    test_overflow_protection.cpp
    test_simple_coverage_boost.cpp
    test_math_utility.cpp
    test_translator_coverage_topoff.cpp
)

add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests PRIVATE translatorlib safechronolib GTest::gtest_main)

# Add LanguageTranslator source files to tests
target_sources(unit_tests PRIVATE 
    ../src/LanguageTranslator/src/LanguageTranslator.cpp
    ../src/LanguageTranslator/src/Persistence.cpp
    ../src/utility/src/mathUtility.cpp
)

# Add include directories for main library headers
target_include_directories(unit_tests PRIVATE 
    ../src
    ../include
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
