#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>


int main(int argc, char *argv[])
{


	struct addrinfo				hints, *res, *p;
	int					status;
	char					ipstr[INET6_ADDRSTRLEN];


        if (argc < 2) {
		fprintf(stderr, "usage: showip hostname\n");
		return 1;
  }

	memset(&hints, 0, sizeof(hints));				   /* reset all fields in the addrinfo struct */
	hints.ai_family = AF_UNSPEC;					   /* this allows for ip4 or ip6 */
	hints.ai_socktype = SOCK_STREAM;				   /* TCP stream connection as opposed to udp datagram */

  
	if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0){
		fprintf(stderr, "getaddinfo error %s\n", gai_strerror(status));
		return 2;
	}

	printf("\nIP for Domain: %s\n",argv[1]);

	void *addr;
	char *version;

	for (p = res; p != NULL; p = p->ai_next) {
		if (p->ai_family == AF_INET) {
			struct sockaddr_in *ip4 = (struct sockaddr_in *) p->ai_addr;
			addr = &(ip4->sin_addr);
			version = "IPV4";
		}
		else {
			struct sockaddr_in6 *ip6 = (struct sockaddr_in6 *) p->ai_addr;
			addr =  &(ip6->sin6_addr);
			version = "IPV6";

		}

                inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf("%s: %s\n",version, ipstr);
		
	}

	freeaddrinfo(res);
	return 0;
}
