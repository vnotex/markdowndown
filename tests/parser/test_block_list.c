#include "test_utils.h"

int main() {
    TEST_AST("abc\n"
        "  d e f\n"
        "d e f  \n"
        "hij",
        "var: Document[0,23)\n"
        "  var: BlockList[0,23)\n"
        "    nul: Block[0,4)\n"
        "    nul: Block[4,12)\n"
        "    nul: Block[12,20)\n"
        "    nul: Block[20,23)\n");

    TEST_AST("中文UTF8\n",
        "var: Document[0,11)\n"
        "  var: BlockList[0,11)\n"
        "    nul: Block[0,11)\n");
    return 0;
}
