//Nabeel Sait and Cemil Can Ali Marandi
//1/31/2020
//This program reads an input and prints it

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char* argv[])
{
   int size = 50;
   char buffer[size];

   while(1)
   {
      char *check = fgets(buffer, size, stdin);
      if (check == NULL)
         break;
      printf("Program 2 got: %s\n", buffer);
   }
}
      
      
