#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int pipeline(char* string, int count, int save_out);

int checkErr(char* message)
{
   if (errno != 0)
   {
      perror(message);
      return 1;
   }
   else
      return 0;
}

void ignoreSignal(int signum) {;}

int main(int argc, char* argv[])
{
   char* cmd;
   int size = 256;
   char buffer[size];
   int save_in = dup(STDIN_FILENO);

   signal(2, ignoreSignal);
   
   while(1)
   {
      char* home = getenv("HOME");
      char cwd[size];
      getcwd(cwd, size);

      int home_len = strlen(home); //length of home directory
      char* home_start = strstr(cwd, home); //Start pointer of home directory in cwd
      int home_start_len = strlen(home_start); //Length of cwd after home directory

      memmove(cwd, home_start + home_len + 1, home_start_len - home_len + 1);

      printf("slush|%s> ", cwd);
      dup2(save_in, STDIN_FILENO);
      char* check = fgets(buffer, size, stdin);
      if (check == NULL)
      {
         printf("Exiting...\n");
         exit(0);
      }
      int length = strlen(buffer);
      if (length == 1) { // ENTER with no command
        continue;
      }

      char* string = strtok(buffer, "\n");
      char nstring[256];
      strcpy(nstring, string);

      char* prog = strtok(string, "(");
      cmd = strtok(prog, " ");
      if (strcmp(cmd, "cd") == 0)
      {
         const char* dir = strtok(NULL, " ");
         if (chdir(dir) != 0)
            perror("Invalid Path");
      }
      else
      {
         int save_out = dup(STDOUT_FILENO);
         pipeline(nstring, 0, save_out);
      }
   }
}

int pipeline(char* string, int count, int save_out)
{
   char nstring[256];
   strcpy(nstring, string);

   char safe_prog[256];
   char* prog;

   //Recursing to end
   if (count == 0)
   {
      prog = strtok(string, "(");
      strcpy(safe_prog, prog);
   }
   else
   {
      prog = strtok(NULL, "(");
      if (prog == NULL)
         return -1;
   }

   strcpy(safe_prog, prog);
   int prev_FD = pipeline(nstring, count + 1, save_out);
   if (prev_FD == -2)
      return -2;

   //Getting command
   int max_args = 15;
   int max_argv_size = max_args + 2; //one for argv[0], one for null terminator
   char* cmd;
   char* my_argv[max_argv_size];

   cmd = strtok(safe_prog, " ");
   my_argv[0] = cmd;

   if (cmd == NULL)
   {
     printf("Invalid null command\n");
     return -2;
   }

   int i = 1;
   while(1)
   {
      char* token = strtok(NULL, " ");
      if((token == NULL) || (i >= max_args))
         break;
      my_argv[i] = token;
      i ++;
   }
   my_argv[i] = '\0';

   //forking and pipelining
   int c_fd[2];
   if (count != 0)
      pipe(c_fd);
   if (checkErr("Pipe Faliure")) { return -2;}

   int cPID = fork();
   if (checkErr("Fork Faliure")) {return -2;}

   if (cPID == 0)
   {
      if ((count == 0) && (prev_FD == -1))
      {
         execvp(cmd, my_argv);
         if (checkErr(cmd)) {return -2;}
      }
      else
      {
         if(prev_FD != -1) //Not the first command
            dup2(prev_FD, STDIN_FILENO);

         if (count == 0) //Last command
         {
            dup2(save_out, STDOUT_FILENO);
         }
         else //Not the last command
         {
            close(c_fd[0]);
            dup2(c_fd[1], STDOUT_FILENO);
         }
         execvp(cmd, my_argv);
         if (checkErr(cmd)) { return -2; }
      }
   }
   else
   {
      if (prev_FD != -1) //Not the first command
         close(prev_FD);

      if (count != 0)
         close(c_fd[1]);

      waitpid(cPID, NULL, 0);
      return c_fd[0];
   }
}
