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
        "      var: NoteBlock[16,20)\n");

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
        "      var: NoteBlock[16,20)\n");

    // Inline note.
    TEST_AST("^[alt **bold** *haha*]\n",
        "var: Document[0,23)\n"
        "  var: BlockList[0,23)\n"
        "    var: Plain[0,23)\n"
        "      var: InlineNote[0,22){|alt **bold** *haha*}\n"
        "        nul: Strong[6,14)\n"
        "        var: Emph[15,21)\n");
   return 0;
}
