#include "test_utils.h"

#include <string.h>
#include <stdio.h>

#include "interface.h"

#define dump_node_type(node) mdd_node_type_to_string((node)->custom.type)
#define dump_node_start(node) (node)->custom.range.start
#define dump_node_end(node) (node)->custom.range.end

int dump_ast(const pcc_ast_node_t *obj, int depth, char *buf, size_t len) {
    size_t idx = 0;
    int total = 0;
    memset(buf, 0, len);
    if (obj) {
        switch (obj->type) {
        case PCC_AST_NODE_TYPE_NULLARY:
            total = snprintf(buf, len, "%*s%s: %s[%zu,%zu)\n", 2 * depth, "", "nul",
                    dump_node_type(obj), dump_node_start(obj), dump_node_end(obj));
            break;
        case PCC_AST_NODE_TYPE_UNARY: {
            int ret = snprintf(buf, len, "%*s%s: %s[%zu,%zu)\n", 2 * depth, "", "una",
                    dump_node_type(obj), dump_node_start(obj), dump_node_end(obj));
            if (ret <= 0) {
                return ret;
            }
            total += ret;

            ret = dump_ast(obj->data.unary.node, depth + 1, buf + total, len - total);
            if (ret <= 0) {
                return ret;
            }
            total += ret;
            break;
        }
        case PCC_AST_NODE_TYPE_BINARY: {
            int ret = snprintf(buf, len, "%*s%s: %s[%zu,%zu)\n", 2 * depth, "", "bin",
                    dump_node_type(obj), dump_node_start(obj), dump_node_end(obj));
            if (ret <= 0) {
                return ret;
            }
            total += ret;

            ret = dump_ast(obj->data.binary.node[0], depth + 1, buf + total, len - total);
            if (ret <= 0) {
                return ret;
            }
            total += ret;

            ret = dump_ast(obj->data.binary.node[1], depth + 1, buf + total, len - total);
            if (ret <= 0) {
                return ret;
            }
            total += ret;
            break;
        }
        case PCC_AST_NODE_TYPE_TERNARY: {
            int ret = snprintf(buf, len, "%*s%s: %s[%zu,%zu)\n", 2 * depth, "", "ter",
                    dump_node_type(obj), dump_node_start(obj), dump_node_end(obj));
            if (ret <= 0) {
                return ret;
            }
            total += ret;

            ret = dump_ast(obj->data.ternary.node[0], depth + 1, buf + total, len - total);
            if (ret <= 0) {
                return ret;
            }
            total += ret;

            ret = dump_ast(obj->data.ternary.node[1], depth + 1, buf + total, len - total);
            if (ret <= 0) {
                return ret;
            }
            total += ret;

            ret = dump_ast(obj->data.ternary.node[2], depth + 1, buf + total, len - total);
            if (ret <= 0) {
                return ret;
            }
            total += ret;
            break;
        }
        case PCC_AST_NODE_TYPE_VARIADIC: {
            int ret = snprintf(buf, len, "%*s%s: %s[%zu,%zu)\n", 2 * depth, "", "var",
                    dump_node_type(obj), dump_node_start(obj), dump_node_end(obj));
            if (ret <= 0) {
                return ret;
            }
            total += ret;

            {
                size_t i;
                for (i = 0; i < obj->data.variadic.len; i++) {
                    int ret = dump_ast(obj->data.variadic.node[i], depth + 1, buf + total, len - total);
                    if (ret <= 0) {
                        return ret;
                    }
                    total += ret;
                }
            }
            break;
        }
        default:
            total = snprintf(buf, len, "%*s%s: %s[%zu,%zu)\n", 2 * depth, "", "(unk)",
                    dump_node_type(obj), dump_node_start(obj), dump_node_end(obj));
            break;
        }
    }
    else {
        total = snprintf(buf, len, "%*s(null)\n", 2 * depth, "");
    }

    return total;
}

#define BUF_LEN 4096u

int test_ast_0(const char *input, const char *expected_ast) {
    return test_ast((const unsigned char *)input, strlen(input), expected_ast);
}

int test_ast(const unsigned char *input, size_t len, const char *expected_ast) {
    int passed = 0;
    char buffer[BUF_LEN + 1] = { 0 };
    pcc_ast_manager_t mgr;

    pcc_ast_node_t *ast = mdd_parse(&mgr, input, len);
    if (ast) {
        int ret = dump_ast(ast, 0, buffer, BUF_LEN);
        if (ret > 0) {
            if (0 == strncmp(expected_ast, buffer, ret)) {
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
