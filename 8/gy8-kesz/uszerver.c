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
  if((sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
  {
    perror("socket");
    return -1;
  }

  /* Kitöltjük a címstruktúrát */
  memset(&address, 0, sizeof(address));
  address.sun_family = AF_UNIX;
  /* Absztrakt nevet használunk, ezért az első karakter: \0 */
  address.sun_path[0] = 0;
  /* A második karaktertől bemásoljuk a címet. */
  strncpy(address.sun_path + 1, ADDR, sizeof(address.sun_path) - 2);

  /* A teljes címhossz tartalmazza a sun_family elemet és az elérési út hosszát. */
  addrlen = sizeof(address.sun_family) + strlen(address.sun_path + 1) + 1;

  /* A socketet hozzákötjuk a címhez. */
  if(bind(sock, (struct sockaddr *) &address, addrlen))
  {
    perror("bind");
    return -1;
  }

  /* Bekapcsoljuk a szerver módot. */
  if(listen(sock, 5))
  {
    perror("listen");
    return -1;
  }

  /* Fogadjuk a kapcsolódásokat. */
  while((conn = accept(sock, (struct sockaddr*)&address, &addrlen)) >= 0)
  {
    /* Fogadjuk az adatokat. */
    printf("Adatok erkeznek...\n");
    while((amount = read(conn, buf, sizeof (buf))) > 0) {
      if(write(STDOUT_FILENO, buf, amount) != amount)
      {
    	perror("write");
    	return -1;
      }
    }

    if(amount < 0) {
        perror("read");
        return -1;
    }

    printf("...vege\n");
    /* Bontjuk a kapcsolatot. */
    close(conn);

  }

  if(conn < 0)
  {
    perror("accept");
    return -1;
  }

  /* Lezárjuk a szerver socketet. */
  close(sock);
  return 0;
}
