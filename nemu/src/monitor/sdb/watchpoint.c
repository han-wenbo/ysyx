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

#define NR_WP 32

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

  for (WP * node = head;  node->next !=NULL; node = node->next) {
    assert(node->used == true);
    bool success;
    word_t new_v = expr(node->expr ,&success);
    assert(success);

    if(new_v != node->last_value) {
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

   return true;
}

bool free_wp(int n) {

  if (n >= NR_WP) {
    printf("n>=NR_WP\n");
    return false;
  }

  if(!wp_pool[n].used) {
    printf("wp_pool.used = 0");
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
  WP *node = free_->next; 
  free_ = &(wp_pool[n]);
  free_->next = node;
  free_->used = false;

  return true;

}


