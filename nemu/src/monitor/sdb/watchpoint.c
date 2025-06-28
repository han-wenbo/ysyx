/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include "sdb.h"
#include "debug-mode.h"
#define NR_WP 32

/* For the usage of test */
#ifdef WP_DEBUG
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <sys/wait.h>
#include "../../isa/riscv32/local-include/reg.h"
#include "isa.h"
#include "memory/paddr.h"
static int used_wp_num = 0;
static int unused_wp_num = NR_WP;
#endif

/* These assertions are always true. */
#define WP_ASSERT			\
   do {					\
       assert(used_wp_num >= 0 && used_wp_num <= NR_WP);	\
       assert(unused_wp_num >= 0 && unused_wp_num <= NR_WP); 	\
       assert(unused_wp_num + used_wp_num == NR_WP);		\
    } while(0)


typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  char expr[200];
  word_t last_value;
  bool used;

} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;


void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */


void show_point() {

  WP * node = head;
  if(!head)
  {
    printf("No watchpoints");
    return;
  }
  
   printf("Num\tWhat\t\tValue\n");
   while (node != NULL) {
      assert(node->used);
      printf("%d\t%s\t\t0x%x\n", node->NO, node->expr, node->last_value);
      node = node->next;
    }
  

}

/* Return ture if a watch point has changed. */
void lookthrough_wp() {
  
  /* There is no watchpoint. */
  if(!head) return;  

  //for (WP * node = head;  node->next !=NULL; node = node->next) {
  for (WP * node = head;  node !=NULL; node = node->next) {
    assert(node->used == true);
    bool success;
    word_t new_v = expr(node->expr ,&success);
    assert(success);

    if(new_v != node->last_value) {
      if(nemu_state.state == NEMU_END) {
         nemu_state.state =  NEMU_STOP;
         return;
      }
      nemu_state.state =  NEMU_STOP;
      printf("Watchpoint %s triggered. Old value = %d, New value = %d\n", node->expr, node->last_value, new_v);
      node->last_value = new_v;
    }
  }
  
}



bool new_wp(char * e) {
   bool success;
   word_t v = expr(e, &success);
   WP * tmp;

   if(!success) return false;
 

   // There in no free watchpoint node.
   if(free_ == NULL) return false;
   
   tmp = head;
 
   assert(free_->used == false);   

   head = free_;

   free_->used = true;
   strcpy(free_->expr, e);
   free_->last_value = v;
   free_ = free_->next; 

   head->next = tmp;

#ifdef WP_DEBUG
   used_wp_num++;
   unused_wp_num--;
   WP_ASSERT;
#endif
   return true;
}

bool free_wp(int n) {

  if (n >= NR_WP) {
    printf("n>=NR_WP\n");
    return false;
  }

  if(!wp_pool[n].used) {
    printf("Watchpoint %d is not used! \n", n);
    return false; 
  }


  // Find the previous node.
  WP * w = head;
  if (head == &wp_pool[n])  {
    head = head->next;
  } else {
    for( ;  w->next != &wp_pool[n]; w = w->next) {
       if(!w->next) {
          printf("Can't find previous node.\n");
          return false;
       }
    } 
    w->next = w->next->next;
  }
  
  WP *node = free_; 
  free_ = &(wp_pool[n]);
  free_->next = node;
  free_->used = false;
#ifdef WP_DEBUG
   used_wp_num--;
   unused_wp_num++;
   WP_ASSERT;
#endif
  return true;

}

#ifdef WP_DEBUG

/* Return the number of nodes linked from h */
static int get_number(WP * h){
  int i = 0;
  WP * tmp_h = h;
  while (tmp_h != NULL) { 
    i++;
    tmp_h = tmp_h->next;
  }
  return i;
}

/*static uint32_t choose(uint32_t n){
  uint32_t r = (uint32_t)rand() % n;
  assert(r < n);
  return r;

}


 Randomly generate a number in [a,b]. 
uint32_t choose2(uint32_t a, uint32_t b) {
   assert(b >= a);
   uint32_t r = a + rand() % (b - a + 1);
   assert(r >= a && r <= b);
   return r;
} */

void watchpoint_test() {
  int i;
    int seed = time(0);
  srand(seed);
  // When there is no watchpoint, try to delete
  for(i = 0; i < 1000; i++) {
     int n = choose(100);
     printf("Delete watchpoint %d...\n", n);
     free_wp(n);
     WP_ASSERT;
  }
  assert(head == NULL);
  assert(used_wp_num == 0);
  assert(unused_wp_num == NR_WP);
  // Add more than NR_WP watchpoints.
  printf("--------------ADD watchpoints---------------\n");
  char e[10] = "$0";
  for (i = 0; i < 100; i++) {
    new_wp(e);
    assert(used_wp_num == get_number(head));
    WP_ASSERT;
  }
  assert(free_ == NULL);
  assert(head != NULL); 
  assert(used_wp_num == NR_WP);
  assert(unused_wp_num == 0);
  assert(get_number(free_) == 0);
  show_point();
  // Don't change any value, and then run lookthough_wp() 
  printf("------------No change, run lookthough_wp()---------------\n");
  lookthrough_wp();
  printf("------------No change, run lookthough_wp() end---------------\n");
 
  // Randomly delete watchpoints.
  printf("------------Randomly delete.---------------\n");
  for(i = 0; i < 30; i++) {
     int n = choose(100);
     printf("Delete watchpoint %d...\n", n);
     free_wp(n);         
     WP_ASSERT;
  }                      
  show_point();
  // delete all watchpoints.
  printf("------------Delete all---------------\n");
  for(i = 0; i < NR_WP; i++) {
     free_wp(i);
     WP_ASSERT; 
  }             
  assert(head == NULL);
  assert(used_wp_num == 0);
  assert(unused_wp_num == NR_WP);
  assert(get_number(free_) == NR_WP);
  assert(get_number(head) == 0);
  assert(free_ != NULL);
  show_point();


  // Test reg watchpoints
  for(i = 0; i < NR_WP; i++) {
    char regname[5];
    sprintf(regname, "$%s",reg_name(i));
    if(new_wp(regname) == false) 
       Log("add new wp %s fail!\n",regname);
  }
  for(i = 1; i< NR_WP; i++) {
    cpu.gpr[i] += 1;
  }

  printf("------------All watchpoints has been changed, and run lookthough_wp()---------------\n");
  lookthrough_wp();
  printf("------------All watchpoints has been changed, and run lookthough_wp() END---------------\n");
  show_point();
  
  // delete all watchpoints.
  for(i = 0; i < NR_WP; i++) {
     free_wp(i);
     WP_ASSERT;
  }
  assert(head == NULL);
  assert(used_wp_num == 0);
  assert(unused_wp_num == NR_WP);
  assert(get_number(free_) == NR_WP);
  assert(get_number(head) == 0);
  show_point();


  //Generate NR_WP valid memory addresses in each iteration.
  for (i = 0; i < 10; i++) {
    printf("====================================%d Gnerating memory express ============================\n",i);
    for(int j = 0; j < NR_WP; j++) {
      char buf_addr[15];
      paddr_t addr = choose2(PMEM_LEFT, PMEM_RIGHT - 3);
      sprintf(buf_addr, "*%u", addr);
      word_t data = choose(UINT32_MAX);
      paddr_write(addr, sizeof(word_t), data);
      if(!new_wp(buf_addr))  
         Log("new_wp fail! expr: %s", buf_addr);
    
      // Change the value stored in this address.
      paddr_write(addr, sizeof(word_t), data + 1);
    }

    WP_ASSERT;
    assert(free_ == NULL);
    assert(get_number(head) == NR_WP);
    assert(used_wp_num == NR_WP);
    show_point();
    printf("------------All watchpoints has been changed, and run lookthough_wp()---------------\n");
    lookthrough_wp();
    printf("------------All watchpoints has been changed, and run lookthough_wp() END---------------\n");

       
  // delete all watchpoints.
  for(int p = 0; p < NR_WP; p++) {
     free_wp(p);
     WP_ASSERT;
  }
  assert(head == NULL);
  assert(used_wp_num == 0);
  assert(unused_wp_num == NR_WP);
  assert(get_number(free_) == NR_WP);
  assert(get_number(head) == 0);
  show_point();

  }
}
#endif 
