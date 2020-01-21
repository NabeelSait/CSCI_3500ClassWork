// Cemil Can Ali Marandi & Nabeel Sait
// 1/17/2020
// The goal for this program is to mimic the behavior of cat

#include <unistd.h>
#include <stdio.h>
#define bufferSize 200

int main(int argc, char* argv[]){
   char buffer [bufferSize];

   while ((read(STDIN_FILENO, buffer, bufferSize)) > 0) {
           write(STDOUT_FILENO,  &buffer, bufferSize);
    }
   return 0;
}
