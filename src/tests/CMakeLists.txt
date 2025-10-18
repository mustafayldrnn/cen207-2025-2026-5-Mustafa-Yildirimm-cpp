# tests/CMakeLists.txt

# Download and include GoogleTest
 include(FetchContent)
 
# OFFLINE 
# ----------------------------------------------------------------------------------
# Include GoogleTest
set(GTEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest)

# Add GoogleTest as a subdirectory
add_subdirectory(${GTEST_DIR} ${CMAKE_CURRENT_BINARY_DIR}/googletest-build EXCLUDE_FROM_ALL)

# Include the Google Test framework
include_directories(${GTEST_DIR}/googletest/include)
# ----------------------------------------------------------------------------------
 
# ONLINE 
# ----------------------------------------------------------------------------------
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
#   DOWNLOAD_EXTRACT_TIMESTAMP true
# )
# 
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)
# ----------------------------------------------------------------------------------

# Include the Google Test framework
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


# Utility tests
if(ENABLE_UTILITY)
	add_subdirectory(utility)
endif()

# Data Structure tests
if(ENABLE_DOUBLE_LINKED_LIST)
	add_subdirectory(DoubleLinkedList)
endif()

if(ENABLE_XOR_LINKED_LIST)
	add_subdirectory(XORLinkedList)
endif()

if(ENABLE_SPARSE_MATRIX)
	add_subdirectory(SparseMatrix)
endif()

if(ENABLE_STACK_QUEUE)
	add_subdirectory(StackQueue)
endif()

if(ENABLE_HEAP)
	add_subdirectory(Heap)
endif()

if(ENABLE_HASH_TABLE)
	add_subdirectory(HashTable)
endif()

