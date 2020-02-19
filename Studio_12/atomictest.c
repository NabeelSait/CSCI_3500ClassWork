//Nabeel Sait and Cemil Can Ali Marandi
//2/15/2020
//This program tests an atomic instruction

#include <stdio.h>

int main(int argc, char* argv[])
{
  int i = 10;
  
  printf("Before addition: %d\n", i);
  __sync_add_and_fetch(&i, 5);
  printf("After addition %d\n", i);
}
