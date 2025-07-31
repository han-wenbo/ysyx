#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


#include <structure.h>

#ifdef ____ringbuf_debug
typedef struct {
    void* buffer;        
    int head; // Index pointing to the next position to write a new element;
    size_t element_num;
    size_t capacity;
    size_t element_size;
} ringbuf_t;

typedef void (*rb_iter_cb) (void * element, void *user_data);

bool ringbuf_init(ringbuf_t * r, size_t capacity, size_t element_size);
bool ringbuf_enq(ringbuf_t *r, const void * e);
bool ringbuf_foreach(ringbuf_t *r, rb_iter_cb callback, void * use_data);
bool ringbuf_free(ringbuf_t *r);
#endif 
bool ringbuf_init(ringbuf_t * r, size_t capacity, size_t element_size) {
  // Ensure r->buffer == NULL is to prevent memory leaks.
  if(capacity == 0 || element_size == 0 || r == NULL || r->buffer != NULL) return false;
 
  r->buffer = malloc(capacity * element_size);
  if(r == NULL) 
    return false;

  r->head = 0;

  r->element_num = 0;

  r->capacity = capacity;

  r->element_size = element_size;
  return true;
}

bool ringbuf_enq(ringbuf_t *r, const void * e) {
   if(e == NULL || r == NULL || r->buffer == NULL)  return false;
   assert(r->element_num <= r->capacity); 
   assert(r->head < r->capacity);  

   memcpy((char *)r->buffer + (r->head * r->element_size), e, r->element_size); 

   r->head = r->head + 1 == r->capacity ? 0 : r->head + 1;  
 
   r->element_num = r->element_num  == r->capacity ? r->element_num : r->element_num + 1;

   assert(r->element_num <= r->capacity);

   return true;
}

bool ringbuf_free(ringbuf_t *r) {
   if(r == NULL || r->buffer == NULL) return false;
   free(r->buffer); 
   r->buffer = NULL;
   return true;
}

bool ringbuf_foreach(ringbuf_t *r, rb_iter_cb callback, void * user_data){
  if(r == NULL || r->buffer == NULL || callback == NULL)  return false;
  assert(r->element_num <= r->capacity);
  assert(r->head < r->capacity);
  for( size_t i = 0; i < r->element_num; i++) {

    callback((char*) r->buffer + i * r->element_size, user_data);

  }
  return true;
}
bool ringbuf_reset(ringbuf_t *r){
  if(r == NULL || r->buffer == NULL)  return false;  
  r->element_num = 0;
  r->head = 0;
  return true;
}

#ifdef ____ringbuf_debug
static void rb_sum(void *e, void * user_data){
   *(int *) user_data +=  *(int *) e;
}


int main() {
 ringbuf_t r; 
 assert(ringbuf_init(&r, 0, sizeof(int)) == false);
 assert(ringbuf_init(&r, 5, 0) == false);
 
 assert(ringbuf_init(&r, 10, sizeof(int))  == true);
 
 for(int i = 0; i < 10; i++) {
   assert(ringbuf_enq(&r, &i) == true); 
 }

 int sum = 0;
 ringbuf_foreach(&r, rb_sum, &sum);
 assert(sum == 45);
 
 sum = 88888;
 
 ringbuf_free(&r);
 ringbuf_init(&r, 10, sizeof(int));
 ringbuf_foreach(&r, rb_sum, &sum);
 assert( sum == 88888);

  for(int i = 0; i < 10; i++) {                                                                             
     assert(ringbuf_enq(&r, &i) == true);                                                                    
   }   

  assert(ringbuf_reset(&r) == true);
  ringbuf_foreach(&r, rb_sum, &sum); 
  assert(sum == 88888);

  assert(ringbuf_free(&r) == true); 
  assert(ringbuf_free(&r) == false);
  assert(ringbuf_reset(&r) == false);

  sum = 0;
 ringbuf_free(&r);
  assert(ringbuf_init(&r, 10,sizeof(int)) == true);
  for (int j = 0; j < 100; j++) {
        for(int i = 0; i < 10; i++) {                                                                                                                          
          assert(ringbuf_enq(&r, &i) == true);                                                                                                                
        }    
  }
 ringbuf_foreach(&r, rb_sum, &sum);
 assert(sum == 45);

 assert(ringbuf_reset(&r) == true);
 int a = 88;
 sum = 0;
 assert(ringbuf_enq(&r, &a) == true);
 ringbuf_foreach(&r, rb_sum, &sum);
 assert(sum == 88);
 assert(ringbuf_free(&r) == true); 

 return 0;
}
#endif
