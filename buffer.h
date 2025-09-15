#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>

typedef struct gap_buf {
    char   *buf;
    size_t  capacity;
    size_t  gap_start;
    size_t  gap_end;
} gb;


gb *gb_new(size_t size);
void gb_free(gb *g);
void gb_left(gb *g);
void gb_right(gb *g);

void gb_insert_at_back(gb *b, char *new_buf, size_t new_size);

int gb_grow(gb *g, size_t k);
int gb_insert_char(gb *g, char input);
void gb_backspace(gb *g);

static inline size_t gb_front_len(const gb *g) { return g->gap_start; }
static inline size_t gb_back_len (const gb *g) { return g->capacity - g->gap_end; }
static inline size_t gb_text_len (const gb *g) { return gb_front_len(g) + gb_back_len(g); }


#endif