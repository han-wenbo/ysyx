#include <stdbool.h>
#include <stddef.h>

#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__
typedef struct { 
    void* buffer;        
    int head;              
    int capacity;          
    size_t element_size; 
} ringbuf_t;

typedef void (*rb_iter_cb) (void * element, void *user_data);

bool ringbuf_init(ringbuf_t * r, size_t capacity, size_t element_size);
bool ringbuf_enq(ringbuf_t *r, const void * e);
void ringbuf_foreach(ringbuf_t *r, rb_iter_cb callback, void * use_data); 
bool ringbuf_free(ringbuf_t *r);

#endif
