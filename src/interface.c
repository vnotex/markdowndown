#include "interface.h"

#include <memory.h>
#include <stdio.h>

#include "markdowndown.h"

pcc_ast_node_t *mdd_parse(pcc_ast_manager_t *mgr, const unsigned char *buf, size_t len) {
    pcc_ast_manager__initialize(mgr);
    mgr->custom.input = buf;
    mgr->custom.len = len;

    mddi_context_t *ctx = mddi_create(mgr);
    pcc_ast_node_t *ast = NULL;
    mddi_parse(ctx, &ast);
    mddi_destroy(ctx);
    return ast;
}

void mdd_clear(pcc_ast_manager_t *mgr, pcc_ast_node_t *ast) {
    if (ast) {
        pcc_ast_node__destroy(ast);
    }
    pcc_ast_manager__finalize(mgr);
}
