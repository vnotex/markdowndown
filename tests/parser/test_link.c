#include "test_utils.h"

int main() {
    // Space between label and source will break a link.
    TEST_AST("[alt] (cat.png)\n",
        "var: Document[0,16)\n"
        "  var: BlockList[0,16)\n"
        "    var: Plain[0,16)\n"
        "      var: Dummy[0,5)\n"
        "        var: Dummy[0,5)\n");

    // Empty label.
    TEST_AST("[](cat.png)\n",
        "var: Document[0,12)\n"
        "  var: BlockList[0,12)\n"
        "    var: Plain[0,12)\n"
        "      var: Link[0,11){0||cat.png|||-1x-1}\n"
        "        nul: LinkLabel[0,2)\n"
        "        nul: LinkSource[3,10)\n");

    TEST_AST("[中文](cat.png)\n",
        "var: Document[0,18)\n"
        "  var: BlockList[0,18)\n"
        "    var: Plain[0,18)\n"
        "      var: Link[0,17){0|中文|cat.png|||-1x-1}\n"
        "        var: LinkLabel[0,8)\n"
        "        nul: LinkSource[9,16)\n");

    // Newline before the last ')'.
    TEST_AST("[alt](cat.png  \n"
        ")\n",
        "var: Document[0,18)\n"
        "  var: BlockList[0,18)\n"
        "    var: Plain[0,18)\n"
        "      var: Link[0,17){0|alt|cat.png|||-1x-1}\n"
        "        var: LinkLabel[0,5)\n"
        "        nul: LinkSource[6,13)\n");

    TEST_AST("[alt](http://vnote.info)\n",
        "var: Document[0,25)\n"
        "  var: BlockList[0,25)\n"
        "    var: Plain[0,25)\n"
        "      var: Link[0,24){0|alt|http://vnote.info|||-1x-1}\n"
        "        var: LinkLabel[0,5)\n"
        "        nul: LinkSource[6,23)\n");

    TEST_AST("[alt](cat.png \"title\")\n",
        "var: Document[0,23)\n"
        "  var: BlockList[0,23)\n"
        "    var: Plain[0,23)\n"
        "      var: Link[0,22){0|alt|cat.png|title||-1x-1}\n"
        "        var: LinkLabel[0,5)\n"
        "        nul: LinkSource[6,13)\n"
        "        nul: LinkTitle[14,21)\n");

    // Reference link.
    TEST_AST("[text][id]\n"
        "\n"
        "[id]: cat.png 'alt'\n",
        "var: Document[0,32)\n"
        "  var: BlockList[0,32)\n"
        "    var: Plain[0,10)\n"
        "      var: Link[0,10){1|text|cat.png|alt|id|-1x-1}\n"
        "        var: LinkLabel[0,6)\n"
        "        var: LinkReference[6,10)\n"
        "    nul: BlankLine[10,12)\n"
        "    var: Reference[12,32){id|cat.png|alt}\n"
        "      var: LinkLabel[12,16)\n"
        "      nul: LinkSource[18,25)\n"
        "      nul: LinkTitle[26,31)\n");

    // Reference link without match.
    TEST_AST("[text][id]\n",
        "var: Document[0,11)\n"
        "  var: BlockList[0,11)\n"
        "    var: Plain[0,11)\n"
        "      var: Dummy[0,10)\n"
        "        var: Dummy[0,6)\n"
        "        var: Dummy[6,10)\n");

    // Reference link with single label/reference.
    TEST_AST("[id]\n"
        "\n"
        "[id]: cat.png 'alt'\n",
        "var: Document[0,26)\n"
        "  var: BlockList[0,26)\n"
        "    var: Plain[0,4)\n"
        "      var: Link[0,4){1|id|cat.png|alt|id|-1x-1}\n"
        "        var: LinkLabel[0,4)\n"
        "    nul: BlankLine[4,6)\n"
        "    var: Reference[6,26){id|cat.png|alt}\n"
        "      var: LinkLabel[6,10)\n"
        "      nul: LinkSource[12,19)\n"
        "      nul: LinkTitle[20,25)\n");

    // Reference link without match.
    TEST_AST("[iid]\n",
        "var: Document[0,6)\n"
        "  var: BlockList[0,6)\n"
        "    var: Plain[0,6)\n"
        "      var: Dummy[0,5)\n"
        "        var: Dummy[0,5)\n");

    // Auto link URL.
    TEST_AST("<https://vnote.fun>\n",
        "var: Document[0,20)\n"
        "  var: BlockList[0,20)\n"
        "    var: Plain[0,20)\n"
        "      nul: AutoLinkUrl[0,19){0|https://vnote.fun|https://vnote.fun|||-1x-1}\n");

    // Auto link email.
    TEST_AST("<mailto:vnote@funs>\n",
        "var: Document[0,20)\n"
        "  var: BlockList[0,20)\n"
        "    var: Plain[0,20)\n"
        "      nul: AutoLinkEmail[0,19){0|mailto:vnote@funs|mailto:vnote@funs|||-1x-1}\n");
    return 0;
}
