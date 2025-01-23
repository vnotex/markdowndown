#include "test_utils.h"

int main() {
    TEST_AST("\n"
        " \n"
        "  \n",
        "var: Document[0,6)\n"
        "  var: BlockList[0,6)\n"
        "    nul: BlankLine[0,6)\n");
    return 0;
}
