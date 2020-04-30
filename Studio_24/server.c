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

int buffer_size = 9000;

int main(int argc, char *argv[]) {
   char buffer[buffer_size];
   char buffer2[buffer_size];
   int sfd, cfd;
   struct sockaddr_un my_addr;
   socklen_t peer_addr_size;
   int connections = 0;

   sfd = socket(AF_UNIX, SOCK_STREAM, 0);
   if (sfd == -1)
   handle_error("socket");

   memset(&my_addr, 0, sizeof(struct sockaddr_un));

   my_addr.sun_family = AF_UNIX;
   strncpy(my_addr.sun_path, MY_SOCK_PATH,
   sizeof(my_addr.sun_path) - 1);

   if (bind(sfd, (struct sockaddr *) &my_addr,
   sizeof(struct sockaddr_un)) == -1)
   handle_error("bind");

   if (listen(sfd, LISTEN_BACKLOG) == -1)
   handle_error("listen");
   while (1) {
      cfd = accept(sfd, NULL, NULL);
      if (cfd == -1)  
         handle_error("accept");

      printf ("Accepted Client Connection\n");

      int bytesRead = read(cfd, buffer, buffer_size);
      if (strncmp(buffer, "quit", 4) == 0)
         exit(0);
      printf("Got '%s' from client\n", buffer);
   }
}
