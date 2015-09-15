
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
	int fd, n, newfd, nw, addrlen;
	struct sockaddr_in addr;
	struct hostent *h;
	char *ptr, buffer[128];

	if((h=gethostbyname("lima")) == NULL) exit(1);
	fd= socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1) exit(1);
	memset((void*) &addr, (int) '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	//addr.sin_addr =
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//addr.sin_addr.s_addr = ((struct in_addr *) (h->h_addr_list[0]))->s_addr;
	addr.sin_port = htons(9000);

	if(bind(fd, (struct sockaddr*) &addr, sizeof(addr)) ==-1)
		exit(1);
	if(listen(fd, 5) == -1) exit(1);

	while(1) {
		addrlen = sizeof(addr);
		if((newfd = accept(fd, (struct sockaddr*) &addr, &addrlen)) == -1)
			exit(1);
		while((n = read(newfd, buffer, 128)) != 0) {
			if(n == -1) exit(1);
			ptr= &buffer[0];
			while(n>0) {if((nw= write(newfd, ptr, n)) <= 0) exit(1);
				n -= nw; ptr +=nw;}
		}
		close(newfd);
	}
//	close(fd); exit(0);
}	
	
