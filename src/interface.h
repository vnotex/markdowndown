#ifndef INTERFACE_H
#define INTERFACE_H

#include "markdowndown.h"

// Parse |buf| with length |len|.
// Should call |mdd_clear(ast)| after the use of the AST.
pcc_ast_node_t *mdd_parse(pcc_ast_manager_t *mgr, const unsigned char *buf, size_t len);

void mdd_clear(pcc_ast_manager_t *mgr, pcc_ast_node_t *ast);

#endif
