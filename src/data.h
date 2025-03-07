#ifndef DATA_H
#define DATA_H

#include <stddef.h>

#include "data_structures.h"

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
    MDD_NODE_TYPE_LINK,
    MDD_NODE_TYPE_LINK_LABEL,
    MDD_NODE_TYPE_LINK_SOURCE,
    MDD_NODE_TYPE_LINK_TITLE,
    MDD_NODE_TYPE_LINK_SIZE,
    MDD_NODE_TYPE_LINK_REFERENCE,
    MDD_NODE_TYPE_REFERENCE,
    MDD_NODE_TYPE_AUTO_LINK_URL,
    MDD_NODE_TYPE_AUTO_LINK_EMAIL,
    MDD_NODE_TYPE_NOTE_REFERENCE,
    MDD_NODE_TYPE_NOTE,
    MDD_NODE_TYPE_NOTE_BLOCK,
    MDD_NODE_TYPE_INLINE_NOTE,
    MDD_NODE_TYPE_CODE,
    MDD_NODE_TYPE_INLINE_FORMULA,
    MDD_NODE_TYPE_DISPLAY_FORMULA,
    MDD_NODE_TYPE_MARK,
    MDD_NODE_TYPE_BLOCK_QUOTE,
    MDD_NODE_TYPE_FENCED_CODE_BLOCK,
    MDD_NODE_TYPE_HORIZONTAL_RULE,
    MDD_NODE_TYPE_DUMMY,

    MDD_NODE_TYPE_H1,
    MDD_NODE_TYPE_H2,
    MDD_NODE_TYPE_H3,
    MDD_NODE_TYPE_H4,
    MDD_NODE_TYPE_H5,
    MDD_NODE_TYPE_H6,

} mdd_node_type_t;

const char *mdd_node_type_to_string(mdd_node_type_t type);

// AST node data.
// Link specific data.
typedef struct mdd_node_type_link_data_tag {
    bool_t is_reference;
    char_array_t label;
    char_array_t source;
    char_array_t title;
    char_array_t reference;
    // -1 indicates not specified.
    int width;
    int height;
} mdd_node_type_link_data_t;

void mdd_node_type_link_data_finalize(mdd_node_type_link_data_t *obj);

// Reference specific data.
typedef struct mdd_node_type_reference_data_tag {
    char_array_t id;
    char_array_t source;
    char_array_t title;
} mdd_node_type_reference_data_t;

void mdd_node_type_reference_data_finalize(mdd_node_type_reference_data_t *obj);

// Note specific data.
typedef struct mdd_node_type_note_data_tag {
    char_array_t reference;
    char_array_t note;
} mdd_node_type_note_data_t;

void mdd_node_type_note_data_finalize(mdd_node_type_note_data_t *obj);

// Code block specific data.
typedef struct mdd_node_type_code_block_data_tag {
    char_array_t lang;
} mdd_node_type_code_block_data_t;

void mdd_node_type_code_block_data_finalize(mdd_node_type_code_block_data_t *obj);

// Label specific data.
typedef struct mdd_node_type_label_data_tag {
    char_array_t text;
} mdd_node_type_label_data_t;

void mdd_node_type_label_data_finalize(mdd_node_type_label_data_t *obj);

// Size specific data.
typedef struct mdd_node_type_size_data_tag {
    int width;
    int height;
} mdd_node_type_size_data_t;

void mdd_node_type_size_data_finalize(mdd_node_type_size_data_t *obj);

typedef union mdd_node_type_data_tag {
    mdd_node_type_link_data_t link_data;
    mdd_node_type_reference_data_t reference_data;
    mdd_node_type_label_data_t label_data;
    mdd_node_type_size_data_t size_data;
    mdd_node_type_note_data_t note_data;
    mdd_node_type_code_block_data_t code_block_data;
} mdd_node_type_data_t;

void mdd_node_type_data_finalize(mdd_node_type_t type, mdd_node_type_data_t *obj);

typedef struct mdd_node_data_tag {
    // TODO: use the built-in label of AST node.
    mdd_node_type_t type;
    // TODO: use the built-in range of AST node.
    range_t range;
    // Data for specific type.
    mdd_node_type_data_t *type_data;
} mdd_node_data_t;

void mdd_node_data_initialize(mdd_node_data_t *obj);
void mdd_node_data_finalize(mdd_node_data_t *obj);

inline static void mdd_node_data_assign(mdd_node_data_t *obj,
        mdd_node_type_t type, size_t start, size_t end) {
    obj->type = type;
    obj->range.start = start;
    obj->range.end = end;
}

inline static void mdd_node_data_set_type(mdd_node_data_t *obj,
        mdd_node_type_t type) {
    obj->type = type;
}

inline static void mdd_node_data_set_range(mdd_node_data_t *obj,
        size_t start, size_t end) {
    obj->range.start = start;
    obj->range.end = end;
}

int mdd_node_type_data_dump(char *buf, size_t len, const mdd_node_data_t *obj);

void mdd_node_type_label_data_new(mdd_node_data_t *obj, const char *text);
void mdd_node_type_label_data_new1(mdd_node_data_t *obj, const char *text, size_t len);

void mdd_node_type_link_data_new(mdd_node_data_t *obj, bool_t is_reference,
        char_array_t *label, char_array_t *source, char_array_t *title,
        char_array_t *reference, int width, int height);

void mdd_node_type_reference_data_new(mdd_node_data_t *obj,
        char_array_t *id, char_array_t *source, char_array_t *title);

void mdd_node_type_size_data_new(mdd_node_data_t *obj, int width, int height);

void mdd_node_type_note_data_new(mdd_node_data_t *obj,
        char_array_t *reference, char_array_t *note);

void mdd_node_type_code_block_data_new(mdd_node_data_t *obj, const char *lang);

// Context data during parse.
typedef struct mdd_data_tag {
    // Input string to parse.
    const unsigned char *input;
    size_t len;

    // Position in |input| that is going to be read currently.
    size_t cur;

    // For reference links and references.
    pointer_array_t reference_links;
    pointer_array_t references;

    // For note references and non-inline notes.
    pointer_array_t note_references;
    pointer_array_t notes;
} mdd_data_t;

void mdd_data_initialize(mdd_data_t *obj);
void mdd_data_finalize(mdd_data_t *obj);

// Used for reading input by the parser.
inline static int mdd_get_char_from_data(mdd_data_t *data) {
    int ret = -1;
    if (data->cur < data->len) {
        ret = (int)data->input[data->cur];
        ++data->cur;
    }
    return ret;
}

#endif
