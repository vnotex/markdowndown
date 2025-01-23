#include "test_utils.h"

int main() {
    // Space between label and source.
    TEST_AST("![alt] (cat.png)\n",
        "var: Document[0,17)\n"
        "  var: BlockList[0,17)\n"
        "    var: Plain[0,17)\n");

    TEST_AST("![alt](cat.png)\n",
        "var: Document[0,16)\n"
        "  var: BlockList[0,16)\n"
        "    var: Plain[0,16)\n"
        "      una: Image[0,15)\n"
        "        var: Link[1,15)\n"
        "          var: Label[1,6)\n");

    // Newline before the last ')'.
    TEST_AST("![alt](cat.png  \n"
        ")\n",
        "var: Document[0,19)\n"
        "  var: BlockList[0,19)\n"
        "    var: Plain[0,19)\n"
        "      una: Image[0,18)\n"
        "        var: Link[1,18)\n"
        "          var: Label[1,6)\n");

    TEST_AST("![alt](http://vnote.info)\n",
        "var: Document[0,26)\n"
        "  var: BlockList[0,26)\n"
        "    var: Plain[0,26)\n"
        "      una: Image[0,25)\n"
        "        var: Link[1,25)\n"
        "          var: Label[1,6)\n");


    TEST_AST("![alt](cat.png \"title\" =512x256)\n",
        "var: Document[0,33)\n"
        "  var: BlockList[0,33)\n"
        "    var: Plain[0,33)\n"
        "      una: Image[0,32)\n"
        "        var: Link[1,32)\n"
        "          var: Label[1,6)\n");
    return 0;
}
