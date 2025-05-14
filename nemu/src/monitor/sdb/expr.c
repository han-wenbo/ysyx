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

#include <isa.h>
#include <memory/paddr.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ,TK_NUM,
  TK_REG, TK_NOTEQ, TK_AND, TK_PONTER

  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal
  {"-" , '-'},
  {"\\*", '*'},
  {"/", '/'},
  {"!=", TK_NOTEQ},
  {"&&", TK_AND},
  {"(0x[a-fA-F0-9]+)|([0-9]+)", TK_NUM},
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;


static void print_expr(bool should_newline) {

  int i = 0;
  assert(nr_token > 0);
  
  for(;i <= nr_token; i++) 
    printf("%s",tokens[i].str);

  if(should_newline)
    printf("\n");

}
// Record 's' in tokens[*index], and then index++
static bool record_token(int *index,const char *s, int str_len, int type){
  int i = *index;

  /* 30 means that  str[31] = '\0'  */
  if(i > 31 || str_len > 30)
    { return false; }

  strncpy(tokens[i].str, s, (size_t)str_len);
  tokens[i].type = (int)type;

  (*index)++;

  return true;
  
}
#define RECORD_TOKEN(t) \
    if(!record_token(&nr_token, substr_start, substr_len, t)) \
       return false;	\
    break 	\

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
	  /* skip the leading spaces */
	  case TK_NOTYPE: 
	  	break;
	  case 	'+'	:
		RECORD_TOKEN('t');
	  case  TK_EQ	:
		RECORD_TOKEN(TK_EQ);
	  case  '-'	:
		RECORD_TOKEN('-');
	  case  '*'	:
		/* '*' is a multiplication operater */
		if(nr_token != 0 && ((tokens[nr_token - 1].type == TK_NUM) || tokens[nr_token - 1].type == ')'))
		  {RECORD_TOKEN('*');}
		/* A pointer */
		else
		  {RECORD_TOKEN(TK_PONTER);}
	  case  '/'	:
		RECORD_TOKEN('/');
	  case  TK_NOTEQ:
		RECORD_TOKEN(TK_NOTEQ);
	  case  TK_AND	:
		RECORD_TOKEN(TK_AND);
	  case  TK_NUM :
		RECORD_TOKEN(TK_NUM);
          default: assert(0);
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}


/* The code for evaluate the express */



static bool check_parentheses(int p,int q) {
  int stack[16];
  int deepth = 0;  
  for(int i = p; i < q; i++){
    if(tokens[i].type == '(') {
	stack[deepth++] = p;
    }
    else if(tokens[i].type == ')') {
	if(deepth <= 0) printf("error/n");
	stack[--deepth] = -1;
    }		
  }

  if(deepth == 1 && stack[0] == p && tokens[q].type == ')')
    return true;
  
  return false;

}
  
static int priority_table(int type){
  switch(type){
    case TK_AND:			return 11;
    case TK_EQ:		case TK_NOTEQ:	return 7;
    case '+':		case '-':	return 4;
    case '*':		case '/':	return 3;
    case TK_PONTER:			return 2;
    /* the thrid branch of get_position() never execute return 0. */
    default:return 0;
  }

}
static int get_position(int p, int q) {
  int i;
  int deepth = 0;
  int min_pri_position = -1;
 
  for(i = q; i >= p; i--) {  
    int is_operater = priority_table(tokens[i].type);

    if(tokens[i].type == ')') 
      deepth++;    
    else if(tokens[i].type == '(') {
      assert(deepth <= 0);
      deepth--;
    }

    if(deepth == 0 && is_operater) {
      /* the first operater that this loop meets */
      if(min_pri_position == -1)
        min_pri_position = i;

      int this_pri = is_operater;
      int min_pri  = priority_table(tokens[min_pri_position].type);
      if(this_pri > min_pri)
	min_pri_position = i;
    }
  }
  assert(min_pri_position >= p && min_pri_position <= q);
  return min_pri_position;
  
}

static int eval(int p, int q) {

  assert(p >= 0 && q <= 31 && p <= q);
  
  if(p == q) {
    return strtol(tokens[p].str, NULL, 0);
  } 
  else if(check_parentheses(p, q) == true) {
    return eval(p + 1, q - 1);
  } 
  else {
    int position = get_position(p,q);
    

#define EVAL_BIN_OP(op)    \
    return (eval(p, position - 1)) op (eval(position + 1, q))\

     switch (tokens[position].type) {
     
       /* for binary operaters */
       case  '+'     :
		EVAL_BIN_OP(+);
       case  TK_EQ   :
		EVAL_BIN_OP(==);
       case  '-'     :
		EVAL_BIN_OP(-);
       case  '*'     :
		EVAL_BIN_OP(*);
       case  '/'     :
		EVAL_BIN_OP(/);
       case  TK_NOTEQ:
		EVAL_BIN_OP(!=);
       case  TK_AND  :
		EVAL_BIN_OP(&&);
	/* others */
       case  TK_PONTER:{ 
		long addr = strtol(tokens[position].str, NULL, 0);
		return *(guest_to_host((paddr_t)addr));
	}
       default: assert(0);
     }
  }
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  int value = eval(0, nr_token);
  print_expr(0);
  printf("=%d\n", value);
  *success = true;
  return value;
}
