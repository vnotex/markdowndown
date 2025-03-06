#include "interface.h"

#include <assert.h>
#include <memory.h>
#include <stdio.h>

#include "data.h"
#include "markdowndown.h"

static void validate_reference_links(mddi_ast_manager_t *mgr) {
    const pointer_array_t *links = &mgr->custom.reference_links;
    const pointer_array_t *refs = &mgr->custom.references;
    if (links->len == 0) {
        return;
    }

    mdd_pointer_array_for_each(links, link)
        mdd_node_data_t *link_node = &((mddi_ast_node_t *)link)->custom;
        mdd_node_type_link_data_t *link_node_data = &link_node->type_data->link_data;
        bool_t found = BOOL_FALSE;
        mdd_pointer_array_for_each(refs, ref)
            mdd_node_data_t *ref_node = &((mddi_ast_node_t *)ref)->custom;
            mdd_node_type_reference_data_t *ref_node_data = &ref_node->type_data->reference_data;
            assert(link_node_data->is_reference == BOOL_TRUE);
            if (mdd_char_array_equal(&link_node_data->reference, &ref_node_data->id)) {
                assert(mdd_char_array_empty(&link_node_data->title));
                assert(mdd_char_array_empty(&link_node_data->source));
                link_node_data->source = mdd_char_array_duplicate(&ref_node_data->source);
                link_node_data->title = mdd_char_array_duplicate(&ref_node_data->title);
                found = BOOL_TRUE;
                break;
            }
        end_for_each
        if (!found) {
            // Transform invalid ref links to dummy elements.
            mddi_ast_node_t *node = (mddi_ast_node_t *)link;
            assert(node->type == MDDI_AST_NODE_TYPE_VARIADIC);
            for (size_t i = 0; i < node->data.variadic.len; ++i) {
                mdd_node_data_t *child_data = &node->data.variadic.node[i]->custom;
                mdd_node_type_t type = child_data->type;
                assert(type == MDD_NODE_TYPE_LINK_LABEL ||
                       type == MDD_NODE_TYPE_LINK_REFERENCE ||
                       type == MDD_NODE_TYPE_LINK_SOURCE ||
                       type == MDD_NODE_TYPE_LINK_TITLE ||
                       type == MDD_NODE_TYPE_LINK_SIZE);
                mdd_node_type_data_finalize(type, child_data->type_data);
                child_data->type_data = NULL;
                child_data->type = MDD_NODE_TYPE_DUMMY;
            }
            mdd_node_type_data_finalize(link_node->type, link_node->type_data);
            link_node->type_data = NULL;
            link_node->type = MDD_NODE_TYPE_DUMMY;
        }
    end_for_each
}

static void validate_note_references(mddi_ast_manager_t *mgr) {
    const pointer_array_t *refs = &mgr->custom.note_references;
    const pointer_array_t *notes = &mgr->custom.notes;
    if (refs->len == 0) {
        return;
    }

    mdd_pointer_array_for_each(refs, ref)
        mdd_node_data_t *ref_node = &((mddi_ast_node_t *)ref)->custom;
        mdd_node_type_note_data_t *ref_node_data = &ref_node->type_data->note_data;
        bool_t found = BOOL_FALSE;
        mdd_pointer_array_for_each(notes, note)
            mdd_node_data_t *note_node = &((mddi_ast_node_t *)note)->custom;
            mdd_node_type_note_data_t *note_node_data = &note_node->type_data->note_data;
            if (mdd_char_array_equal(&ref_node_data->reference, &note_node_data->reference)) {
                assert(mdd_char_array_empty(&ref_node_data->note));
                ref_node_data->note = mdd_char_array_duplicate(&note_node_data->note);
                found = BOOL_TRUE;
                break;
            }
        end_for_each
        if (!found) {
            // Transform invalid note refs to dummy elements.
            mddi_ast_node_t *node = (mddi_ast_node_t *)ref;
            assert(node->type == MDDI_AST_NODE_TYPE_NULLARY);
            mdd_node_type_data_finalize(ref_node->type, ref_node->type_data);
            ref_node->type_data = NULL;
            ref_node->type = MDD_NODE_TYPE_DUMMY;
        }
    end_for_each
}


mddi_ast_node_t *mdd_parse(mddi_ast_manager_t *mgr, const unsigned char *buf, size_t len) {
    mddi_ast_manager__initialize(mgr);
    mgr->custom.input = buf;
    mgr->custom.len = len;

    mddi_context_t *ctx = mddi_create(mgr);
    mddi_ast_node_t *ast = NULL;
    mddi_parse(ctx, &ast);
    validate_reference_links(mgr);
    validate_note_references(mgr);
    mddi_destroy(ctx);
    return ast;
}

void mdd_clear(mddi_ast_manager_t *mgr, mddi_ast_node_t *ast) {
    if (ast) {
        mddi_ast_node__destroy(ast);
    }
    mddi_ast_manager__finalize(mgr);
}
