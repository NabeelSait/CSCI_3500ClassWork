//Nabeel Sait and Cemil Can Ali Marandi
// 1/31/20
//This program creates a pipeline

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
   int pfd[2];
   pipe(pfd);

   int cPID1 = fork();

   if (cPID1 == 0)
   {
      close(pfd[0]);
      dup2(pfd[1], STDOUT_FILENO);
      char* cmd = "./prog1";
      char* myargv[] = {"prog1", '\0'};
      int ret = execvp( cmd, myargv );
      if( ret == -1 ) perror("Error exec'ing prog1");
   }
   else
   {
      int cPID2 = fork();
      if (cPID2 == 0)
      {
         close(pfd[1]);
         dup2(pfd[0], STDIN_FILENO);
         char* cmd = "./prog2";
         char* myargv[] = {"prog2", '\0'};
         int ret = execvp( cmd, myargv );
         if( ret == -1 ) perror("Error exec'ing prog2");
      }
      else
      {
         waitpid(cPID1, NULL, 0);
         close(pfd[1]);
         waitpid(cPID2, NULL, 0);
         close(pfd[0]);
      }
   }
}
