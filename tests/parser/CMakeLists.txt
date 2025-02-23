project(TestParser VERSION 0.1.0 LANGUAGES C)

add_executable(test_document
    test_document.c
    test_utils.h test_utils.c)
target_link_libraries(test_document PRIVATE markdowndown)

add_executable(test_front_matter
    test_front_matter.c
    test_utils.h test_utils.c)
target_link_libraries(test_front_matter PRIVATE markdowndown)

add_executable(test_blank_line
    test_blank_line.c
    test_utils.h test_utils.c)
target_link_libraries(test_blank_line PRIVATE markdowndown)

add_executable(test_verbatim
    test_verbatim.c
    test_utils.h test_utils.c)
target_link_libraries(test_verbatim PRIVATE markdowndown)

add_executable(test_plain
    test_plain.c
    test_utils.h test_utils.c)
target_link_libraries(test_plain PRIVATE markdowndown)

add_executable(test_strong
    test_strong.c
    test_utils.h test_utils.c)
target_link_libraries(test_strong PRIVATE markdowndown)

add_executable(test_emph
    test_emph.c
    test_utils.h test_utils.c)
target_link_libraries(test_emph PRIVATE markdowndown)

add_executable(test_strike
    test_strike.c
    test_utils.h test_utils.c)
target_link_libraries(test_strike PRIVATE markdowndown)

add_executable(test_image
    test_image.c
    test_utils.h test_utils.c)
target_link_libraries(test_image PRIVATE markdowndown)

add_executable(test_link
    test_link.c
    test_utils.h test_utils.c)
target_link_libraries(test_link PRIVATE markdowndown)

add_executable(test_note
    test_note.c
    test_utils.h test_utils.c)
target_link_libraries(test_note PRIVATE markdowndown)

add_test(NAME test_document
    COMMAND $<TARGET_FILE:test_document>)
add_test(NAME test_front_matter
    COMMAND $<TARGET_FILE:test_front_matter>)
add_test(NAME test_blank_line
    COMMAND $<TARGET_FILE:test_blank_line>)
add_test(NAME test_verbatim
    COMMAND $<TARGET_FILE:test_verbatim>)
add_test(NAME test_plain
    COMMAND $<TARGET_FILE:test_plain>)
add_test(NAME test_strong
    COMMAND $<TARGET_FILE:test_strong>)
add_test(NAME test_emph
    COMMAND $<TARGET_FILE:test_emph>)
add_test(NAME test_strike
    COMMAND $<TARGET_FILE:test_strike>)
add_test(NAME test_image
    COMMAND $<TARGET_FILE:test_image>)
add_test(NAME test_link
    COMMAND $<TARGET_FILE:test_link>)
add_test(NAME test_note
    COMMAND $<TARGET_FILE:test_note>)
