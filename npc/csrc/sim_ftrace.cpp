#include <stdio.h>
#include "npcConfig.h"
static int trigger = 0;
extern int jal_jalr_occur;
extern "C" void dpi_trigger_ftrace() {
   // printf("Between eval(): trigger = %d", trigger);
   #ifdef USING_FTRACE
   trigger = 1; 
   #endif
   return;
}

void set_jal_jalr_occur(){
  
  if(trigger == 1) {
    trigger = 0;
    jal_jalr_occur = 1;
  }
}
