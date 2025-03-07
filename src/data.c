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
    mdd_pointer_array_initialize(&obj->note_references);
    mdd_pointer_array_initialize(&obj->notes);
}

void mdd_data_finalize(mdd_data_t *obj) {
    mdd_pointer_array_finalize(&obj->reference_links);
    mdd_pointer_array_finalize(&obj->references);
    mdd_pointer_array_finalize(&obj->note_references);
    mdd_pointer_array_finalize(&obj->notes);
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
        // Fallthrough.
    case MDD_NODE_TYPE_LINK:
        // Fallthrough.
    case MDD_NODE_TYPE_AUTO_LINK_URL:
        // Fallthrough.
    case MDD_NODE_TYPE_AUTO_LINK_EMAIL:
        mdd_node_type_link_data_finalize(&obj->link_data);
        break;
    case MDD_NODE_TYPE_REFERENCE:
        mdd_node_type_reference_data_finalize(&obj->reference_data);
        break;
    case MDD_NODE_TYPE_NOTE_REFERENCE:
        // Fallthrough.
    case MDD_NODE_TYPE_NOTE:
        // Fallthrough.
    case MDD_NODE_TYPE_INLINE_NOTE:
        mdd_node_type_note_data_finalize(&obj->note_data);
        break;
    case MDD_NODE_TYPE_LINK_LABEL:
        // Fallthrough.
    case MDD_NODE_TYPE_LINK_REFERENCE:
        // Fallthrough.
    case MDD_NODE_TYPE_LINK_SOURCE:
        // Fallthrough.
    case MDD_NODE_TYPE_LINK_TITLE:
        // Fallthrough.
        // Headings.
    case MDD_NODE_TYPE_H1:
        // Fallthrough.
    case MDD_NODE_TYPE_H2:
        // Fallthrough.
    case MDD_NODE_TYPE_H3:
        // Fallthrough.
    case MDD_NODE_TYPE_H4:
        // Fallthrough.
    case MDD_NODE_TYPE_H5:
        // Fallthrough.
    case MDD_NODE_TYPE_H6:
        mdd_node_type_label_data_finalize(&obj->label_data);
        break;
    case MDD_NODE_TYPE_LINK_SIZE:
        mdd_node_type_size_data_finalize(&obj->size_data);
        break;
    case MDD_NODE_TYPE_FENCED_CODE_BLOCK:
        mdd_node_type_code_block_data_finalize(&obj->code_block_data);
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

void mdd_node_type_note_data_finalize(mdd_node_type_note_data_t *obj) {
    mdd_char_array_finalize(&obj->reference);
    mdd_char_array_finalize(&obj->note);
}

void mdd_node_type_code_block_data_finalize(mdd_node_type_code_block_data_t *obj) {
    mdd_char_array_finalize(&obj->lang);
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

void mdd_node_type_note_data_new(mdd_node_data_t *obj,
        char_array_t *reference, char_array_t *note) {
    assert(!obj->type_data);
    obj->type_data = mdd_node_type_data_new();
    mdd_node_type_note_data_t *note_data = &obj->type_data->note_data;
    if (reference) {
        mdd_char_array_swap(&note_data->reference, reference);
    }
    if (note) {
        mdd_char_array_swap(&note_data->note, note);
    }
}

void mdd_node_type_code_block_data_new(mdd_node_data_t *obj, const char *lang) {
    assert(!obj->type_data);
    obj->type_data = mdd_node_type_data_new();
    mdd_node_type_code_block_data_t *code_block_data = &obj->type_data->code_block_data;
    mdd_char_array_assign(&obj->type_data->code_block_data.lang, lang);
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
    case MDD_NODE_TYPE_AUTO_LINK_URL: return "AutoLinkUrl";
    case MDD_NODE_TYPE_AUTO_LINK_EMAIL: return "AutoLinkEmail";
    case MDD_NODE_TYPE_NOTE_REFERENCE: return "NoteReference";
    case MDD_NODE_TYPE_INLINE_NOTE: return "InlineNote";
    case MDD_NODE_TYPE_NOTE: return "Note";
    case MDD_NODE_TYPE_NOTE_BLOCK: return "NoteBlock";
    case MDD_NODE_TYPE_CODE: return "Code";
    case MDD_NODE_TYPE_INLINE_FORMULA: return "InlineFormula";
    case MDD_NODE_TYPE_DISPLAY_FORMULA: return "DisplayFormula";
    case MDD_NODE_TYPE_MARK: return "Mark";
    case MDD_NODE_TYPE_BLOCK_QUOTE: return "BlockQuote";
    case MDD_NODE_TYPE_FENCED_CODE_BLOCK: return "FencedCodeBlock";
    case MDD_NODE_TYPE_HORIZONTAL_RULE: return "HorizontalRule";
    case MDD_NODE_TYPE_DUMMY: return "Dummy";
    case MDD_NODE_TYPE_H1: return "H1";
    case MDD_NODE_TYPE_H2: return "H2";
    case MDD_NODE_TYPE_H3: return "H3";
    case MDD_NODE_TYPE_H4: return "H4";
    case MDD_NODE_TYPE_H5: return "H5";
    case MDD_NODE_TYPE_H6: return "H6";
    }
}

int mdd_node_type_data_dump(char *buf, size_t len, const mdd_node_data_t *obj) {
    if (!obj->type_data) {
        return 0;
    }

    switch (obj->type) {
    case MDD_NODE_TYPE_IMAGE:
        // Fallthrough.
    case MDD_NODE_TYPE_AUTO_LINK_URL:
        // Fallthrough.
    case MDD_NODE_TYPE_AUTO_LINK_EMAIL:
        // Fallthrough.
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
    case MDD_NODE_TYPE_NOTE:
        // Fallthrough.
    case MDD_NODE_TYPE_INLINE_NOTE:
        // Fallthrough.
    case MDD_NODE_TYPE_NOTE_REFERENCE: {
        const mdd_node_type_note_data_t *data = &obj->type_data->note_data;
        return snprintf(buf, len, "{%s|%s}",
                mdd_char_array_to_string(&data->reference),
                mdd_char_array_to_string(&data->note));
        break;
    }
    case MDD_NODE_TYPE_FENCED_CODE_BLOCK: {
        const mdd_node_type_code_block_data_t *data = &obj->type_data->code_block_data;
        return snprintf(buf, len, "{%s}",
                mdd_char_array_to_string(&data->lang));
        break;
    }
    case MDD_NODE_TYPE_H1:
        // Fallthrough.
    case MDD_NODE_TYPE_H2:
        // Fallthrough.
    case MDD_NODE_TYPE_H3:
        // Fallthrough.
    case MDD_NODE_TYPE_H4:
        // Fallthrough.
    case MDD_NODE_TYPE_H5:
        // Fallthrough.
    case MDD_NODE_TYPE_H6: {
        const mdd_node_type_label_data_t *data = &obj->type_data->label_data;
        return snprintf(buf, len, "{%s}",
                mdd_char_array_to_string(&data->text));
        break;
    }
    default:
        break;
    }

    return 0;
}
