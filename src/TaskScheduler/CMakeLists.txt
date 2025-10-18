# TaskScheduler CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Set library name
set(LIBNAME "taskscheduler")

# Add library
add_library(${LIBNAME} STATIC
    src/TaskScheduler.cpp
)

# Include directories
target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/header
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link with StackQueue
target_link_libraries(${LIBNAME} stackqueue)

# Set properties
set_target_properties(${LIBNAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

# Install
install(TARGETS ${LIBNAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY header/ DESTINATION include/${LIBNAME}
    FILES_MATCHING PATTERN "*.h"
)
