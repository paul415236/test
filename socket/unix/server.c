#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>



char *socket_path = "/tmp/socket";

int main() {
  int fd, i;
  int clients[10], num_clients;
  fd_set read_set;
  char buf[100];

  struct sockaddr_un addr;

  if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    perror("socket error");
    exit(-1);
  }
  printf("11111 \n");
  unlink(socket_path);

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

  if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("bind error");
    exit(-1);
  }

  if (listen(fd, 5) == -1) {
    perror("listen error");
    exit(-1);
  }

  num_clients = 0;

  while (1) {
    FD_ZERO(&read_set);
    FD_SET(fd, &read_set);

    for (i = 0; i < num_clients; i++) {
      FD_SET(clients[i], &read_set);
    }

    select(fd + num_clients + 1, &read_set, NULL, NULL, NULL);

    if (FD_ISSET(fd, &read_set)) {
      if ( (clients[num_clients++] = accept(fd, NULL, NULL)) == -1) {
        perror("accept error");
        continue;
      }
      printf("we got a connection!\n");
    }

    for (i = 0; i < num_clients; i++) {
      if (FD_ISSET(clients[i], &read_set)) {
        read(clients[i], buf, sizeof(buf));
        printf("client %d says: %s\n", i, buf);
      }
    }
  }
}
