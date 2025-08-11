#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>
#include <time.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t n = 0;
  while ( *s++ != '\0') {
    n++; 
  }
  return n;
}

char *strcpy(char *dst, const char *src) {
  memcpy((void *)dst, (void *)src, strlen(src));
  *(dst + strlen(src)) = '\0';
  return dst;
}

// strlen(s) < maxl , return strnlen 
// strlen(s) >= maxl, retrun maxl
/*
size_t strnlen(const char *s, size_t maxl) {
  if(strlen(s) < maxl)  return strlen(s);  
  return maxl;
}
*/
extern size_t strnlen(const char *s, size_t maxl);
char *strncpy(char *dst, const char *src, size_t n) {
  size_t size = strnlen(src, n); 
  uint8_t * dst2 = memcpy(dst, src, size) + size;
  return memset((void *) dst2, 0, n - size);
  
}

char *strcat(char *dst, const char *src) {
    strcpy(dst + strlen(dst),src);
    return dst;
}

int strcmp(const char *s1, const char *s2) {
   unsigned char * s1_tmp = (unsigned char *) s1;
   unsigned char * s2_tmp = (unsigned char *) s2;

   while(*s1_tmp == *s2_tmp) {
     if(*s1_tmp == '\0') return 0;   
     s1_tmp++;
     s2_tmp++;
   }   

   if(*s1_tmp > *s2_tmp) return 1;
   return -1;
}

int strncmp(const char *s1, const char *s2, size_t n) {
     unsigned char * s1_tmp = (unsigned char *) s1;
     unsigned char * s2_tmp = (unsigned char *) s2;
 
    size_t i = 0; 
     while(*s1_tmp == *s2_tmp && i < n) {
       if(*s1_tmp == '\0') return 0;
       s1_tmp++;
       s2_tmp++;
       i++;
     }
  
     if(*s1_tmp > *s2_tmp) return 1;
     return -1; 
}

void *memset(void *s, int c, size_t n) {
  uint8_t * p = (uint8_t *) s ;
  for(size_t i = 0; i < n ; i++) {
     *p++ = (uint8_t) c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
    uint8_t buf[n];
    memcpy((void*)buf, src, n);
    return memcpy(dst, (void *)buf, n);
}

void *memcpy(void *out, const void *in, size_t n) {
    /*for( size_t i = 0; i < n; i ++) {
       uintptr_t in_tmp = (uintptr_t)in  + i;
       for (size_t j = 0; j < n; j++ ) {
         uintptr_t out_tmp = (uintptr_t)out + j;
	 // if these two areas overlap, return NULL.
         if(in_tmp == out_tmp) return NULL;
       }
    }*/   

    uint8_t * in2 = ((uint8_t *) in);
    uint8_t * out2 = ((uint8_t *) out);
    for (; n > 0; n-- ) {
       *(uint8_t *) out2++ = *(uint8_t *) in2++;
    }
    return (void *) out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  unsigned char * s1_tmp = (unsigned char *) s1;
  unsigned char * s2_tmp = (unsigned char *) s2;
  for (size_t i = 0; i < n; i++) {
    if( *s1_tmp != *s2_tmp){ 
       if(*s1_tmp > *s2_tmp) return 1;
       return -1;       
    } 
    s1_tmp++;
    s2_tmp++;
  }
  return 0;
}

#endif
