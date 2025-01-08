#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>

#include "markdowndown.h"

int dump_ast(const pcc_ast_node_t *obj, int depth, char *buf, size_t len);

int test_ast(const unsigned char *input, size_t len, const char *expected_ast);

int test_ast_0(const char *input, const char *expected_ast);

#define TEST_AST(X, Y) do { if (test_ast_0((X), (Y)) == 0) return -1; } while (0)

static int test_case_idx = 0;

#define CASE(func) do { printf("=== CASE %d ===\n", test_case_idx++); if (func() <= 0) return -1; } while (0)

#endif
