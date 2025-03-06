#ifndef UTILS_H
#define UTILS_H

#include "markdowndown.h"

#define mdd_node_create_0(type, start, end) mdd_node_create_nullary(auxil, (type), (start), (end))
#define mdd_node_create_1(type, start, end, node) mdd_node_create_unary(auxil, (type), (start), (end), (node))
#define mdd_node_create_2(type, start, end, node0, node1) mdd_node_create_binary(auxil, (type), (start), (end), (node0), (node1))
#define mdd_node_create_3(type, start, end, node0, node1, node2) mdd_node_create_ternary(auxil, (type), (start), (end), (node0), (node1), (node2))
#define mdd_node_create_v(type, start, end) mdd_node_create_variadic(auxil, (type), (start), (end))

mddi_ast_node_t *mdd_node_create_nullary(mddi_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end);
mddi_ast_node_t *mdd_node_create_unary(mddi_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end,
        mddi_ast_node_t *node);
mddi_ast_node_t *mdd_node_create_binary(mddi_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end,
        mddi_ast_node_t *node0, mddi_ast_node_t *node1);
mddi_ast_node_t *mdd_node_create_ternary(mddi_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end,
        mddi_ast_node_t *node0, mddi_ast_node_t *node1, mddi_ast_node_t *node2);
mddi_ast_node_t *mdd_node_create_variadic(mddi_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end);

void mdd_node_append_child(mddi_ast_node_t *parent, mddi_ast_node_t *node);

mdd_node_type_label_data_t *mdd_node_type_data_get_label(mddi_ast_node_t *node);

mdd_node_type_size_data_t *mdd_node_type_data_get_size(mddi_ast_node_t *node);

#endif
