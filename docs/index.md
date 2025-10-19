# BASIC Translator (C++17)

This project provides:
- Core data structures with meaningful use-cases: Doubly Linked List, XOR Linked List, Sparse Matrix, Stack/Queue, Binary Heap, Graph (BFS/DFS), Hash Table.
- A BASIC language translator skeleton with Lexer and Parser scaffolding.
- GoogleTest unit tests for each data structure (100% pass expected once GTest is fetched).

Build (CMake)
- Configure: `cmake -S . -B build -DTRANSLATOR_ENABLE_TESTS=ON`
- Build: `cmake --build build --config Release`
- Run tests: `ctest --test-dir build`

Notes
- Tests use GoogleTest via FetchContent. First configure requires network to download googletest.
- Translator CLI: `translator input.bas -o output.cpp`

Planned next steps
- Flesh out parser (shunting-yard for expressions), AST, symbol table, CFG analysis, and codegen.

