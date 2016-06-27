/* udpkliens-cork.c
 * 
 * UDP_CORK opció használatát demonstráló példa.
 * A program az udpkliens.c továbbfejlesztése. A bemenetén kapott szöveget
 * egy UDP csomagban küldi el, amikor a bemenetet CTRL+D billentyűkkel
 * lezárjuk.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT "1122"

int main(int argc, char* argv[])
{
  struct addrinfo hints;
  struct addrinfo* res;
  int err;
  int sock;
  char buf[1024];
  int len;
  int state;
  
  if(argc != 2)
  {
    printf("Használat: %s <szerver>\n", argv[0]);
    return 1;
  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  err = getaddrinfo(argv[1], PORT, &hints, &res);
  if(err != 0)
  {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
    return -1;
  }
  if(res == NULL)
  {
    return -1;
  }
  
  sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if(sock < 0)
  {
    perror("socket");
    return -1;
  }

  // TODO: UDP_CORK bebillentése
  
  while((len = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
  {
    sendto(sock, buf, len, 0, res->ai_addr, res->ai_addrlen);
  }
  
  freeaddrinfo(res);

  // TODO: UDP_CORK befejezése

  close(sock);

  return 0;
}
