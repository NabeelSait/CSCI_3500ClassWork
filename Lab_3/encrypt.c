#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
     printf("usage: encrypt <password> <salt> \n");
     exit(-1);
  }
   
  char* password = argv[1];
  char* salt = argv[2];
  
  char* res = crypt(password, salt);
  printf("Encrypted: %s\n", res);

}
