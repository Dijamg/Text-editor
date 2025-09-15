#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include "buffer.h"

#define gb_front_len(g) ((g)->gap_start)
#define gb_back_len(g) ((g)->capacity-(g)->gap_end)
#define gb_text_len(g) (gb_front_len(g)+gb_back_len(g))

gb *gb_new(size_t size){
    gb *g = malloc(sizeof(gb));
    if (!g) return NULL;

    g->buf = malloc(size);
    if(!g->buf){
        free(g);
        return NULL;
    }

    g->capacity=size;
    g->gap_start=0;
    g->gap_end=size;
    return g;
}

void gb_free(gb *g){
    if(!g) return;
    free(g->buf);
    free(g);
}

/*Copies the current back text and moves it to the end (after gap) of new gap buffer after resizing gap*/
void gb_insert_at_back(gb *g, char *new_buf, size_t new_size){
    char *to = new_buf + new_size - gb_back_len(g);
    char *from = g->buf + g->gap_end;
    size_t numBytes = gb_back_len(g);

    memcpy(to, from, numBytes);
}


void gb_left(gb *g){
    if(g->gap_start > 0){
        /*What happens here
        AB_ _CD ---> A_ _ BCD*/
        g->gap_start--;
        g->gap_end--;
        g->buf[g->gap_end] = g->buf[g->gap_start];
    }
}

void gb_right(gb *g){
    if(g->gap_end < g->capacity){
        /*What happens here
        AB_ _CD ---> ABC_ _D*/
        g->gap_start++;
        g->gap_end++;
        g->buf[g->gap_start] = g->buf[g->gap_end];
    }
}

int gb_grow(gb *g, size_t new_size){
    //First reallocate more memory to accomodate increased size
    char *new_buf = realloc(g->buf, new_size);
    if(!new_buf){
        return -1;
    }

    //move the current back text to its new position
    gb_insert_at_back(g, new_buf, new_size);

    g->buf = new_buf;
    g->gap_end = new_size - gb_back_len(g);
    g->capacity = new_size;

    return 0;
}

int gb_insert_char(gb *g, char input){
    //Add size to gap if needed.
    if(g->gap_end - g->gap_start < 1){
        if(gb_grow(g, g->capacity + 1) == -1){
            return -1;
        }
    }

    //insert the character and move start forward
    g->buf[g->gap_start] = input;
    g->gap_start++;

    return 0;
}

//on backspace we just move the start back by one so it overlaps the deleted letter
void gb_backspace(gb *g){
    if(g->gap_start > 0){
        g->gap_start--;
    }
}