# BrowserHistory CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Set library name
set(LIBNAME "browserhistory")

# Add library
add_library(${LIBNAME} STATIC
    src/BrowserHistory.cpp
)

# Include directories
target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/header
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

# No external link required; uses header-only ds::DoublyLinkedList under include/ds

# Set properties
set_target_properties(${LIBNAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
  target_compile_options(${LIBNAME} PRIVATE /Zi /Od)
  target_link_options(${LIBNAME} PRIVATE /DEBUG:FULL)
endif()

# Install
install(TARGETS ${LIBNAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY header/ DESTINATION include/${LIBNAME}
    FILES_MATCHING PATTERN "*.h"
)
