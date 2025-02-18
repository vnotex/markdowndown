#include "data.h"

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mdd_data_initialize(mdd_data_t *obj) {
    obj->input = NULL;
    obj->len = 0;
    obj->cur = 0;
    mdd_pointer_array_initialize(&obj->reference_links);
    mdd_pointer_array_initialize(&obj->references);
}

void mdd_data_finalize(mdd_data_t *obj) {
    mdd_pointer_array_finalize(&obj->reference_links);
    mdd_pointer_array_finalize(&obj->references);
}

void mdd_node_data_initialize(mdd_node_data_t *obj) {
    obj->type = MDD_NODE_TYPE_UNKNOWN;
    obj->range = mdd_range_empty();
    obj->type_data = NULL;
}

void mdd_node_data_finalize(mdd_node_data_t *obj) {
    mdd_node_type_data_finalize(obj->type, obj->type_data);
}

void mdd_node_type_data_finalize(mdd_node_type_t type, mdd_node_type_data_t *obj) {
    if (!obj) {
        return;
    }
    switch (type) {
    case MDD_NODE_TYPE_IMAGE:
        __attribute__ ((fallthrough));
    case MDD_NODE_TYPE_LINK:
        mdd_node_type_link_data_finalize(&obj->link_data);
        break;
    case MDD_NODE_TYPE_REFERENCE:
        mdd_node_type_reference_data_finalize(&obj->reference_data);
        break;
    case MDD_NODE_TYPE_LINK_LABEL:
        __attribute__ ((fallthrough));
    case MDD_NODE_TYPE_LINK_REFERENCE:
        __attribute__ ((fallthrough));
    case MDD_NODE_TYPE_LINK_SOURCE:
        __attribute__ ((fallthrough));
    case MDD_NODE_TYPE_LINK_TITLE:
        mdd_node_type_label_data_finalize(&obj->label_data);
        break;
    case MDD_NODE_TYPE_LINK_SIZE:
        mdd_node_type_size_data_finalize(&obj->size_data);
        break;
    default:
        break;
    }
    free(obj);
}

static mdd_node_type_data_t *mdd_node_type_data_new() {
    mdd_node_type_data_t *data = (mdd_node_type_data_t *)malloc(sizeof(mdd_node_type_data_t));
    memset(data, 0, sizeof(mdd_node_type_data_t));
    return data;
}

void mdd_node_type_link_data_finalize(mdd_node_type_link_data_t *obj) {
    mdd_char_array_finalize(&obj->label);
    mdd_char_array_finalize(&obj->source);
    mdd_char_array_finalize(&obj->title);
    mdd_char_array_finalize(&obj->reference);
}

void mdd_node_type_reference_data_finalize(mdd_node_type_reference_data_t *obj) {
    mdd_char_array_finalize(&obj->id);
    mdd_char_array_finalize(&obj->source);
    mdd_char_array_finalize(&obj->title);
}

void mdd_node_type_label_data_finalize(mdd_node_type_label_data_t *obj) {
    mdd_char_array_finalize(&obj->text);
}

void mdd_node_type_size_data_finalize(mdd_node_type_size_data_t *obj) {
    // Do nothing.
}

void mdd_node_type_label_data_new(mdd_node_data_t *obj, const char *text) {
    mdd_node_type_label_data_new1(obj, text, text ? strlen(text) : 0);
}

void mdd_node_type_label_data_new1(mdd_node_data_t *obj, const char *text, size_t len) {
    assert(!obj->type_data);
    obj->type_data = mdd_node_type_data_new();
    mdd_char_array_assign1(&obj->type_data->label_data.text, text, len);
}

void mdd_node_type_link_data_new(mdd_node_data_t *obj, bool_t is_reference,
        char_array_t *label, char_array_t *source, char_array_t *title,
        char_array_t *reference, int width, int height) {
    assert(!obj->type_data);
    obj->type_data = mdd_node_type_data_new();
    mdd_node_type_link_data_t *link_data = &obj->type_data->link_data;
    link_data->is_reference = is_reference;
    link_data->width = width;
    link_data->height = height;
    if (label) {
        mdd_char_array_swap(&link_data->label, label);
    }
    if (source) {
        mdd_char_array_swap(&link_data->source, source);
    }
    if (title) {
        mdd_char_array_swap(&link_data->title, title);
    }
    if (reference) {
        mdd_char_array_swap(&link_data->reference, reference);
    }
}

void mdd_node_type_reference_data_new(mdd_node_data_t *obj,
        char_array_t *id, char_array_t *source, char_array_t *title) {
    assert(!obj->type_data);
    obj->type_data = mdd_node_type_data_new();
    mdd_node_type_reference_data_t *reference_data = &obj->type_data->reference_data;
    if (id) {
        mdd_char_array_swap(&reference_data->id, id);
    }
    if (source) {
        mdd_char_array_swap(&reference_data->source, source);
    }
    if (title) {
        mdd_char_array_swap(&reference_data->title, title);
    }
}

void mdd_node_type_size_data_new(mdd_node_data_t *obj, int width, int height) {
    assert(!obj->type_data);
    obj->type_data = mdd_node_type_data_new();
    obj->type_data->size_data.width = width;
    obj->type_data->size_data.height = height;
}

const char *mdd_node_type_to_string(mdd_node_type_t type) {
    switch (type) {
    case MDD_NODE_TYPE_UNKNOWN: return "Unknown";
    case MDD_NODE_TYPE_DOCUMENT: return "Document";
    case MDD_NODE_TYPE_FRONT_MATTER: return "FrontMatter";
    case MDD_NODE_TYPE_BLOCK_LIST: return "BlockList";
    case MDD_NODE_TYPE_BLANK_LINE: return "BlankLine";
    case MDD_NODE_TYPE_VERBATIM: return "Verbatim";
    case MDD_NODE_TYPE_PLAIN: return "Plain";
    case MDD_NODE_TYPE_INLINES: return "Inlines";
    case MDD_NODE_TYPE_STRONG: return "Strong";
    case MDD_NODE_TYPE_EMPH: return "Emph";
    case MDD_NODE_TYPE_STRIKE: return "Strike";
    case MDD_NODE_TYPE_IMAGE: return "Image";
    case MDD_NODE_TYPE_HTML: return "HTML";
    case MDD_NODE_TYPE_ENTITY: return "Entity";
    case MDD_NODE_TYPE_LINK_LABEL: return "LinkLabel";
    case MDD_NODE_TYPE_LINK_REFERENCE: return "LinkReference";
    case MDD_NODE_TYPE_LINK_SOURCE: return "LinkSource";
    case MDD_NODE_TYPE_LINK_TITLE: return "LinkTitle";
    case MDD_NODE_TYPE_LINK_SIZE: return "LinkSize";
    case MDD_NODE_TYPE_LINK: return "Link";
    case MDD_NODE_TYPE_REFERENCE: return "Reference";
    case MDD_NODE_TYPE_DUMMY: return "Dummy";
    case MDD_NODE_TYPE_H1: return "H1";
    case MDD_NODE_TYPE_H2: return "H2";
    }
}

int mdd_node_type_data_dump(char *buf, size_t len, const mdd_node_data_t *obj) {
    if (!obj->type_data) {
        return 0;
    }

    switch (obj->type) {
    case MDD_NODE_TYPE_IMAGE:
        __attribute__ ((fallthrough));
    case MDD_NODE_TYPE_LINK: {
        const mdd_node_type_link_data_t *data = &obj->type_data->link_data;
        return snprintf(buf, len, "{%d|%s|%s|%s|%s|%dx%d}",
                data->is_reference,
                mdd_char_array_to_string(&data->label),
                mdd_char_array_to_string(&data->source),
                mdd_char_array_to_string(&data->title),
                mdd_char_array_to_string(&data->reference),
                data->width, data->height);
        break;
    }
    case MDD_NODE_TYPE_REFERENCE: {
        const mdd_node_type_reference_data_t *data = &obj->type_data->reference_data;
        return snprintf(buf, len, "{%s|%s|%s}",
                mdd_char_array_to_string(&data->id),
                mdd_char_array_to_string(&data->source),
                mdd_char_array_to_string(&data->title));
        break;
    }
    default:
        break;
    }

    return 0;
}
