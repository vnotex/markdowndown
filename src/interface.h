#ifndef INTERFACE_H
#define INTERFACE_H

#include "markdowndown.h"

// Parse |buf| with length |len|.
// Should call |mdd_clear(ast)| after the use of the AST.
mddi_ast_node_t *mdd_parse(mddi_ast_manager_t *mgr, const unsigned char *buf, size_t len);

void mdd_clear(mddi_ast_manager_t *mgr, mddi_ast_node_t *ast);

#endif
