#include "data.h"

#include <memory.h>
#include <stdlib.h>

void mdd_data_on_initialize(mdd_data_t *obj) {
    obj->input = NULL;
    obj->len = 0;
    obj->cur = 0;
}

void mdd_data_on_finalize(mdd_data_t *obj) {
}

void mdd_node_data_on_initialize(mdd_node_data_t *obj) {
    obj->type = MDD_NODE_TYPE_UNKNOWN;
    obj->range = mdd_range_empty();
}

void mdd_node_data_on_finalize(mdd_node_data_t *obj) {
}

const char *mdd_node_type_to_string(mdd_node_type_t type) {
    switch (type) {
    case MDD_NODE_TYPE_UNKNOWN: return "Unknown";
    case MDD_NODE_TYPE_DOCUMENT: return "Document";
    case MDD_NODE_TYPE_FRONT_MATTER: return "FrontMatter";
    case MDD_NODE_TYPE_BLOCK_LIST: return "BlockList";
    case MDD_NODE_TYPE_BLOCK: return "Block";
    case MDD_NODE_TYPE_H1: return "H1";
    case MDD_NODE_TYPE_H2: return "H2";
    }
}
