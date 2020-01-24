// Cemil Can Ali Marandi & Nabeel Sait
// 1/17/2020
// The goal for this program is to mimic the behavior of cat

#include <unistd.h>
#include <stdio.h>
#define bufferSize 1

int main(int argc, char* argv[]){
   char buffer [bufferSize];

   while (1) {
      int bytes_read = read(STDIN_FILENO, buffer, bufferSize);
      if (bytes_read == 0)
         break;
      write(STDOUT_FILENO,  &buffer, bytes_read);
    }
   return 0;
}
