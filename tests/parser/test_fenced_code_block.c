#include "test_utils.h"

int main() {
    // Basic fenced code block with backticks
    TEST_AST("```\n"
        "code here\n"
        "```\n",
        "var: Document[0,18)\n"
        "  var: BlockList[0,18)\n"
        "    nul: FencedCodeBlock[0,18){}\n");

    // End of file.
    TEST_AST("```\n"
        "code here\n"
        "```",
        "var: Document[0,17)\n"
        "  var: BlockList[0,17)\n"
        "    nul: FencedCodeBlock[0,17){}\n");

    // Fenced code block with language identifier
    TEST_AST("```python\n"
        "def hello():\n"
        "    print('Hello')\n"
        "```\n",
        "var: Document[0,46)\n"
        "  var: BlockList[0,46)\n"
        "    nul: FencedCodeBlock[0,46){python}\n");

    // Fenced code block with tildes
    TEST_AST("~~~\n"
        "code here\n"
        "~~~\n",
        "var: Document[0,18)\n"
        "  var: BlockList[0,18)\n"
        "    nul: FencedCodeBlock[0,18){}\n");

    // Fenced code block with tildes and language
    TEST_AST("~~~javascript\n"
        "function hello() {\n"
        "    console.log('Hello');\n"
        "}\n"
        "~~~\n",
        "var: Document[0,65)\n"
        "  var: BlockList[0,65)\n"
        "    nul: FencedCodeBlock[0,65){javascript}\n");

    // Multiple fenced code blocks
    TEST_AST("```python\n"
        "print('Hello')\n"
        "```\n\n"
        "```javascript\n"
        "console.log('World')\n"
        "```\n",
        "var: Document[0,69)\n"
        "  var: BlockList[0,69)\n"
        "    nul: FencedCodeBlock[0,29){python}\n"
        "    nul: BlankLine[29,30)\n"
        "    nul: FencedCodeBlock[30,69){javascript}\n");

    // Fenced code block with empty lines
    TEST_AST("```\n"
        "line 1\n"
        "\n"
        "line 2\n"
        "```\n",
        "var: Document[0,23)\n"
        "  var: BlockList[0,23)\n"
        "    nul: FencedCodeBlock[0,23){}\n");

    TEST_AST("```\n"
        "```\n",
        "var: Document[0,8)\n"
        "  var: BlockList[0,8)\n"
        "    nul: FencedCodeBlock[0,8){}\n");

    return 0;
}
