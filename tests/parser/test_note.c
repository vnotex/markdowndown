#include "test_utils.h"

int main() {
    TEST_AST("[^alt]\n"
        "\n"
        "[^alt]: ABC\n",
        "var: Document[0,20)\n"
        "  var: BlockList[0,20)\n"
        "    var: Plain[0,6)\n"
        "      nul: NoteReference[0,6){alt|ABC\n}\n"
        "    nul: BlankLine[6,8)\n"
        "    var: Note[8,20){alt|ABC\n}\n"
        "      var: Plain[16,20)\n");

    TEST_AST("[^alt]\n"
        "\n"
        "[^alt]: ABC **def** *very\n"
        "good*\n",
        "var: Document[0,40)\n"
        "  var: BlockList[0,40)\n"
        "    var: Plain[0,6)\n"
        "      nul: NoteReference[0,6){alt|ABC **def** *very\ngood*\n}\n"
        "    nul: BlankLine[6,8)\n"
        "    var: Note[8,40){alt|ABC **def** *very\ngood*\n}\n"
        "      var: Plain[16,40)\n"
        "        var: Strong[20,27)\n"
        "        var: Emph[28,39)\n");

    // Ref without match.
    TEST_AST("[^alt]\n"
        "\n"
        "[^alr]: ABC\n",
        "var: Document[0,20)\n"
        "  var: BlockList[0,20)\n"
        "    var: Plain[0,6)\n"
        "      nul: Dummy[0,6)\n"
        "    nul: BlankLine[6,8)\n"
        "    var: Note[8,20){alr|ABC\n}\n"
        "      var: Plain[16,20)\n");

    // Inline note.
    TEST_AST("^[alt **bold** *haha*]\n",
        "var: Document[0,23)\n"
        "  var: BlockList[0,23)\n"
        "    var: Plain[0,23)\n"
        "      var: InlineNote[0,22){|alt **bold** *haha*}\n"
        "        var: Strong[6,14)\n"
        "        var: Emph[15,21)\n");

    // Note with strong and emphasis
    TEST_AST("[^fmt]\n"
        "\n"
        "[^fmt]: This is **bold** and *italic*\n",
        "var: Document[0,46)\n"
        "  var: BlockList[0,46)\n"
        "    var: Plain[0,6)\n"
        "      nul: NoteReference[0,6){fmt|This is **bold** and *italic*\n}\n"
        "    nul: BlankLine[6,8)\n"
        "    var: Note[8,46){fmt|This is **bold** and *italic*\n}\n"
        "      var: Plain[16,46)\n"
        "        var: Strong[24,32)\n"
        "        var: Emph[37,45)\n");

    // Note with link
    TEST_AST("[^link]\n"
        "\n"
        "[^link]: Visit [example](http://example.com)\n",
        "var: Document[0,54)\n"
        "  var: BlockList[0,54)\n"
        "    var: Plain[0,7)\n"
        "      nul: NoteReference[0,7){link|Visit [example](http://example.com)\n}\n"
        "    nul: BlankLine[7,9)\n"
        "    var: Note[9,54){link|Visit [example](http://example.com)\n}\n"
        "      var: Plain[18,54)\n"
        "        var: Link[24,53){0|example|http://example.com|||-1x-1}\n"
        "          var: LinkLabel[24,33)\n"
        "          nul: LinkSource[34,52)\n");

    return 0;
}
