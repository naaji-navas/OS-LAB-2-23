#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
  int a = 10;

  int *p1 = &a;
  int **p2 = &p1;
  int ***p3 = &p2;
  ***p3 = 20;
  printf("%d\n", a);


  // write here to the code to make
  // int***p = 20;
}