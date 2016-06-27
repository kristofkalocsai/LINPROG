/* udpszervermulti.c
 * 
 * UDP többesküldés példa.
 * A program az udpszerver.c példa továbbfejlesztése. A program egy 
 * IPv4 (224.1.1.1) és egy IPv6 (ff02::13D) multicast címre regisztrál,
 * így képes fogadni a megadott címekre küldött multicast csomagokat.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT "1122"

int main() 
{
  struct addrinfo hints;
  struct addrinfo* res;
  int err;
  struct sockaddr_in6 addr;
  socklen_t addrlen;
  char ips[NI_MAXHOST];
  char servs[NI_MAXSERV];
  int sock;
  char buf[256];
  int len;
  struct ip_mreq mreq;
  struct ipv6_mreq mreq6;
  
  memset(&hints, 0, sizeof(hints));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_DGRAM;

  err = getaddrinfo(NULL, PORT, &hints, &res);
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
    return 1;
  }
  
  if(bind(sock, res->ai_addr, res->ai_addrlen) < 0)
  {
    perror("bind");    
    return 1;
  }

  freeaddrinfo(res);

  // TODO: regisztrálás a 224.1.1.1 és az ff02::13D csoportokba 

  addrlen = sizeof(addr);
  while((len = recvfrom(sock, buf, sizeof(buf), 0, 
    (struct sockaddr*)&addr, &addrlen)) > 0)
  {
    if(getnameinfo((struct sockaddr*)&addr, addrlen, 
      ips, sizeof(ips), servs, sizeof(servs), 0) == 0)
    {
      fprintf(stdout, "%s:%s: ", ips, servs);
      fflush(stdout);
    }
    
    write(STDOUT_FILENO, buf, len);
  }
  
  close(sock);
  
  return 0;
}
