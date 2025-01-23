#include "test_utils.h"

int main() {
    TEST_AST("d~a~\n",
        "var: Document[0,5)\n"
        "  var: BlockList[0,5)\n"
        "    var: Plain[0,5)\n"
        "      var: Strike[1,4)\n");

    TEST_AST("~abc~def\n"
        "~abc~ def",
        "var: Document[0,18)\n"
        "  var: BlockList[0,18)\n"
        "    var: Plain[0,18)\n"
        "      var: Strike[0,5)\n"
        "      var: Strike[9,14)\n");

    return 0;
}
