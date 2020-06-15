#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <zconf.h>

int main() {
//      int socket(int domain, int type, int protocol);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);


//      int connect(int sockfd, const struct sockaddr *addr,
//                   socklen_t addrlen);

    struct sockaddr_in ssockaddr;

    ssockaddr.sin_port = htons(9999);
    ssockaddr.sin_family = AF_INET;

    char *addr = "127.0.0.1";
    inet_pton(AF_INET, addr, &ssockaddr.sin_addr.s_addr);

    int fd = connect(sockfd, (const struct sockaddr *) &ssockaddr, sizeof(ssockaddr));

    char buff[BUFSIZ];
    char receive[BUFSIZ];

    while (1) {
        int n = read(STDIN_FILENO, buff, BUFSIZ);
        if (n > 0) {
            write(sockfd, buff, n);
        }
        int readn = read(sockfd, receive, BUFSIZ);
        if (readn > 0) {
            write(STDERR_FILENO, receive, readn);
        }
    }

    return 0;
}