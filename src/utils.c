#include "utils.h"

#include <assert.h>

mddi_ast_node_t *mdd_node_create_nullary(mddi_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end) {
    mddi_ast_node_t *const obj = mddi_ast_node__create_nullary(mgr,
            mddi_ast_range__new(start, end), 0);
    mdd_node_data_assign(&obj->custom, type, start, end);
    return obj;
}

mddi_ast_node_t *mdd_node_create_unary(mddi_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end,
        mddi_ast_node_t *node) {
    mddi_ast_node_t *const obj = mddi_ast_node__create_unary(mgr,
            mddi_ast_range__new(start, end), 0, node);
    mdd_node_data_assign(&obj->custom, type, start, end);
    assert(mdd_range_contains(&obj->custom.range, &node->custom.range));
    return obj;
}

mddi_ast_node_t *mdd_node_create_binary(mddi_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end,
        mddi_ast_node_t *node0, mddi_ast_node_t *node1) {
    mddi_ast_node_t *const obj = mddi_ast_node__create_binary(mgr,
            mddi_ast_range__new(start, end), 0, node0, node1);
    mdd_node_data_assign(&obj->custom, type, start, end);
    assert(mdd_range_contains(&obj->custom.range, &node0->custom.range));
    assert(mdd_range_contains(&obj->custom.range, &node1->custom.range));
    return obj;
}

mddi_ast_node_t *mdd_node_create_ternary(mddi_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end,
        mddi_ast_node_t *node0, mddi_ast_node_t *node1, mddi_ast_node_t *node2) {
    mddi_ast_node_t *const obj = mddi_ast_node__create_ternary(mgr,
            mddi_ast_range__new(start, end), 0, node0, node1, node2);
    mdd_node_data_assign(&obj->custom, type, start, end);
    assert(mdd_range_contains(&obj->custom.range, &node0->custom.range));
    assert(mdd_range_contains(&obj->custom.range, &node1->custom.range));
    assert(mdd_range_contains(&obj->custom.range, &node2->custom.range));
    return obj;
}

mddi_ast_node_t *mdd_node_create_variadic(mddi_ast_manager_t *mgr,
        mdd_node_type_t type, size_t start, size_t end) {
    mddi_ast_node_t *const obj = mddi_ast_node__create_variadic(mgr,
            mddi_ast_range__new(start, end), 0);
    mdd_node_data_assign(&obj->custom, type, start, end);
    return obj;
}

void mdd_node_append_child(mddi_ast_node_t *parent, mddi_ast_node_t *node) {
    if (!node) {
        return;
    }
    // Assume that node does not have a parent yet.
    assert(!node->parent);
    mddi_ast_node__add_child(parent, node);
    // Do we need to take care of the range in the custom data?
}

mdd_node_type_label_data_t *mdd_node_type_data_get_label(mddi_ast_node_t *node) {
    if (!node) {
        return NULL;
    }

    mdd_node_data_t *obj = &node->custom;
    if (!obj->type_data) {
        return NULL;
    }

    if (obj->type == MDD_NODE_TYPE_LINK_LABEL ||
        obj->type == MDD_NODE_TYPE_LINK_REFERENCE ||
        obj->type == MDD_NODE_TYPE_LINK_SOURCE ||
        obj->type == MDD_NODE_TYPE_LINK_TITLE) {
        return &obj->type_data->label_data;
    }

    return NULL;
}

mdd_node_type_size_data_t *mdd_node_type_data_get_size(mddi_ast_node_t *node) {
    if (!node) {
        return NULL;
    }

    mdd_node_data_t *obj = &node->custom;
    if (!obj->type_data) {
        return NULL;
    }

    if (obj->type == MDD_NODE_TYPE_LINK_SIZE) {
        return &obj->type_data->size_data;
    }

    return NULL;
}
