#ifndef __DEBUG_MODE__
#define __DEBUG_MODE__

#define WP_DEBUG
#define EXPR_DEBUG

#define DEBUG_OPEN

#ifdef DEBUG_OPEN
#include <stdint.h>
uint32_t choose(uint32_t n);
uint32_t choose2(uint32_t a, uint32_t b);
#endif

#endif 
