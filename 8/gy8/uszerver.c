/* uszerver.c
 *
 * Egyszerű példa szerver a Unix domain socket használatára.
 *
 */

#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define ADDR "myaddr"

int main(void)
{
  struct sockaddr_un address;
  int sock, conn;
  socklen_t addrlen;
  char buf[1024];
  int amount;

  /* Létrehozzuk a socketet. */
  /* int socket(int domain, int type, int protocol); */
  if((sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
  {
    perror("socket");
    return -1;
  }

  /* Kitöltjük a címstruktúrát */
  /* address.sun_family, address.sun_path */
  /* Absztrakt nevet használunk, ezért az első karakter: \0 */
  /* A második karaktertől bemásoljuk a címet. */
  memset(&address, 0, sizeof(address));
  address.sun_family = AF_UNIX;
  address.sun_path[0] = 0;
  strncpy(address.sun_path + 1, ADDR, sizeof(address.sun_path) - 2);

  /* A teljes címhossz tartalmazza a sun_family elemet és az elérési út hosszát. */
  /* addrlen */
  addrlen = sizeof(address.sun_family) +
  strnlen(address.sun_path + 1, sizeof(address.sun_path) - 1) + 1;

  /* A socketet hozzákötjuk a címhez. */
  /* int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); */
  if (bind(sock, (struct sockaddr*)&address, addrlen) < 0) {
      perror("bind");
      return -1;
  }
  else printf("binded!\n");

  /* Bekapcsoljuk a szerver módot. */
  /* int listen(int sockfd, int backlog); */
  if (listen(sock, 5) ) {
      perror("listen");
      return -1;
  }
  else printf("listening\n");

  /* Fogadjuk a kapcsolódásokat. */
  /* int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); */
  while((conn = accept(sock, (struct sockaddr*)&address, &addrlen)) >= 0)
  {
    /* FoDrigadjuk az adatokat. */
    printf("Adatok erkeznek...\n");

    /* Olvasunk a kapcsolat socketből amíg lehet, és kiírjuk a képernyőre (STDOUT_FILENO) */
    /* ssize_t read(int fd, void *buf, size_t count); */
    /* ssize_t write(int fd, const void *buf, size_t count); */
    while((amount = read(conn, buf, sizeof(buf))) > 0) {
        if (write(STDOUT_FILENO, buf, amount) != amount) {
            perror("write");
            return -1;
        }
    }

    if (amount < 0) {
        perror("read");
        return -1;
    }

    printf("...vege\n");
    /* Bontjuk a kapcsolatot. */
    /* int close(int fd); */
    close(conn);
  }

  /* Ide kerül az accept hibájának vizsgálata */
  if (conn < 0) {
      perror("accept");
      return -1;
  }

  /* Lezárjuk a szerver socketet. */
  /* int close(int fd); */
  close(sock);

  return 0;
}
