#include "test_utils.h"

int main() {
    // Empty.
    TEST_AST("---\n"
        "---\n",
        "var: Document[0,8)\n"
        "  nul: FrontMatter[0,8)\n");

    // No blocks.
    TEST_AST("---\n"
        "title: vnote docs\n"
        "type: tech\n"
        "---\n",
        "var: Document[0,37)\n"
        "  nul: FrontMatter[0,37)\n");

    // Front matter + blocks.
    TEST_AST("---\n"
        "title: vnote docs\n"
        "type: tech\n"
        "---\n"
        "body\n",
        "var: Document[0,42)\n"
        "  nul: FrontMatter[0,37)\n"
        "  var: BlockList[37,42)\n"
        "    nul: Block[37,42)\n");

    return 0;
}
