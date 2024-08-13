set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_program(PACKCC packcc)

add_custom_command(
    OUTPUT markdowndown.h markdowndown.c
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/markdowndown.peg" "${CMAKE_CURRENT_BINARY_DIR}"
    COMMAND "${PACKCC}" ${CMAKE_CURRENT_BINARY_DIR}/markdowndown.peg
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/markdowndown.peg
    VERBATIM)

add_library(markdowndown STATIC
    markdowndown.h markdowndown.c)

target_include_directories(markdowndown PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
)
