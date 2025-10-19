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
