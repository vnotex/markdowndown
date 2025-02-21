#include "test_utils.h"

int main() {
    TEST_AST("d~~a~~\n",
        "var: Document[0,7)\n"
        "  var: BlockList[0,7)\n"
        "    var: Plain[0,7)\n"
        "      nul: Strike[1,6)\n");

    TEST_AST("~~abc~~def\n"
        "~~abc~~ def",
        "var: Document[0,22)\n"
        "  var: BlockList[0,22)\n"
        "    var: Plain[0,22)\n"
        "      nul: Strike[0,7)\n"
        "      nul: Strike[11,18)\n");

    return 0;
}
