#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define MY_SOCK_PATH "sockethandler"
#define LISTEN_BACKLOG 50

#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

int buffer_size = 1024;

int main(int argc, char *argv[]) {
   
   int buffer[buffer_size];
   int ret, sfd, cfd;
   struct sockaddr_un my_addr;
   socklen_t addr_size;

   sfd = socket(AF_UNIX, SOCK_STREAM, 0);
   if (sfd == -1)
   {
      handle_error("socket");
   }

   memset(&my_addr, 0, sizeof(struct sockaddr_un));
   my_addr.sun_family = AF_UNIX;
   strncpy(my_addr.sun_path, MY_SOCK_PATH,
         sizeof(my_addr.sun_path) - 1);

   addr_size = sizeof(struct sockaddr_un);
   ret = connect(sfd, (struct sockaddr *) &my_addr, addr_size);

   if( ret == -1 ) {
      perror("Could not connect");
   }
   
   printf("Connected to server successfully\n");
   printf("Enter a message: ");
   scanf("%s", buffer);
   write (sfd, buffer, buffer_size);
}
