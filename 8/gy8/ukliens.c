/* ukliens.c
 *
 * Egyszerű pelda kliens a Unix domain socket használatára.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define ADDR "myaddr"

int main(void)
{
  struct sockaddr_un address;
  int sock;
  size_t addrlen;
  char buf[1024];
  int amount;

  /* Létrehozzuk a socket-et. */
  if((sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
  {
    perror("socket");
    return -1;
  }

  /* Kitöltjük a címstruktúrát */
  memset(&address, 0, sizeof(address));
  address.sun_family = AF_UNIX;
  address.sun_path[0] = 0;
  strncpy(address.sun_path + 1, ADDR, sizeof(address.sun_path) - 2);

  /* A teljes cím hossz tartalmazza a sun_family elemet és az elérési út hosszát. */
  addrlen = sizeof(address.sun_family) +
  strnlen(address.sun_path + 1, sizeof(address.sun_path) - 1) + 1;

  /* Kapcsolodunk a szerverhez. */
  /* int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen); */
  if (connect(sock, (struct sockaddr*) &address, addrlen) < 0) {
      perror("connect");
      return -1;
  }
  else {
      printf("connected.\n");
  }

  /* Elkuldjuk az adatokat, amit a stdinről olvasunk (STDIN_FILENO) */
  /* ssize_t read(int fd, void *buf, size_t count); */
  /* ssize_t write(int fd, const void *buf, size_t count); */
  while((amount = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
      if(write(sock, buf, amount) != amount) {
          perror("write");
          return -1;
      }
  }

  if (amount < 0) {
      perror("read");
      return -1;
  }

  /* Bontjuk a kapcsolatot. */
  close(sock);
  return 0;
}
