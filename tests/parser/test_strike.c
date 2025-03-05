#include "test_utils.h"

int main() {
    TEST_AST("d~~a~~\n",
        "var: Document[0,7)\n"
        "  var: BlockList[0,7)\n"
        "    var: Plain[0,7)\n"
        "      var: Strike[1,6)\n");

    TEST_AST("~~abc~~def\n"
        "~~abc~~ def",
        "var: Document[0,22)\n"
        "  var: BlockList[0,22)\n"
        "    var: Plain[0,22)\n"
        "      var: Strike[0,7)\n"
        "      var: Strike[11,18)\n");

    // Do not allow whitespace before the ending mark.
    TEST_AST("~~abc ~~def\n",
        "var: Document[0,12)\n"
        "  var: BlockList[0,12)\n"
        "    var: Plain[0,12)\n");
    TEST_AST("~~abc\t~~def\n",
        "var: Document[0,12)\n"
        "  var: BlockList[0,12)\n"
        "    var: Plain[0,12)\n");
    TEST_AST("~~abc\n~~def\n",
        "var: Document[0,12)\n"
        "  var: BlockList[0,12)\n"
        "    var: Plain[0,12)\n");
    TEST_AST("~~abc\r~~def\n",
        "var: Document[0,12)\n"
        "  var: BlockList[0,12)\n"
        "    var: Plain[0,12)\n");

    return 0;
}
