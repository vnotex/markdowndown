#include "test_utils.h"

int main() {
    // Spaces.
    TEST_AST("    abc\n"
        "    abc\n"
        "    abc\n",
        "var: Document[0,24)\n"
        "  var: BlockList[0,24)\n"
        "    nul: Verbatim[0,24)\n");

    // Tab.
    TEST_AST("	abc\n"
        "	abc\n"
        "	abc\n",
        "var: Document[0,15)\n"
        "  var: BlockList[0,15)\n"
        "    nul: Verbatim[0,15)\n");

    // Empty line separated.
    TEST_AST("    abc\n"
        "    abc\n"
        "\n"
        "    abc\n",
        "var: Document[0,25)\n"
        "  var: BlockList[0,25)\n"
        "    nul: Verbatim[0,16)\n"
        "    nul: BlankLine[16,17)\n"
        "    nul: Verbatim[17,25)\n");
    return 0;
}
