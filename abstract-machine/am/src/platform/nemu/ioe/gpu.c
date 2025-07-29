#include <am.h>
#include <nemu.h>

//  #define VGACTL_ADDR     (DEVICE_BASE + 0x0000100)
#define SYNC_ADDR (VGACTL_ADDR + 4)
//#define FB_ADDR 0xa1000000

extern void __am_gpu_config(AM_GPU_CONFIG_T *cfg);
void __am_gpu_init() {
  int i;
 
  AM_GPU_CONFIG_T cfg;
 __am_gpu_config(&cfg); 

  int w = cfg.width;  // TODO: get the correct width
  int h = cfg.height;  // TODO: get the correct height
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  for (i = 0; i < w * h; i ++) fb[i] = i;
  outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  unsigned int regv = inl(VGACTL_ADDR);
  
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = regv >> 16, .height = (regv & 0x0000FFFF) ,
    .vmemsz = (regv >> 16) * (regv & 0x0000FFFF) * 4
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {

  AM_GPU_CONFIG_T cfg;
 __am_gpu_config(&cfg); 

//  int w = cfg.width;  // TODO: get the correct width
  int h = cfg.height;  // TODO: get the correct height

 ctl->sync = inl(VGACTL_ADDR);
  int (*fb_addr)[h] = (int (*)[h])FB_ADDR;
  int (*pix)[ctl->h] = ctl->pixels;

  if (ctl->sync) {
     for(int i = 0; i < ctl->w; i++) {
        for(int j = 0; j < ctl->h; j++){
	   outl((int)(&fb_addr[ctl->x+i][ctl->y+j]), pix[i][j]);
	}
     }	     
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
