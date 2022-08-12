cmake_minimum_required(VERSION 3.3)

set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")

# expected
add_subdirectory("expected")

# sfml
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sfml-2.5.1/lib/cmake/SFML" PARENT_SCOPE)

set(ZUMA_3RDPARTY_INCLUDE_DIRECTORIES "${INCLUDE_DIRS}" PARENT_SCOPE)