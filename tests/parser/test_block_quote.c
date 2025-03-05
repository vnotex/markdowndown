#include "test_utils.h"

int main() {
    // Basic block quote
    TEST_AST("> Simple block quote\n",
        "var: Document[0,21)\n"
        "  var: BlockList[0,21)\n"
        "    var: BlockQuote[0,21)\n");

    // Block quote with strong and emphasis
    TEST_AST("> This is a **bold** and *italic* text\n",
        "var: Document[0,39)\n"
        "  var: BlockList[0,39)\n"
        "    var: BlockQuote[0,39)\n"
        "      var: Strong[12,20)\n"
        "      var: Emph[25,33)\n");

    // Block quote with link
    TEST_AST("> Check out [this link](http://example.com)\n",
        "var: Document[0,44)\n"
        "  var: BlockList[0,44)\n"
        "    var: BlockQuote[0,44)\n"
        "      var: Link[12,43){0|this link|http://example.com|||-1x-1}\n"
        "        var: LinkLabel[12,23)\n"
        "        nul: LinkSource[24,42)\n");

    // Block quote with multiple paragraphs and mixed formatting
    TEST_AST("> First paragraph with **bold**\n"
        ">\n"
        "> Second paragraph with *italic* and [link](http://example.com)\n"
        "> And a continuation with `code`\n",
        "var: Document[0,131)\n"
        "  var: BlockList[0,131)\n"
        "    var: BlockQuote[0,131)\n"
        "      var: Strong[23,31)\n"
        "      var: Emph[58,66)\n"
        "      var: Link[71,97){0|link|http://example.com|||-1x-1}\n"
        "        var: LinkLabel[71,77)\n"
        "        nul: LinkSource[78,96)\n"
        "      nul: Code[124,130)\n");

    return 0;
}
