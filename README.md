# project-tcp-ip
//echo # project-tcp-ip >> README.md
//git init
//git add README.md
//git commit -m "first commit"
//git remote add origin https://github.com/SLTCP/project-tcp-ip.git
//git push -u origin master

//socket function

#include <sys/socket.h>
#include <unist.h>

pid_t fork(void);



int socket (int family, int type, int protocol);
int connect (int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
int bind(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *cliaddr,
socklen_t *addrlen);
ssize_t send(int sockfd, const void *buf, size_t nbytes, int flags);
ssize_t recv(int sockfd, void *buf, size_t nbytes, int flags);
int close(int sockfd);
