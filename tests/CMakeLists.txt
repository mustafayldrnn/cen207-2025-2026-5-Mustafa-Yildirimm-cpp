enable_testing()

# Derlenmeyen bazı ağır test dosyalarını hariç tutup, çalışan seti sabitliyoruz
set(TEST_SOURCES
    LanguageTranslator_test.cpp
    test_language_translator_comprehensive.cpp
    test_language_translator_extra.cpp
    test_language_translator_user_management.cpp
    test_language_translator_dictionary.cpp
    test_language_translator_history.cpp
    test_translator_additional.cpp
    test_safe_chrono_calculator.cpp
    test_overflow_protection.cpp
    test_simple_coverage_boost.cpp
    test_math_utility.cpp
    test_translator_coverage_topoff.cpp
    test_hash_table.cpp
    test_heap.cpp
    test_sparse_matrix.cpp
    test_doubly_linked_list.cpp
    test_binary_tree.cpp
    test_lexer_parser_codegen.cpp
    test_graph_bfs_dfs.cpp
    test_stack_queue.cpp
    test_xor_linked_list.cpp
    test_string_view_coverage.cpp
    test_string_view_advanced_coverage.cpp
    test_string_view_comprehensive.cpp
    test_string_view_internal_utilities.cpp
    test_chrono_coverage.cpp
    test_chrono_advanced_coverage.cpp
    test_comprehensive_edge_cases.cpp
    test_advanced_coverage_boost.cpp
)

add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests PRIVATE translatorlib safechronolib GTest::gtest_main)

# Add LanguageTranslator source files to tests
target_sources(unit_tests PRIVATE 
    ../src/LanguageTranslator/src/LanguageTranslator.cpp
    ../src/LanguageTranslator/src/Persistence.cpp
    ../src/utility/src/mathUtility.cpp
    ../src/coverage_anchor/CoverageAnchor.cpp
)

# Add include directories for main library headers
target_include_directories(unit_tests PRIVATE 
    ../src
    ../include
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
