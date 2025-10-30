cmake_minimum_required(VERSION 3.16)
project(basic_translator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TRANSLATOR_ENABLE_TESTS "Enable building tests" ON)

add_library(translatorlib
  src/translator/lexer.cpp
  src/translator/parser.cpp
  src/translator/codegen.cpp
)

target_include_directories(translatorlib PUBLIC include src)

add_executable(translator apps/translator/main.cpp)
target_link_libraries(translator PRIVATE translatorlib)

# BASIC to C++ Translator Application
add_executable(basic_translator src/Translateapp/src/Translateapp.cpp src/Translate/src/Translate.cpp)
target_include_directories(basic_translator PRIVATE src)

# 37-Basic Language Translator Application
add_executable(language_translator 
    apps/language_translator/main.cpp 
    src/LanguageTranslator/src/LanguageTranslator.cpp
    src/LanguageTranslator/src/Persistence.cpp
)
target_include_directories(language_translator PRIVATE src)

# Safe Chrono Calculator Library
add_library(safechronolib src/SafeChronoCalculator.cpp)
target_include_directories(safechronolib PUBLIC src)

# Data structure libs used by BrowserHistory
add_subdirectory(src/BrowserHistory)

if(TRANSLATOR_ENABLE_TESTS)
  include(FetchContent)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
  )
  FetchContent_MakeAvailable(googletest)

  enable_testing()
  add_subdirectory(tests)
endif()
