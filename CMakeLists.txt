cmake_minimum_required (VERSION 3.12)
project(MarkdownDown VERSION 0.1.0 LANGUAGES C)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CTest)

add_subdirectory(src)
add_subdirectory(tests)
