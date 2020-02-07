//Nabeel Sait and Cemil Can Ali Marandi
//1/29/20
//This program is designed to test different methods of manipulating processes

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
   int cPID = fork();
   char* child_argv[] = {"ls", "-l", NULL};
   char* child_prog = child_argv[0];
   
   if (cPID == 0)
   {
      sleep(3);
      int PID = getpid();
      printf("Child PID: %d\n", PID);
      execvp(child_prog, child_argv);
   }
   else
   {
      waitpid( cPID, NULL, 0);
      int PID = getpid();
      printf("Parent PID: %d\n", PID);
   }	
}
