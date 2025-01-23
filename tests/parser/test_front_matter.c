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

    // No blocks, UTF8.
    TEST_AST("---\n"
        "title: vnote docs\n"
        "type: 技术\n"
        "---\n",
        "var: Document[0,39)\n"
        "  nul: FrontMatter[0,39)\n");

    return 0;
}
