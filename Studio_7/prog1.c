// Nabeel Sait and Cemil Can Ali Marandi
// 1/31/2020
// This program prints a message

#include <unistd.h>

int main(int argc, char* argv[]) {
   
   char buffer[] = "Hello, world!\n";
   write(STDOUT_FILENO, buffer, 14);
   
   return 0;
}

