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

add_executable(test_code
    test_code.c
    test_utils.h test_utils.c)
target_link_libraries(test_code PRIVATE markdowndown)

add_executable(test_inline_formula
    test_inline_formula.c
    test_utils.h test_utils.c)
target_link_libraries(test_inline_formula PRIVATE markdowndown)

add_executable(test_mark
    test_mark.c
    test_utils.h test_utils.c)
target_link_libraries(test_mark PRIVATE markdowndown)

add_executable(test_block_quote
    test_block_quote.c
    test_utils.h test_utils.c)
target_link_libraries(test_block_quote PRIVATE markdowndown)

add_executable(test_fenced_code_block
    test_fenced_code_block.c
    test_utils.h test_utils.c)
target_link_libraries(test_fenced_code_block PRIVATE markdowndown)

add_executable(test_display_formula
    test_display_formula.c
    test_utils.h test_utils.c)
target_link_libraries(test_display_formula PRIVATE markdowndown)

add_executable(test_horizontal_rule
    test_horizontal_rule.c
    test_utils.h test_utils.c)
target_link_libraries(test_horizontal_rule PRIVATE markdowndown)

add_executable(test_heading
    test_heading.c
    test_utils.h test_utils.c)
target_link_libraries(test_heading PRIVATE markdowndown)

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
add_test(NAME test_code
    COMMAND $<TARGET_FILE:test_code>)
add_test(NAME test_inline_formula
    COMMAND $<TARGET_FILE:test_inline_formula>)
add_test(NAME test_mark
    COMMAND $<TARGET_FILE:test_mark>)
add_test(NAME test_block_quote
    COMMAND $<TARGET_FILE:test_block_quote>)
add_test(NAME test_fenced_code_block
    COMMAND $<TARGET_FILE:test_fenced_code_block>)
add_test(NAME test_display_formula
    COMMAND $<TARGET_FILE:test_display_formula>)
add_test(NAME test_horizontal_rule
    COMMAND $<TARGET_FILE:test_horizontal_rule>)
add_test(NAME test_heading
    COMMAND $<TARGET_FILE:test_heading>)
