#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

#define PORT 59000
int main() {
	int fd, n;
	struct sockaddr_in addr;
	struct hostent *h;
	struct in_addr *a;
	int addrlen;
char buffer[128];

	if((h=gethostbyname("lima")) == NULL) exit(1);

	printf("official host name: %s\n", h->h_name);
	
	fd=socket(AF_INET, SOCK_DGRAM, 0); // udp socket
	memset((void*) &addr, (int) '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ((struct in_addr *) (h->h_addr_list[0]))->s_addr;
	addr.sin_port = htons((u_short) PORT);

	addrlen = sizeof(addr);

	n=sendto(fd, "Hello\n", 7, 0, (struct sockaddr *) &addr, addrlen);
	if(n== -1) exit(1);

	addrlen = sizeof(addr);
n = recvfrom(fd, buffer, 128, 0, (struct sockaddr *) &addr, &addrlen);

	if(n== -1) exit(1);
	write(1, "echo: ", 6);
	write(1, buffer, n);

	close(fd);
	exit(0);
	write(1, "echo: ", 6);
	write(1, buffer, n);

	close(fd);
	exit(0);
}
