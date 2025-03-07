#include "test_utils.h"

int main() {
    // Inline formula.
    TEST_AST("$a$\n",
        "var: Document[0,4)\n"
        "  var: BlockList[0,4)\n"
        "    var: Plain[0,4)\n"
        "      nul: InlineFormula[0,3)\n");
    // Not inline formula.
    TEST_AST("2$a$\n",
        "var: Document[0,5)\n"
        "  var: BlockList[0,5)\n"
        "    var: Plain[0,5)\n");
    // Not inline formula.
    TEST_AST("$$$\n",
        "var: Document[0,4)\n"
        "  var: BlockList[0,4)\n"
        "    var: Plain[0,4)\n");
    // Not inline formula.
    TEST_AST("$\\$\n",
        "var: Document[0,4)\n"
        "  var: BlockList[0,4)\n"
        "    var: Plain[0,4)\n");
    // Not inline formula.
    TEST_AST("$a$9\n",
        "var: Document[0,5)\n"
        "  var: BlockList[0,5)\n"
        "    var: Plain[0,5)\n");

    // Inline formula.
    TEST_AST("$ab$\n",
        "var: Document[0,5)\n"
        "  var: BlockList[0,5)\n"
        "    var: Plain[0,5)\n"
        "      nul: InlineFormula[0,4)\n");
    // Not inline formula.
    TEST_AST("$a\\$\n",
        "var: Document[0,5)\n"
        "  var: BlockList[0,5)\n"
        "    var: Plain[0,5)\n");
    // Not inline formula.
    TEST_AST("$a $\n",
        "var: Document[0,5)\n"
        "  var: BlockList[0,5)\n"
        "    var: Plain[0,5)\n");
    // Not inline formula.
    TEST_AST("$a\t$\n",
        "var: Document[0,5)\n"
        "  var: BlockList[0,5)\n"
        "    var: Plain[0,5)\n");
   return 0;
}
