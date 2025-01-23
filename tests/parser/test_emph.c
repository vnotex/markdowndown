#include "test_utils.h"

int main() {
    // Plain instead of emph.
    TEST_AST("d_a_\n",
        "var: Document[0,5)\n"
        "  var: BlockList[0,5)\n"
        "    var: Plain[0,5)\n");

    // Emph.
    TEST_AST("d*a*\n",
        "var: Document[0,5)\n"
        "  var: BlockList[0,5)\n"
        "    var: Plain[0,5)\n"
        "      var: Emph[1,4)\n");

    TEST_AST("*abc*def\n"
        "_abc_ def",
        "var: Document[0,18)\n"
        "  var: BlockList[0,18)\n"
        "    var: Plain[0,18)\n"
        "      var: Emph[0,5)\n"
        "      var: Emph[9,14)\n");

    // Strong within emph.
    TEST_AST("*a**b**c*\n",
        "var: Document[0,10)\n"
        "  var: BlockList[0,10)\n"
        "    var: Plain[0,10)\n"
        "      var: Emph[0,9)\n"
        "        nul: Strong[2,7)\n");
    return 0;
}
