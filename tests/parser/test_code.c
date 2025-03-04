#include "test_utils.h"

int main() {
    TEST_AST("`abc`\n",
        "var: Document[0,6)\n"
        "  var: BlockList[0,6)\n"
        "    var: Plain[0,6)\n"
        "      nul: Code[0,5)\n");

    TEST_AST("`abc\n"
        "def`\n",
        "var: Document[0,10)\n"
        "  var: BlockList[0,10)\n"
        "    var: Plain[0,10)\n"
        "      nul: Code[0,9)\n");

    TEST_AST("``a`b`c``\n",
        "var: Document[0,10)\n"
        "  var: BlockList[0,10)\n"
        "    var: Plain[0,10)\n"
        "      nul: Code[0,9)\n");

    TEST_AST("```a``b``c```\n",
        "var: Document[0,14)\n"
        "  var: BlockList[0,14)\n"
        "    var: Plain[0,14)\n"
        "      nul: Code[0,13)\n");

    // Fenced code block.
    TEST_AST("```abc\n"
        "```\n",
        "var: Document[0,11)\n"
        "  var: BlockList[0,11)\n"
        "    var: Plain[0,11)\n");
   return 0;
}
