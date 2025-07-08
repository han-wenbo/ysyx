#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

static void num2str(int num, char * buf) {
  char b_tmp[30];
  char * b = b_tmp;
  int is_positive = num >= 0 ? 1 : 0;
  // When num is MINMANUM , what happen??
  if(!is_positive)  num = -num;
  if(num == 0) { *buf = 0; return;}
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
}
// When this function finishes:
// *pout points to the next position to write;
// *pp_fmt points to the next character to read.
// Return the number of characters written into *pout.
static int handle_fmt(char ** pout, char ** pp_fmt, va_list sp) {
	int n = 0;
	 switch(**pp_fmt) {
	   case('d'):{
		     char buffer[30];
	             int num = va_arg(sp, int);
		     num2str(num,buffer);
		     strcpy(*pout, buffer);
		     n = strlen(buffer);
		     (*pout)+= n;
		     break;
  	   }
           case('s'):{
		     char * s = va_arg(sp, char *);
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
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) { 
   // the number of characters writen into.
   int n = 0;
   char * p_fmt = (char *) fmt;
   
   while(*p_fmt != '\0') {
     if(*p_fmt == '%') {
      p_fmt++;
      n += handle_fmt(&out, &p_fmt, ap);
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
