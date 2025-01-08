#ifndef UTILS_H
#define UTILS_H

#include "markdowndown.h"

#define mdd_node_create_0(type, start, end) mdd_node_create_nullary(auxil, (type), (start), (end))
#define mdd_node_create_1(type, start, end, node) mdd_node_create_unary(auxil, (type), (start), (end), (node))
#define mdd_node_create_2(type, start, end, node0, node1) mdd_node_create_binary(auxil, (type), (start), (end), (node0), (node1))
#define mdd_node_create_3(type, start, end, node0, node1, node2) mdd_node_create_ternary(auxil, (type), (start), (end), (node0), (node1), (node2))
#define mdd_node_create_v(type, start, end) mdd_node_create_variadic(auxil, (type), (start), (end))

pcc_ast_node_t *mdd_node_create_nullary(pcc_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end);
pcc_ast_node_t *mdd_node_create_unary(pcc_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end,
        pcc_ast_node_t *node);
pcc_ast_node_t *mdd_node_create_binary(pcc_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end,
        pcc_ast_node_t *node0, pcc_ast_node_t *node1);
pcc_ast_node_t *mdd_node_create_ternary(pcc_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end,
        pcc_ast_node_t *node0, pcc_ast_node_t *node1, pcc_ast_node_t *node2);
pcc_ast_node_t *mdd_node_create_variadic(pcc_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end);

void mdd_node_append_child(pcc_ast_node_t *parent, pcc_ast_node_t *node);

#endif
