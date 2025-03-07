#include "test_utils.h"

int main() {
    // Basic horizontal rule with hyphens
    TEST_AST("---\n",
        "var: Document[0,4)\n"
        "  var: BlockList[0,4)\n"
        "    nul: HorizontalRule[0,4)\n");

    // Horizontal rule with more than three hyphens
    TEST_AST("----\n",
        "var: Document[0,5)\n"
        "  var: BlockList[0,5)\n"
        "    nul: HorizontalRule[0,5)\n");

    // Horizontal rule with asterisks
    TEST_AST("***\n",
        "var: Document[0,4)\n"
        "  var: BlockList[0,4)\n"
        "    nul: HorizontalRule[0,4)\n");

    // Horizontal rule with underscores
    TEST_AST("___\n",
        "var: Document[0,4)\n"
        "  var: BlockList[0,4)\n"
        "    nul: HorizontalRule[0,4)\n");

    // Multiple horizontal rules
    TEST_AST("---\n\n***\n",
        "var: Document[0,9)\n"
        "  var: BlockList[0,9)\n"
        "    nul: HorizontalRule[0,4)\n"
        "    nul: BlankLine[4,5)\n"
        "    nul: HorizontalRule[5,9)\n");

    // Horizontal rule with spaces before
    TEST_AST("  ---\n",
        "var: Document[0,6)\n"
        "  var: BlockList[0,6)\n"
        "    nul: HorizontalRule[0,6)\n");

    // Horizontal rule with spaces after
    TEST_AST("---  \n",
        "var: Document[0,6)\n"
        "  var: BlockList[0,6)\n"
        "    nul: HorizontalRule[0,6)\n");

    // Horizontal rule with spaces before and after
    TEST_AST("  ---  \n",
        "var: Document[0,8)\n"
        "  var: BlockList[0,8)\n"
        "    nul: HorizontalRule[0,8)\n");

    // Horizontal rule with mixed characters (should not match)
    TEST_AST("--*\n",
        "var: Document[0,4)\n"
        "  var: BlockList[0,4)\n"
        "    var: Plain[0,4)\n");

    return 0;
}
