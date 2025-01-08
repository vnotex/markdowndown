option(MDD_GENERATE_PEG "Generate C files from PEG file" ON)

if(MDD_GENERATE_PEG)
    find_program(PACKCC_EXECUTABLE packcc DOC "Path to the packcc utility" REQUIRED)
    get_filename_component(PACKCC_BIN_DIR "${PACKCC_EXECUTABLE}" DIRECTORY)
    set(PACKCC_IMPORT_DIR "${PACKCC_BIN_DIR}/../import")
    cmake_path(NORMAL_PATH PACKCC_IMPORT_DIR OUTPUT_VARIABLE PACKCC_IMPORT_DIR)
    add_custom_command(
        OUTPUT markdowndown.h markdowndown.c
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/markdowndown.peg" "${CMAKE_CURRENT_BINARY_DIR}"
        COMMAND "${PACKCC_EXECUTABLE}" -I "${PACKCC_IMPORT_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/markdowndown.peg"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/markdowndown.peg
        VERBATIM)
endif()

add_library(markdowndown STATIC
    markdowndown.h markdowndown.c
    data.h data.c
    interface.h interface.c
    utils.h utils.c)

target_include_directories(markdowndown PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)
