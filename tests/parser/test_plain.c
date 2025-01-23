#include "test_utils.h"

int main() {
    TEST_AST("abc\n"
        "def\n",
        "var: Document[0,8)\n"
        "  var: BlockList[0,8)\n"
        "    var: Plain[0,8)\n");

    // Chinese.
    TEST_AST("abc\n"
        "中文\n",
        "var: Document[0,11)\n"
        "  var: BlockList[0,11)\n"
        "    var: Plain[0,11)\n");

    // No new line.
    TEST_AST("abc",
        "var: Document[0,3)\n"
        "  var: BlockList[0,3)\n"
        "    var: Plain[0,3)\n");

    // UL line or star line.
    TEST_AST("_____\n"
        " ___ \n"
        "****\n"
        " *** \n",
        "var: Document[0,23)\n"
        "  var: BlockList[0,23)\n"
        "    var: Plain[0,23)\n");
    return 0;
}
