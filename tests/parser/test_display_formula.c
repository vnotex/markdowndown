#include "test_utils.h"

int main() {
    // Basic display formula with dollar signs
    TEST_AST("$$\n"
        "E = mc^2\n"
        "$$\n",
        "var: Document[0,15)\n"
        "  var: BlockList[0,15)\n"
        "    nul: DisplayFormula[0,15)\n");

    // Display formula with dollar signs and formula number
    TEST_AST("$$\n"
        "E = mc^2\n"
        "$$ (1)\n",
        "var: Document[0,19)\n"
        "  var: BlockList[0,19)\n"
        "    nul: DisplayFormula[0,19)\n");

    // Display formula with raw LaTeX
    TEST_AST("\\begin{equation}\n"
        "E = mc^2\n"
        "\\end{equation}\n",
        "var: Document[0,41)\n"
        "  var: BlockList[0,41)\n"
        "    nul: DisplayFormula[0,41)\n");

    // Display formula with raw LaTeX and formula number
    TEST_AST("\\begin{equation}\n"
        "E = mc^2\n"
        "\\end{equation} (1)\n",
        "var: Document[0,45)\n"
        "  var: BlockList[0,45)\n"
        "    nul: DisplayFormula[0,45)\n");

    // Multiple display formulas
    TEST_AST("$$\n"
        "E = mc^2\n"
        "$$\n\n"
        "\\begin{equation}\n"
        "F = ma\n"
        "\\end{equation}\n",
        "var: Document[0,55)\n"
        "  var: BlockList[0,55)\n"
        "    nul: DisplayFormula[0,15)\n"
        "    nul: BlankLine[15,16)\n"
        "    nul: DisplayFormula[16,55)\n");

    // Display formula with complex LaTeX
    TEST_AST("\\begin{align}\n"
        "\\frac{\\partial f}{\\partial x} &= \\lim_{h \\to 0} \\frac{f(x+h) - f(x)}{h} \\\\\n"
        "&= \\lim_{h \\to 0} \\frac{(x+h)^2 - x^2}{h}\n"
        "\\end{align}\n",
        "var: Document[0,143)\n"
        "  var: BlockList[0,143)\n"
        "    nul: DisplayFormula[0,143)\n");

    // Display formula with empty lines
    TEST_AST("$$\n"
        "E = mc^2\n"
        "\n"
        "F = ma\n"
        "$$\n",
        "var: Document[0,23)\n"
        "  var: BlockList[0,23)\n"
        "    nul: DisplayFormula[0,23)\n");

    return 0;
}
