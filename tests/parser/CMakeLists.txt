project(TestParser VERSION 0.1.0 LANGUAGES C)

add_executable(test_document
    test_document.c
    test_utils.h test_utils.c)
target_link_libraries(test_document PRIVATE markdowndown)

add_executable(test_front_matter
    test_front_matter.c
    test_utils.h test_utils.c)
target_link_libraries(test_front_matter PRIVATE markdowndown)

add_executable(test_block_list
    test_block_list.c
    test_utils.h test_utils.c)
target_link_libraries(test_block_list PRIVATE markdowndown)

add_test(NAME test_document
    COMMAND $<TARGET_FILE:test_document>)
add_test(NAME test_front_matter
    COMMAND $<TARGET_FILE:test_front_matter>)
add_test(NAME test_block_list
    COMMAND $<TARGET_FILE:test_block_list>)
