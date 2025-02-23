#include "data_structures.h"

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _WIN32
#define strncpy_s(dest, dest_size, src, cnt) \
    do { \
        assert((dest_size) > (cnt));
        strncpy((dest), (src), (cnt)); \
        (dest)[(cnt)] = '\0'; \
    } while (0)
#endif

void mdd_char_array_initialize(char_array_t *obj) {
    obj->buf = NULL;
    obj->capacity = 0;
    obj->len = 0;
}

void mdd_char_array_finalize(char_array_t *obj) {
    free(obj->buf);
}

char_array_t mdd_char_array_new() {
    char_array_t tmp;
    mdd_char_array_initialize(&tmp);
    return tmp;
}

static size_t cal_next_capacity(size_t cap, size_t new_len) {
    if (cap >= new_len + 1) {
        // No change.
        return cap;
    }

    if (cap == 0) {
        cap = 256;
    }
    while (cap < new_len + 1 && cap != 0) {
        cap <<= 1;
    }
    if (cap == 0) {
        cap = new_len + 1;
    }
    return cap;
}

void mdd_char_array_resize(char_array_t *obj, size_t new_len) {
    const size_t cap = cal_next_capacity(obj->capacity, new_len);
    if (cap != obj->capacity) {
        char *new_buf = (char *)realloc(obj->buf, cap);
        if (!new_buf) {
            fprintf(stderr, "Out of memory\n");
            free(obj->buf);
            exit(1);
        }
        obj->buf = new_buf;
        obj->capacity = cap;
    }
    obj->len = new_len;
}

void mdd_char_array_clear(char_array_t *obj) {
    mdd_char_array_finalize(obj);
    mdd_char_array_initialize(obj);
}

void mdd_char_array_swap(char_array_t *a, char_array_t *b) {
    if (a == b) {
        return;
    }
    char_array_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void mdd_char_array_assign(char_array_t *obj, const char *text) {
    mdd_char_array_assign1(obj, text, text ? strlen(text) : 0);
}

void mdd_char_array_assign1(char_array_t *obj, const char *text, size_t len) {
    assert(len <= strlen(text));
    if (text && len > 0) {
        mdd_char_array_resize(obj, len);
        strncpy_s(obj->buf, len + 1, text, len);
    } else {
        mdd_char_array_clear(obj);
    }
}

bool_t mdd_char_array_equal(const char_array_t *a, const char_array_t *b) {
    if (a == b) {
        return BOOL_TRUE;
    }
    if (a == NULL || b == NULL) {
        return BOOL_FALSE;
    }
    if (a->len != b->len) {
        return BOOL_FALSE;
    }
    for (size_t i = 0; i < a->len; ++i) {
        if (a->buf[i] != b->buf[i]) {
            return BOOL_FALSE;
        }
    }
    return BOOL_TRUE;
}

bool_t mdd_char_array_empty(const char_array_t *obj) {
    return obj->len == 0 ? BOOL_TRUE : BOOL_FALSE;
}

const char *mdd_char_array_to_string(const char_array_t *obj) {
    if (obj->len == 0) {
        return "";
    } else {
        return obj->buf;
    }
}

char_array_t mdd_char_array_duplicate(const char_array_t *obj) {
    char_array_t new_chars = mdd_char_array_new();
    mdd_char_array_assign1(&new_chars, obj->buf, obj->len);
    return new_chars;
}

void mdd_pointer_array_initialize(pointer_array_t *obj) {
    obj->pbuf = NULL;
    obj->capacity = 0;
    obj->len = 0;
}

void mdd_pointer_array_finalize(pointer_array_t *obj) {
    // Objects in the array are not owned by us.
    free(obj->pbuf);
}

void mdd_pointer_array_add(pointer_array_t *obj, void *ele) {
    if (obj->len >= obj->capacity) {
        size_t cap = cal_next_capacity(obj->capacity, obj->len + 1);
        void **new_buf = (void **)realloc(obj->pbuf, cap);
        if (!new_buf) {
            fprintf(stderr, "Out of memory\n");
            free(obj->pbuf);
            exit(1);
        }
        obj->pbuf = new_buf;
        obj->capacity = cap;
    }
    obj->pbuf[obj->len++] = ele;
}
