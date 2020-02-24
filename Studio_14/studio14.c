#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
int main (int argc, char* argv[]){
   if (argc != 2)
   {
      printf("usage: ./studio14 <number>\n");
      exit(-1);
   }
   int number = atoi(argv[1]);
   int i;
   int j;

   omp_set_num_threads(5);
   #pragma omp parallel for schedule( dynamic, 2 )
   for (i=0; i<number; i++)
   {
      //int max = omp_get_max_threads();
      //printf("Max threads: %d\n", max);
      if (i <= 4) sleep(1);
      int num = omp_get_thread_num();
      printf("Index: %d Thread #: %d\n", i, num);  
   }
   return 0;
}
