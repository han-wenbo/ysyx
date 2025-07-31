#include <am.h>
#include <riscv/riscv.h>
#define RTC_ADDRR (0xa0000048) 

void __am_timer_init() {
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uptime->us = 0;
}

// Functions used for calculate current time.

static inline int is_leap(int year){
   if(((year % 4 == 0) && (year % 100 !=0)) || (year % 400 ==  0))
	return 1;
   return 0;
}
static inline int days_in_year(int year){ 
   if(is_leap(year)) return 366;
   return 365;
}
static inline void secs_to_rtc(unsigned long long int all_secs, AM_TIMER_RTC_T *rtc) {

  // a day has 60 * 60 * 12 seconds
  int days = all_secs / 60 * 60 * 24;
  int secs = all_secs % 60 * 60 * 24; 
 
  int years = 1970;
  while(days >= days_in_year(years)) {
     days = days - days_in_year(years);
     years++;
  }
   
  int month[12] = {31, 28, 31, 30, 31, 30 ,31, 30 ,31, 30 ,31, 30}; 

  if(is_leap(years)) month[1] = 29; 

  int months = 0;
  while(days >= month[months]) {
    days = days - month[months];
    months++;
  }
  months++;
  

  rtc->second = ((secs % (60 * 60 * 24)) % (60 * 60)) % 60;
  rtc->minute = ((secs % (60 * 60 * 24)) % (60 * 60)) / 60;
  rtc->hour   = (secs % (60 * 60 * 24)) / (60 * 60);
  rtc->day    = days + 1;
  rtc->month  = months;
  rtc->year   = years;

}
void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  unsigned long long int cur_time = inl(RTC_ADDRR + 4);
  cur_time = (cur_time << 32) | inl(RTC_ADDRR);
  

  secs_to_rtc(cur_time, rtc);
}
