// Cemil Can Ali Marandi & Nabeel Sait
// 1/17/2020
// The goal for this program is to open a file

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define bufferSize 200

int main(int argc, char* argv[]){
   
   char* inputFileName = argv[1];	
   int inputFD = open(inputFileName, O_RDONLY);
   if (inputFD == -1)
   {
      perror("Error opening file");
      exit(-1);
   }
   char buffer[bufferSize];
 
   int bytes_read = read(inputFD, buffer, bufferSize);
   while (bytes_read > 0)
   {
      write(STDOUT_FILENO, buffer, bytes_read);
      bytes_read = read(inputFD, buffer, bufferSize);
   }
    
   close(inputFD);
   return 0;
}
