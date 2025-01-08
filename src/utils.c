#include "utils.h"

#include <assert.h>

pcc_ast_node_t *mdd_node_create_nullary(pcc_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end) {
    pcc_ast_node_t *const obj = pcc_ast_node__create_nullary(mgr);
    mdd_node_data_assign(&obj->custom, type, start, end);
    return obj;
}

pcc_ast_node_t *mdd_node_create_unary(pcc_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end,
        pcc_ast_node_t *node) {
    pcc_ast_node_t *const obj = pcc_ast_node__create_unary(mgr, node);
    mdd_node_data_assign(&obj->custom, type, start, end);
    assert(mdd_range_contains(&obj->custom.range, &node->custom.range));
    return obj;
}

pcc_ast_node_t *mdd_node_create_binary(pcc_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end,
        pcc_ast_node_t *node0, pcc_ast_node_t *node1) {
    pcc_ast_node_t *const obj = pcc_ast_node__create_binary(mgr, node0, node1);
    mdd_node_data_assign(&obj->custom, type, start, end);
    assert(mdd_range_contains(&obj->custom.range, &node0->custom.range));
    assert(mdd_range_contains(&obj->custom.range, &node1->custom.range));
    return obj;
}

pcc_ast_node_t *mdd_node_create_ternary(pcc_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end,
        pcc_ast_node_t *node0, pcc_ast_node_t *node1, pcc_ast_node_t *node2) {
    pcc_ast_node_t *const obj = pcc_ast_node__create_ternary(mgr, node0, node1, node2);
    mdd_node_data_assign(&obj->custom, type, start, end);
    assert(mdd_range_contains(&obj->custom.range, &node0->custom.range));
    assert(mdd_range_contains(&obj->custom.range, &node1->custom.range));
    assert(mdd_range_contains(&obj->custom.range, &node2->custom.range));
    return obj;
}

pcc_ast_node_t *mdd_node_create_variadic(pcc_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end) {
    pcc_ast_node_t *const obj = pcc_ast_node__create_variadic(mgr);
    mdd_node_data_assign(&obj->custom, type, start, end);
    return obj;
}

void mdd_node_append_child(pcc_ast_node_t *parent, pcc_ast_node_t *node) {
    if (!node) {
        return;
    }
    // Assume that node does not have a parent yet.
    assert(!node->parent);
    pcc_ast_node__add_child(parent, node);
    // Do we need to take care of the range in the custom data?
}
