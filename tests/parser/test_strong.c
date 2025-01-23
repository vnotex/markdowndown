#include "test_utils.h"

int main() {
    // Plain instead of strong.
    TEST_AST("d__a__\n",
        "var: Document[0,7)\n"
        "  var: BlockList[0,7)\n"
        "    var: Plain[0,7)\n");

    // Strong.
    TEST_AST("d**a**\n",
        "var: Document[0,7)\n"
        "  var: BlockList[0,7)\n"
        "    var: Plain[0,7)\n"
        "      nul: Strong[1,6)\n");

    TEST_AST("**abc**def\n"
        "__abc__ def",
        "var: Document[0,22)\n"
        "  var: BlockList[0,22)\n"
        "    var: Plain[0,22)\n"
        "      nul: Strong[0,7)\n"
        "      nul: Strong[11,18)\n");
    return 0;
}
