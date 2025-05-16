#include <stdio.h>

int main() {

  int n;
  char s[] = "123             asdasd456";
  int r;
  sscanf(s, "%d%n", &r,&n);
  printf("\n%d\n",n);

}
