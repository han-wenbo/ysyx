#include <assert.h>
#include <elf.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <utils.h>
#include <debug.h>

#ifdef __FTRACE_DEBUG_
#define MAX_FUNC 50
typedef struct {
  Elf32_Addr start;
  Elf32_Addr end;
  char name [32];
} symtab_for_func_map;

typedef struct {
  symtab_for_func_map s_map[MAX_FUNC];
  size_t funcs_num; 
}symtab_for_func;
#endif


FILE * ftrace_file_fp = NULL;

#ifndef __FTRACE_DEBUG_
void init_ftrace_file(char * file_name) {
  if (file_name != NULL) {
    FILE *fp = fopen(file_name, "w");
    Assert(fp, "Can not open '%s'", file_name);
    ftrace_file_fp = fp;
  }
  Log("Function trace is written to %s", ftrace_file_fp ? file_name : "stdout");
}
#endif


static unsigned long fread_at(void * buf, unsigned long size,unsigned long n, FILE *fp, unsigned long position) {
  if(fseek(fp, position, SEEK_SET) != 0) {
    return false;
  }
  if(fread(buf, size, n, fp) != n){
    return false;
  }
  return n;
}
// caller should ensute shdr is leagal.
static size_t find_section(char * name, uint32_t type, const Elf32_Shdr *shdr,size_t s_num, char * name_str) {
  if(name == NULL || shdr == NULL) return 0;

  for( size_t i = 0; i < s_num; i++) {

    if((shdr + i)->sh_type == type && strcmp(name_str + (shdr + i)->sh_name, name) == 0) {
      return i;
    }
  }

  return -1;
}

static void * read_section(const Elf32_Shdr * shdr, size_t idx, FILE * fp){
      assert(shdr != NULL && fp != NULL); 

      void * r =  malloc((shdr + idx)->sh_size);
      if(fread_at(r, 1, (shdr + idx)->sh_size ,fp, (shdr+idx)->sh_offset) !=  (shdr + idx)->sh_size) {  free(r);   return NULL; }
      return r;
}

static bool do_map(const Elf32_Shdr *shdr, size_t symtab_idx, size_t symname_idx, symtab_for_func * st, FILE *fp){
  
  if( shdr == NULL || st == NULL) return false;
  assert(symname_idx != symtab_idx);

  void * symtab = read_section(shdr, symtab_idx, fp);
  if(symtab == NULL) return false;
  void * symstr = read_section(shdr, symname_idx, fp);
  if(symstr == NULL) {free(symtab); return false;}

  // Count the number of symbol table entries.
  assert((shdr + symtab_idx)->sh_entsize != 0);
  size_t sym_num = (shdr + symtab_idx)->sh_size / (shdr + symtab_idx)->sh_entsize; 
  
  size_t fun_n = 0;
  for(size_t i = 0; i < sym_num; i++) {
    assert(fun_n < MAX_FUNC);
    // When find a symboy of function,
    if (ELF32_ST_TYPE((((Elf32_Sym *)symtab) + i)->st_info) == STT_FUNC){
       st->s_map[fun_n].start = (((Elf32_Sym *) symtab) + i)->st_value;
       st->s_map[fun_n].end = (((Elf32_Sym *) symtab) + i)->st_value + (((Elf32_Sym *) symtab) + i)->st_size -1;

       // Prevent out-of-bounds access to symbol name string.
       //size_t name_str_size = (shdr + symtab_idx)->sh_size;
       //Elf32_Addr max_addr = (shdr + symtab_idx)->sh_addr + name_str_size;
       //assert();
       strcpy( st->s_map[fun_n].name,(char *) symstr + (((Elf32_Sym *) symtab) +i )->st_name);
       fun_n++;
    }
    st->funcs_num = fun_n;
  }

  for( size_t i = 0; i < fun_n; i++) {
       printf("[%zu] name: %s   start:0x%x  end: 0x%x \n", i, st->s_map[i].name,st->s_map[i].start, st->s_map[i].end);
  }
  
  free(symtab);
  free(symstr);
  return true;

}



bool init_symtab_for_func_map(char * elf_name, symtab_for_func * st) {
  if (elf_name == NULL || st == NULL || st->funcs_num != 0) return false;
  FILE * fp = fopen(elf_name,"rb");   
  if(fp == NULL) return false;
/*
    fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  rewind(fp);
  long pos = ftell(fp);
  printf("File size: %ld, current position before fread: %ld\n", size, pos);  
  char resolved_path[100];
realpath(elf_name, resolved_path);
printf("Trying to open: %s (realpath: %s)\n", elf_name, resolved_path);
*/
  // Read the header of elf file into elf_header
  Elf32_Ehdr elf_header;
  int r;
  if((r = fread(&elf_header, 1, sizeof(Elf32_Ehdr), fp)) != sizeof(Elf32_Ehdr)) {
    if (feof(fp)) {
    printf("fread failed: reached EOF\n");
}
    fclose(fp);
    return false;
  }

  //e_shstrndx
  // a valid elf file ?
  if (elf_header.e_ident[EI_MAG0] != ELFMAG0 ||
      elf_header.e_ident[EI_MAG1] != ELFMAG1 ||
      elf_header.e_ident[EI_MAG2] != ELFMAG2 ||
      elf_header.e_ident[EI_MAG3] != ELFMAG3) {
    fclose(fp);
    return false;
  }

  // section header does not exist
  if(elf_header.e_shoff == 0) {
    fclose(fp);
    return false;
  }

  // Read section header table.
  Elf32_Shdr shdr[elf_header.e_shnum];
  if(fread_at(shdr, sizeof(Elf32_Shdr), elf_header.e_shnum, fp, elf_header.e_shoff) != elf_header.e_shnum) {
    fclose(fp);
    return false;
  }
  
  //  section name string does not exist.
  if(elf_header.e_shstrndx == SHN_UNDEF) {
    fclose(fp);
    return false;
  }

  // Read section name string.
  char * sh_str = malloc( shdr[elf_header.e_shstrndx].sh_size);
  if(fread_at(sh_str, 1, shdr[elf_header.e_shstrndx].sh_size, fp, shdr[elf_header.e_shstrndx].sh_offset) !=shdr[elf_header.e_shstrndx].sh_size) {
    fclose(fp);
    return false;
  }
 
  size_t sym_idx  = find_section(".symtab",  SHT_SYMTAB, shdr, elf_header.e_shnum, sh_str);
  if(sym_idx == -1) {
    fclose(fp);
    return false;
  }
  size_t secname_idx = find_section(".strtab",  SHT_STRTAB, shdr ,elf_header.e_shnum, sh_str);
  if(secname_idx == -1) {
    fclose(fp);
    return false;
  }

  if(!do_map(shdr, sym_idx,secname_idx, st,fp)){
    fclose(fp);
    return false;
  }
  free(sh_str);
  return true;
}


Elf32_Addr func_name2star_addr(char * func_name,symtab_for_func * st) {

  return 0;
}

const char * star_add2fcun_name(Elf32_Addr addr, symtab_for_func * st) {
  assert(st != NULL);
  assert(st->funcs_num < MAX_FUNC);

  for(size_t i = 0; i <st->funcs_num; i++){
     if(addr >= st->s_map[i].start &&  addr <= st->s_map[i].end) 
        return st->s_map[i].name;
  } 
  return "???";
}

bool is_func_start(Elf32_Addr addr, symtab_for_func *st){
  assert(st != NULL);
  assert(st->funcs_num < MAX_FUNC);

  for(size_t i = 0; i <st->funcs_num; i++){
     if(addr == st->s_map[i].start) 
        return true;
  } 
  return false;
}
bool is_func_end(Elf32_Addr addr, symtab_for_func *st){
  assert(st != NULL);
  assert(st->funcs_num < MAX_FUNC);
  for(size_t i = 0; i <st->funcs_num; i++){
     if(addr == st->s_map[i].end) {
        return true;
        }
  } 
  return false;
}

size_t addr2idx(Elf32_Addr addr, symtab_for_func *st){
  assert(st != NULL);
  assert(st->funcs_num < MAX_FUNC);

  for(size_t i = 0; i <st->funcs_num; i++){
     if(addr >= st->s_map[i].start &&  addr <= st->s_map[i].end) 
        return i;
  } 
  return -1;
}
bool reset_symtab_for_func(symtab_for_func * s){
  if (s == NULL) return false;
  s->funcs_num = 0;
  return true;
}

#ifdef __FTRACE_DEBUG_
#define FUN1_S 0x1000
#define FUN1_E 0x1016
#define FUN2_S 0x1017
#define FUN2_E 0x102c
#define FUN3_S 0x102d
#define FUN3_E 0x1041
#define FUN4_S 0x1042
#define FUN4_E 0x1057
#define MAIN_S 0x106d 
#define MAIN_E 0x10ce


  symtab_for_func st;
static void __test_star_add2fcun_name(Elf32_Addr start,Elf32_Addr end,char * fun_name) {
   for( uintptr_t i = start; i <= end; i++){
     assert(strcmp(star_add2fcun_name(i,&st),fun_name) == 0);
   }
}

int main() {
  // A unexisted file
  assert(init_symtab_for_func_map("123", &st) == false);
  assert(init_symtab_for_func_map("/home/ubuntu/ysyx-workbench/nemu/utest/legal.elf",  &st) == true);
  assert(reset_symtab_for_func(&st) == true);
  // A illegal-elf file.
  assert(init_symtab_for_func_map("/home/ubuntu/ysyx-workbench/nemu/utest/illgal.elf",  &st) == false);
  // symtab_for_func has been initlized, but has not been reset,  initlizing repeatly.
  assert(init_symtab_for_func_map("/home/ubuntu/ysyx-workbench/nemu/utest/legal.elf",  &st) == true);
  //assert(init_symtab_for_func_map("/home/ubuntu/ysyx-workbench/nemu/utest/legal.elf",  &st) == false);
  assert(reset_symtab_for_func(&st) == true);
  assert(init_symtab_for_func_map("/home/ubuntu/ysyx-workbench/nemu/utest/legal.elf",  &st) == true);
  assert(reset_symtab_for_func(&st) == true);
  // ELF does not have symbol table or strtable
  assert(init_symtab_for_func_map("/home/ubuntu/ysyx-workbench/nemu/utest/nosymbol.elf",  &st) == false);
  assert(reset_symtab_for_func(&st) == true);
   
  // ilegal address
  assert(init_symtab_for_func_map("/home/ubuntu/ysyx-workbench/nemu/utest/legal.elf",  &st) == true);
  __test_star_add2fcun_name(FUN1_S,FUN1_E,"fun_1");
  __test_star_add2fcun_name(FUN2_S,FUN2_E,"fun_2");
  __test_star_add2fcun_name(FUN3_S,FUN3_E,"fun_3");
  __test_star_add2fcun_name(FUN4_S,FUN4_E,"fun_4");
  __test_star_add2fcun_name(MAIN_S,MAIN_E,"main");
  __test_star_add2fcun_name(0,FUN1_S-1,"???");
  __test_star_add2fcun_name(MAIN_E+1,1000000,"???");
}
#endif
/* 
 0000000000001000    1000:       f3 0f 1e fa             endbr64
    1004:       55                      push   %rbp
    1005:       48 89 e5                mov    %rsp,%rbp
    1008:       89 7d fc                mov    %edi,-0x4(%rbp)
    100b:       89 75 f8                mov    %esi,-0x8(%rbp)
    100e:       8b 55 fc                mov    -0x4(%rbp),%edx
    1011:       8b 45 f8                mov    -0x8(%rbp),%eax
    1014:       01 d0                   add    %edx,%eax
    1016:       5d                      pop    %rbp
    1017:       c3                      ret

0000000000001018 <fun_2>:
    1018:       f3 0f 1e fa             endbr64
    101c:       55                      push   %rbp
    101d:       48 89 e5                mov    %rsp,%rbp
    1020:       89 7d fc                mov    %edi,-0x4(%rbp)
    1023:       89 75 f8                mov    %esi,-0x8(%rbp)
    1026:       8b 45 fc                mov    -0x4(%rbp),%eax
    1029:       0f af 45 f8             imul   -0x8(%rbp),%eax
    102d:       5d                      pop    %rbp
    102e:       c3                      ret

000000000000102f <fun_3>:
    102f:       f3 0f 1e fa             endbr64
    1033:       55                      push   %rbp
    1034:       48 89 e5                mov    %rsp,%rbp
    1037:       89 7d fc                mov    %edi,-0x4(%rbp)
    103a:       89 75 f8                mov    %esi,-0x8(%rbp)
    103d:       8b 45 fc                mov    -0x4(%rbp),%eax
    1040:       2b 45 f8                sub    -0x8(%rbp),%eax
    1043:       5d                      pop    %rbp
    1044:       c3                      ret

0000000000001045 <fun_4>:
    1045:       f3 0f 1e fa             endbr64
    1049:       55                      push   %rbp
    104a:       48 89 e5                mov    %rsp,%rbp
    104d:       89 7d fc                mov    %edi,-0x4(%rbp)
    1050:       89 75 f8                mov    %esi,-0x8(%rbp)
    1053:       8b 45 fc                mov    -0x4(%rbp),%eax
    1056:       99                      cltd
    1057:       f7 7d f8                idivl  -0x8(%rbp)
    105a:       5d                      pop    %rbp
    105b:       c3                      ret

000000000000105c <fun_5>:
    105c:       f3 0f 1e fa             endbr64
    1060:       55                      push   %rbp
    1061:       48 89 e5                mov    %rsp,%rbp
    1064:       89 7d fc                mov    %edi,-0x4(%rbp)
    1067:       89 75 f8                mov    %esi,-0x8(%rbp)
    106a:       8b 45 fc                mov    -0x4(%rbp),%eax
    106d:       33 45 f8                xor    -0x8(%rbp),%eax
    1070:       5d                      pop    %rbp
    1071:       c3                      ret

0000000000001072 <main>:
    1072:       f3 0f 1e fa             endbr64
    1076:       55                      push   %rbp
    1077:       48 89 e5                mov    %rsp,%rbp
    107a:       53                      push   %rbx
    107b:       be 64 00 00 00          mov    $0x64,%esi
    1080:       bf 64 00 00 00          mov    $0x64,%edi
    1085:       e8 76 ff ff ff          call   1000 <fun_1>
    108a:       89 c3                   mov    %eax,%ebx
    108c:       be 09 02 00 00          mov    $0x209,%esi
    1091:       bf 03 00 00 00          mov    $0x3,%edi
    1096:       e8 7d ff ff ff          call   1018 <fun_2>
    109b:       01 c3                   add    %eax,%ebx
    109d:       be 4f 02 00 00          mov    $0x24f,%esi
    10a2:       bf 01 00 00 00          mov    $0x1,%edi
    10a7:       e8 83 ff ff ff          call   102f <fun_3>
    10ac:       01 c3                   add    %eax,%ebx
    10ae:       be 20 00 00 00          mov    $0x20,%esi
    10b3:       bf 57 02 00 00          mov    $0x257,%edi
    10b8:       e8 88 ff ff ff          call   1045 <fun_4>
    10bd:       01 c3                   add    %eax,%ebx
    10bf:       be 0d 00 00 00          mov    $0xd,%esi
    10c4:       bf 1d 00 00 00          mov    $0x1d,%edi
    10c9:       e8 8e ff ff ff          call   105c <fun_5>
    10ce:       01 d8                   add    %ebx,%eax
    10d0:       48 8b 5d f8             mov    -0x8(%rbp),%rbx
    10d4:       c9                      leave
    10d5:       c3                      ret */
