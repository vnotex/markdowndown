#include "test_utils.h"

int main() {
    TEST_AST("Heading 1\n"
        "=\n",
        "var: Document[0,12)\n"
        "  var: BlockList[0,12)\n"
        "    var: H1[0,12){Heading 1}\n");

    TEST_AST("Heading 2\n"
        "-----\n",
        "var: Document[0,16)\n"
        "  var: BlockList[0,16)\n"
        "    var: H2[0,16){Heading 2}\n");

    // Level 1 heading
    TEST_AST("# Heading 1\n",
        "var: Document[0,12)\n"
        "  var: BlockList[0,12)\n"
        "    var: H1[0,12){Heading 1}\n");

    // Level 2 heading
    TEST_AST("## Heading 2\n",
        "var: Document[0,13)\n"
        "  var: BlockList[0,13)\n"
        "    var: H2[0,13){Heading 2}\n");

    // Level 3 heading
    TEST_AST("### Heading 3\n",
        "var: Document[0,14)\n"
        "  var: BlockList[0,14)\n"
        "    var: H3[0,14){Heading 3}\n");

    // Level 4 heading
    TEST_AST("#### Heading 4\n",
        "var: Document[0,15)\n"
        "  var: BlockList[0,15)\n"
        "    var: H4[0,15){Heading 4}\n");

    // Level 5 heading
    TEST_AST("##### Heading 5\n",
        "var: Document[0,16)\n"
        "  var: BlockList[0,16)\n"
        "    var: H5[0,16){Heading 5}\n");

    // Level 6 heading
    TEST_AST("###### Heading 6\n",
        "var: Document[0,17)\n"
        "  var: BlockList[0,17)\n"
        "    var: H6[0,17){Heading 6}\n");

    // Level 1 heading with pending #
    TEST_AST("# Heading 1 ####\n",
        "var: Document[0,17)\n"
        "  var: BlockList[0,17)\n"
        "    var: H1[0,17){Heading 1}\n");

    // Multiple headings
    TEST_AST("# Heading 1\n\n"
        "## Heading 2\n",
        "var: Document[0,26)\n"
        "  var: BlockList[0,26)\n"
        "    var: H1[0,12){Heading 1}\n"
        "    nul: BlankLine[12,13)\n"
        "    var: H2[13,26){Heading 2}\n");

    // Heading with inline elements
    TEST_AST("# Heading with **bold** and *italic*\n",
        "var: Document[0,37)\n"
        "  var: BlockList[0,37)\n"
        "    var: H1[0,37){Heading with **bold** and *italic*}\n"
        "      var: Strong[15,23)\n"
        "      var: Emph[28,36)\n");

    // Heading with spaces before
    TEST_AST("  # Heading with spaces\n",
        "var: Document[0,24)\n"
        "  var: BlockList[0,24)\n"
        "    var: H1[0,24){Heading with spaces}\n");

    // Heading with spaces after
    TEST_AST("# Heading with spaces  \n",
        "var: Document[0,24)\n"
        "  var: BlockList[0,24)\n"
        "    var: H1[0,24){Heading with spaces}\n");

    // Invalid heading (no space after #)
    TEST_AST("#Heading without space\n",
        "var: Document[0,23)\n"
        "  var: BlockList[0,23)\n"
        "    var: Plain[0,23)\n");

    // Invalid heading (too many #)
    TEST_AST("####### Heading level 7\n",
        "var: Document[0,24)\n"
        "  var: BlockList[0,24)\n"
        "    var: Plain[0,24)\n");

    return 0;
}
