#ifndef DATA_H
#define DATA_H

typedef struct range_tag {
    size_t start;
    size_t end;
} range_t;

inline static range_t mdd_range_empty(void) {
    const range_t r = { 0, 0 };
    return r;
}

inline static range_t mdd_range_new(size_t start, size_t end) {
    const range_t r = { start, end };
    return r;
}

// |a| contains |b|.
static int mdd_range_contains(const range_t *a, const range_t *b) {
    return (a->start <= b->start) && (a->end >= b->end);
}

typedef enum mdd_node_type_tag {
    MDD_NODE_TYPE_UNKNOWN,
    MDD_NODE_TYPE_DOCUMENT,
    MDD_NODE_TYPE_FRONT_MATTER,
    MDD_NODE_TYPE_BLOCK_LIST,
    MDD_NODE_TYPE_BLANK_LINE,
    MDD_NODE_TYPE_VERBATIM,
    MDD_NODE_TYPE_PLAIN,
    MDD_NODE_TYPE_INLINES,
    MDD_NODE_TYPE_STRONG,
    MDD_NODE_TYPE_EMPH,
    MDD_NODE_TYPE_STRIKE,
    MDD_NODE_TYPE_IMAGE,
    MDD_NODE_TYPE_HTML,
    MDD_NODE_TYPE_ENTITY,
    MDD_NODE_TYPE_LABEL,
    MDD_NODE_TYPE_LINK,
    MDD_NODE_TYPE_H1,
    MDD_NODE_TYPE_H2,
} mdd_node_type_t;

const char *mdd_node_type_to_string(mdd_node_type_t type);

// Context data during parse.
typedef struct mdd_data_tag {
    // Input string to parse.
    const unsigned char *input;
    size_t len;

    // Position in |input| that is going to be read currently.
    size_t cur;
} mdd_data_t;

void mdd_data_on_initialize(mdd_data_t *obj);
void mdd_data_on_finalize(mdd_data_t *obj);

// Used for reading input by the parser.
inline static int mdd_get_char_from_data(mdd_data_t *data) {
    int ret = -1;
    if (data->cur < data->len) {
        ret = (int)data->input[data->cur];
        ++data->cur;
    }
    return ret;
}

// AST node data.
typedef struct mdd_node_data_tag {
    mdd_node_type_t type;
    range_t range;
} mdd_node_data_t;

void mdd_node_data_on_initialize(mdd_node_data_t *obj);
void mdd_node_data_on_finalize(mdd_node_data_t *obj);

inline static void mdd_node_data_assign(mdd_node_data_t *obj,
        mdd_node_type_t type, size_t start, size_t end) {
    obj->type = type;
    obj->range.start = start;
    obj->range.end = end;
}

inline static void mdd_node_data_set_range(mdd_node_data_t *obj,
        size_t start, size_t end) {
    obj->range.start = start;
    obj->range.end = end;
}

#endif
