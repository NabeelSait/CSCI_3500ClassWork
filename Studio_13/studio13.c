#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
int main (int argc, char* argv[]){
   if (argc != 2)
   {
      printf("usage: ./studio13 <number>\n");
      exit(-1);
   }
   int number = atoi(argv[1]);
   int i;
   int j;

   #pragma omp parallel for
       for (i=2; i<number; i++)
       {
          bool prime=true;
          for (j=2; j*j<=i; j++)
          {
              if (i % j == 0)
              {
                  prime=false;
                  break;   
              }
          }  
          //if(prime) printf("prime number :%d\n", i);
        }
    return 0;
}
