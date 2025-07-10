#include <stdbool.h>
#include <stddef.h>
//#include <structure.h>
#include <assert.h>
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

bool ringbuf_init(ringbuf_t * r, size_t capacity, size_t element_size) {

  return false;
}

bool ringbuf_enq(ringbuf_t *r, const void * e) {

   return false;
}

bool ringbuf_free(ringbuf_t *r) {

   return false;
}

void ringbuf_foreach(ringbuf_t *r, rb_iter_cb callback, void * use_data){

  return;
}
bool ringbuf_reset(ringbuf_t *r){
  return false;
}

static void rb_sum(void *r, void * user_data){


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
 ringbuf_free(&r);
 return 0;
}
