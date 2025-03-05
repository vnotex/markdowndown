#include "test_utils.h"

int main() {
    // Multiple blank lines will break.
    TEST_AST("__ab\n"
        "\n"
        "cd__",
        "var: Document[0,10)\n"
        "  var: BlockList[0,10)\n"
        "    var: Plain[0,4)\n"
        "    nul: BlankLine[4,6)\n"
        "    var: Plain[6,10)\n");

    // Plain instead of strong.
    TEST_AST("d__a__\n",
        "var: Document[0,7)\n"
        "  var: BlockList[0,7)\n"
        "    var: Plain[0,7)\n");

    // Strong.
    TEST_AST("d**a**\n",
        "var: Document[0,7)\n"
        "  var: BlockList[0,7)\n"
        "    var: Plain[0,7)\n"
        "      var: Strong[1,6)\n");

    // Strong with inlines.
    TEST_AST("**ab*cd*e`f`g**\n",
        "var: Document[0,16)\n"
        "  var: BlockList[0,16)\n"
        "    var: Plain[0,16)\n"
        "      var: Strong[0,15)\n"
        "        var: Emph[4,8)\n"
        "        nul: Code[9,12)\n");

    TEST_AST("**abc**def\n"
        "__abc__ def",
        "var: Document[0,22)\n"
        "  var: BlockList[0,22)\n"
        "    var: Plain[0,22)\n"
        "      var: Strong[0,7)\n"
        "      var: Strong[11,18)\n");

    // Not strong.
    TEST_AST("**abc **\n",
        "var: Document[0,9)\n"
        "  var: BlockList[0,9)\n"
        "    var: Plain[0,9)\n");

    // Not strong.
    TEST_AST("**abc\n**\n",
        "var: Document[0,9)\n"
        "  var: BlockList[0,9)\n"
        "    var: Plain[0,9)\n");

    // Strong.
    TEST_AST("**ac\n"
        "c**\n",
        "var: Document[0,9)\n"
        "  var: BlockList[0,9)\n"
        "    var: Plain[0,9)\n"
        "      var: Strong[0,8)\n");
    return 0;
}
