#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <sys/wait.h>


/* Randomly generate a number which is smaller than n */
uint32_t choose(uint32_t n){
  int seed = time(0);
  srand(seed);
  uint32_t r = (uint32_t)rand() % n;
  assert(r < n);
  return r;

}
/* Randomly generate a number in [a,b]. */
uint32_t choose2(uint32_t a, uint32_t b) {
   int seed = time(0);
   srand(seed);
   assert(b >= a);
   uint32_t r = a + rand() % (b - a + 1);
   assert(r >= a && r <= b);
   return r;
}

