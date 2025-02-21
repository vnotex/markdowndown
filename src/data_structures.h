#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stddef.h>

typedef enum bool_tag {
    BOOL_FALSE = 0,
    BOOL_TRUE
} bool_t;

typedef struct char_array_tag {
    char *buf;
    // Pay attention to the nul terminator.
    size_t capacity;
    // Excluding the nul terminator.
    size_t len;
} char_array_t;

void mdd_char_array_initialize(char_array_t *obj);
void mdd_char_array_finalize(char_array_t *obj);
char_array_t mdd_char_array_new();
void mdd_char_array_resize(char_array_t *obj, size_t new_len);
void mdd_char_array_clear(char_array_t *obj);
void mdd_char_array_swap(char_array_t *a, char_array_t *b);
void mdd_char_array_assign(char_array_t *obj, const char *text);
void mdd_char_array_assign1(char_array_t *obj, const char *text, size_t len);
bool_t mdd_char_array_equal(const char_array_t *a, const char_array_t *b);
bool_t mdd_char_array_empty(const char_array_t *obj);
const char *mdd_char_array_to_string(const char_array_t *obj);
char_array_t mdd_char_array_duplicate(const char_array_t *obj);

typedef struct pointer_array_tag {
    // Do NOT own the void*.
    void **pbuf;
    size_t capacity;
    size_t len;
} pointer_array_t;

void mdd_pointer_array_initialize(pointer_array_t *obj);
void mdd_pointer_array_finalize(pointer_array_t *obj);
void mdd_pointer_array_add(pointer_array_t *obj, void *ele);

#define mdd_pointer_array_for_each(obj, iter) \
    for (size_t iii = 0; iii < (obj)->len; ++iii) { \
        void *iter = (obj)->pbuf[iii];
#define end_for_each }

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

#endif
