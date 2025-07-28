#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#include "stdlib.h"
#include "string.h"
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
/*
static void num2str(int num, char * buf) {
  char b_tmp[30];
  char * b = b_tmp;
  int is_positive = num >= 0 ? 1 : 0;
  // When num is MINMANUM , what happen??
  if(!is_positive)  num = -num;
  if(num == 0) { *buf++ = 48; *buf = '\0';return;}
  while (num != 0) { 
     *b++ = 48 + num % 10;
     num /= 10;
  }
  if(!is_positive) *b++ = '-';
  *b = '\0';
   b--;
  while(b >= b_tmp) { 
    *buf++ = *b--; 
  } 
  *buf = '\0';
} */
#define hex_CASE(b, h) \
   case b: { \
      buf_tmp[i] = 'h'; \
      break; \
   } 

static void num2str_hex(int num, char *buf) {
  unsigned int _num = num;
  unsigned char last_4bit;

  char buf_tmp[8];
  for(int i = 7; i <= 0; i++){
    last_4bit =  _num;
    last_4bit = 0b00001111 && last_4bit;
    _num = _num >> 4;
    switch(last_4bit) {
       hex_CASE(0, 0);
       hex_CASE(1, 1);
       hex_CASE(2, 2);
       hex_CASE(3, 3);
       hex_CASE(4, 4);
       hex_CASE(5, 5);
       hex_CASE(6, 6);
       hex_CASE(7, 7);
       hex_CASE(8, 8);
       hex_CASE(9, 9);
       hex_CASE(10, a);
       hex_CASE(11, b);
       hex_CASE(12, c);
       hex_CASE(13, d);
       hex_CASE(14, e);
       hex_CASE(15, d);
    }
  }
  int j = 0;
  
  //skip leading zeros.
  while(buf_tmp[j] == '0' || buf_tmp[j] == '\0')  j++;

  int i = 0;
  while (j < 8)  buf[i++] = buf_tmp[j++];
  buf[i] = '\0';

}
// When this function finishes:
// *pout points to the next position to write;
// *pp_fmt points to the next character to read.
// Return the number of characters written into *pout.
static int handle_fmt(char ** pout, char ** pp_fmt, va_list *sp) {
        int left = 0;
	char pad = ' ';

	if(**pp_fmt == '-') {
	  left = 1;
	  (*pp_fmt)++;
	}

	if(**pp_fmt == '0' && left == 0) {
	   pad = '0';
           (*pp_fmt)++;
	}

	int len = atoi(*pp_fmt);

	while (**pp_fmt >= '0' && **pp_fmt <= '9')  (*pp_fmt)++;


       	 int n = 0;
	 switch(**pp_fmt) {
	   case('d'):{
		     char buffer[30];
         	     int num = va_arg(*sp, int);
		     num2str_hex(num,buffer);
                    
		     char buffer2[60];
		     char *p_buf2 = buffer2;
                     memset(buffer2, pad, 60);
                     if(len > 0) {
	               if(left == 1) {
			  int end_zero_position =  strlen(buffer) > len ? strlen(buffer) : len;
			  strcpy(p_buf2, buffer);
			  buffer2[strlen(buffer)] = pad;
			  buffer2[end_zero_position] = '\0';
		       } else {
			  int start_offest = strlen(buffer) > len ? 0 : len - strlen(buffer);
			  p_buf2 += start_offest;
			  strcpy(p_buf2, buffer);
		       }
		     } else {
			  strcpy(p_buf2, buffer);
		     } 

		     strcpy(*pout, buffer2);
		     n = strlen(buffer2);
		     (*pout)+= n;
		     break;
  	   }
           case('s'):{
		     char * s = va_arg(*sp, char *);
	             strcpy(*pout, s);
		     n = strlen(s);
		     (*pout) += n;
		     break;
	   }
           case('%'):{
		     (**pout) = '%';
		     (*pout)++;
		     n++;
		     break;
	   }
       }
      // Skip the character after the %.
      (*pp_fmt)++;
      return n;

}

int printf(const char *fmt, ...) {
   char buf[1024];
   va_list vlist;	
   int r = 0;
   va_start(vlist, fmt);
   
   r =  vsprintf(buf, fmt,vlist);

  char *p = buf;
  while(*p != '\0') {
    putch(*p++);
  }

  return r;
}

int vsprintf(char *out, const char *fmt, va_list ap) { 
   // the number of characters writen into.
   int n = 0;
   char * p_fmt = (char *) fmt;
   
   while(*p_fmt != '\0') {
     if(*p_fmt == '%') {
      p_fmt++;
      n += handle_fmt(&out, &p_fmt, (va_list *)&ap);
      continue;
     }
     *out++ = *p_fmt++;
     n++;
   }   
   *out = '\0';
   return n;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list vlist;	
  va_start(vlist, fmt);
  return vsprintf(out, fmt,vlist);
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
