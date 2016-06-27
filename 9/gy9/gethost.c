/* gethost.c 
 * 
 * Internetes névfeloldás példa. A paraméterként kapott IP címet
 * hoszt névvé alakítja. Támogatja az IPv4 és IPv6 címeket is.
 * 
 */

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
  struct sockaddr_in addr;
  char name[256];
  int err;

  if(argc != 2)
  {
    printf("Hasznalat: %s <IP cim>\n", argv[0]);
    return -1;
  }

  /* A szöveges címet hálózati bináris címmé alakítjuk. */
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  if(inet_pton(AF_INET, argv[1], &addr.sin_addr) == 0)
  {
    perror("inet_pton");
    return -1;
  }

  /* Lekérjük a címhez tartozó nevet. */
  err = getnameinfo((struct sockaddr*)&addr, sizeof(addr), 
    name, sizeof(name), NULL, 0, NI_NAMEREQD);
  if(err != 0)
  {
    fprintf(stderr, "getnameinfo: %s\n", gai_strerror(err));
    return -1;
  }

  printf("A gep neve: %s\n", name);

  return 0;
}
