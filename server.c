#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <zconf.h>
#include <arpa/inet.h>

int main() {

//      int socket(int domain, int type, int protocol);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);


//   int bind(int sockfd, const struct sockaddr *addr,
//                socklen_t addrlen);

    struct sockaddr_in sockaddr;

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(9999);
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (const struct sockaddr *) &sockaddr, sizeof(sockaddr));

    //  int listen(int sockfd, int backlog);

    listen(sockfd, 128);

    //  int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

    struct sockaddr_in csockaddr;

    socklen_t socklen = sizeof(csockaddr);

    int cfd = accept(sockfd, (struct sockaddr *) &csockaddr, &socklen);

//       const char *inet_ntop(int af, const void *src,
//                             char *dst, socklen_t size);

    char client_ip[1024];
    inet_ntop(AF_INET, &csockaddr.sin_addr.s_addr, client_ip, sizeof(client_ip));

    fprintf(stderr, "client ip is %s", client_ip);

    char buff[BUFSIZ];
    //read
    int rsize;

    while (1) {
        rsize = read(cfd, buff, BUFSIZ);
        if (rsize > 0) {
            for (int i = 0; i < rsize; ++i) {
                buff[i] = toupper(buff[i]);
            }
            write(cfd, buff, rsize);
        }
    }

    return 0;
}
