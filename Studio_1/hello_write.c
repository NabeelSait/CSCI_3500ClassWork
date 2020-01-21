// Nabeel Sait and Cecil Can Ali Marandi
// 1/13/2020
// This program prints a message

#include <unistd.h>

int main(int argc, char* argv[]) {
   
   char buffer[] = "Hello, world!\n";
   write(STDOUT_FILENO, buffer, 100);
   
   return 0;
}
