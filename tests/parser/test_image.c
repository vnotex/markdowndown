#include "test_utils.h"

int main() {
    // Space between label and source.
    // FIXME: uncomment it after adding check of reference label.
    /*
    TEST_AST("![alt] (cat.png)\n",
        "var: Document[0,17)\n"
        "  var: BlockList[0,17)\n"
        "    var: Plain[0,17)\n");

    // Empty label.
    TEST_AST("![](cat.png)\n",
        "var: Document[0,13)\n"
        "  var: BlockList[0,13)\n"
        "    var: Plain[0,13)\n"
        "      var: Image[0,12){0||cat.png|||-1x-1}\n"
        "        nul: LinkLabel[1,3)\n"
        "        nul: LinkSource[4,11)\n");

    TEST_AST("![中文](cat.png)\n",
        "var: Document[0,19)\n"
        "  var: BlockList[0,19)\n"
        "    var: Plain[0,19)\n"
        "      var: Image[0,18){0|中文|cat.png|||-1x-1}\n"
        "        var: LinkLabel[1,9)\n"
        "        nul: LinkSource[10,17)\n");

    // Newline before the last ')'.
    TEST_AST("![alt](cat.png  \n"
        ")\n",
        "var: Document[0,19)\n"
        "  var: BlockList[0,19)\n"
        "    var: Plain[0,19)\n"
        "      var: Image[0,18){0|alt|cat.png|||-1x-1}\n"
        "        var: LinkLabel[1,6)\n"
        "        nul: LinkSource[7,14)\n");

    TEST_AST("![alt](http://vnote.info)\n",
        "var: Document[0,26)\n"
        "  var: BlockList[0,26)\n"
        "    var: Plain[0,26)\n"
        "      var: Image[0,25){0|alt|http://vnote.info|||-1x-1}\n"
        "        var: LinkLabel[1,6)\n"
        "        nul: LinkSource[7,24)\n");

    TEST_AST("![alt](cat.png \"title\" =512x256)\n",
        "var: Document[0,33)\n"
        "  var: BlockList[0,33)\n"
        "    var: Plain[0,33)\n"
        "      var: Image[0,32){0|alt|cat.png|title||512x256}\n"
        "        var: LinkLabel[1,6)\n"
        "        nul: LinkSource[7,14)\n"
        "        nul: LinkTitle[15,22)\n"
        "        nul: LinkSize[23,31)\n");

    // Only width.
    TEST_AST("![alt](cat.png =512x)\n",
        "var: Document[0,22)\n"
        "  var: BlockList[0,22)\n"
        "    var: Plain[0,22)\n"
        "      var: Image[0,21){0|alt|cat.png|||512x-1}\n"
        "        var: LinkLabel[1,6)\n"
        "        nul: LinkSource[7,14)\n"
        "        nul: LinkSize[15,20)\n");

    // Only height.
    TEST_AST("![alt](cat.png =x512)\n",
        "var: Document[0,22)\n"
        "  var: BlockList[0,22)\n"
        "    var: Plain[0,22)\n"
        "      var: Image[0,21){0|alt|cat.png|||-1x512}\n"
        "        var: LinkLabel[1,6)\n"
        "        nul: LinkSource[7,14)\n"
        "        nul: LinkSize[15,20)\n");
    */

    // Reference link.
    TEST_AST("![text][id]\n"
        "\n"
        "[id]: cat.png 'alt'\n",
        "var: Document[0,33)\n"
        "  var: BlockList[0,33)\n"
        "    var: Plain[0,11)\n"
        "      var: Image[0,11){1|text|cat.png|alt|id|-1x-1}\n"
        "        var: LinkLabel[1,7)\n"
        "        var: LinkReference[7,11)\n"
        "    nul: BlankLine[11,13)\n"
        "    var: Reference[13,33){id|cat.png|alt}\n"
        "      var: LinkLabel[13,17)\n"
        "      nul: LinkSource[19,26)\n"
        "      nul: LinkTitle[27,32)\n");

    // Reference link without match.
    TEST_AST("![text][id]\n",
        "var: Document[0,12)\n"
        "  var: BlockList[0,12)\n"
        "    var: Plain[0,12)\n"
        "      var: Dummy[0,11)\n"
        "        var: Dummy[1,7)\n"
        "        var: Dummy[7,11)\n");

    // Reference link with single label/reference.
    TEST_AST("![id]\n"
        "\n"
        "[id]: cat.png 'alt'\n",
        "var: Document[0,27)\n"
        "  var: BlockList[0,27)\n"
        "    var: Plain[0,5)\n"
        "      var: Image[0,5){1|id|cat.png|alt|id|-1x-1}\n"
        "        var: LinkLabel[1,5)\n"
        "    nul: BlankLine[5,7)\n"
        "    var: Reference[7,27){id|cat.png|alt}\n"
        "      var: LinkLabel[7,11)\n"
        "      nul: LinkSource[13,20)\n"
        "      nul: LinkTitle[21,26)\n");
    return 0;
}
