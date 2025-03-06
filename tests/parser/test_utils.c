#include "test_utils.h"

#include <string.h>
#include <stdio.h>

#include "interface.h"

#define dump_node_type(node) mdd_node_type_to_string((node)->custom.type)
#define dump_node_type_data(buf, len, node) mdd_node_type_data_dump((buf), len, &(node)->custom)
#define dump_node_start(node) (node)->custom.range.start
#define dump_node_end(node) (node)->custom.range.end

#define add_and_check_buf() \
    do { \
        if (ret < 0) { \
            return ret; \
        } \
        total += ret; \
        if (total >= len) { \
            return total; \
        } \
    } while (0)

int dump_ast(const mddi_ast_node_t *obj, int depth, char *buf, size_t len) {
    const char *ast_node_type_strs[] = {"nul", "una", "bin", "ter", "var"};
    size_t idx = 0;
    int total = 0;
    if (obj) {
        int ret = snprintf(buf, len, "%*s%s: %s[%zu,%zu)",
                           2 * depth, "",
                           ast_node_type_strs[(int)obj->type],
                           dump_node_type(obj), dump_node_start(obj), dump_node_end(obj));
        add_and_check_buf();
        ret = dump_node_type_data(buf + total, len - total, obj);
        add_and_check_buf();
        ret = snprintf(buf + total, len - total, "\n");
        add_and_check_buf();

        switch (obj->type) {
        case MDDI_AST_NODE_TYPE_NULLARY:
            break;
        case MDDI_AST_NODE_TYPE_UNARY: {
            ret = dump_ast(obj->data.unary.node, depth + 1, buf + total, len - total);
            add_and_check_buf();
            break;
        }
        case MDDI_AST_NODE_TYPE_BINARY: {
            ret = dump_ast(obj->data.binary.node[0], depth + 1, buf + total, len - total);
            add_and_check_buf();
            ret = dump_ast(obj->data.binary.node[1], depth + 1, buf + total, len - total);
            add_and_check_buf();
            break;
        }
        case MDDI_AST_NODE_TYPE_TERNARY: {
            ret = dump_ast(obj->data.ternary.node[0], depth + 1, buf + total, len - total);
            add_and_check_buf();
            ret = dump_ast(obj->data.ternary.node[1], depth + 1, buf + total, len - total);
            add_and_check_buf();
            ret = dump_ast(obj->data.ternary.node[2], depth + 1, buf + total, len - total);
            add_and_check_buf();
            break;
        }
        case MDDI_AST_NODE_TYPE_VARIADIC: {
            {
                for (size_t i = 0; i < obj->data.variadic.len; ++i) {
                    ret = dump_ast(obj->data.variadic.node[i], depth + 1, buf + total, len - total);
                    add_and_check_buf();
                }
            }
            break;
        }
        }
    }
    else {
        total = snprintf(buf, len, "%*s(null)\n", 2 * depth, "");
    }

    return total;
}

#define BUF_LEN 4096u

int test_ast(const char *input, const char *expected_ast) {
    int passed = 0;
    char buffer[BUF_LEN + 1] = { 0 };
    mddi_ast_manager_t mgr;

    mddi_ast_node_t *ast = mdd_parse(&mgr, (const unsigned char *)input, strlen(input));
    if (ast) {
        int ret = dump_ast(ast, 0, buffer, BUF_LEN);
        if (ret > 0) {
            if (ret == strlen(expected_ast) && 0 == strncmp(expected_ast, buffer, ret)) {
                printf(">>> Test PASSED <<<\n");
                passed = 1;
            } else {
                printf(">>> Test FAILED <<<\n");
                printf(">>> EXPECTED:\n%s\n", expected_ast);
                printf(">>> ACTUAL:\n%s\n", buffer);
            }
        } else {
            printf(">>> Test ERROR <<<\n");
        }
    } else {
        if (strlen(expected_ast) == 0) {
            printf(">>> Test PASSED <<<\n");
            passed = 1;
        } else {
            printf(">>> Test FAILED <<<\n");
            printf(">>> EXPECTED:\n%s\n", expected_ast);
            printf(">>> ACTUAL:\nEMPTY AST\n");
        }
    }
    mdd_clear(&mgr, ast);
    return passed;
}
