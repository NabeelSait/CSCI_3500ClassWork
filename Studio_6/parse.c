//Nabeel Sait and Cemil Can Ali Marandi
//1/30/20
//This program is designed to test input parsing

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
   printf("Enter input: ");
   
   int max_args = 15;
   int max_argv_size = max_args + 2; //one for argv[0], one for null terminator
   char* cmd;
   char* my_argv[max_argv_size];
   
   int size = 50;
   char buffer[size];
   
   fgets(buffer, size, stdin);
   char* string = strtok(buffer, "\n");
   cmd  = strtok(string, " ");

   my_argv[0] = cmd;   
   int count = 1;
   
   while(1)
   {
      char* token = strtok(NULL, " ");
      if((token == NULL) || (count >= max_args))
         break;
      my_argv[count] = token;
      count ++;
   }
   my_argv[count + 1] = '\0';

   execvp( cmd, my_argv );
   
}
