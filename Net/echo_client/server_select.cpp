#include <string.h>
#include <stdio.h>
#include <time.h>

#include <cstdlib>
#include <sys/wait.h>

#include "uni.h"
#include "rwops.h"
#include "signalproc.h"

const int BUF_SIZE = 256;

char ip[] = "255.255.255.255";
const unsigned short port = 3456;

void str_echo(int fd) {
  ssize_t n;
  char buf[BUF_SIZE] = {0};
  again:
  memset(buf, 0, sizeof(buf));
  while((n=read(fd, buf, sizeof(buf))) > 0) {
    buf[strlen(buf)+1] = 0;
    writen(fd, buf, strlen(buf)+1);
    memset(buf, 0, sizeof(buf));
  }
  if( n<0 && errno == EINTR){
    goto again;
  }
}
const unsigned CLIENT_MAX_NUM = 16;
int main(int argc, char *argv[])
{
  int res = 0;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("sockfd:%d\n", sockfd);
  if(sockfd < 0) {
    perror("socket create failed!");
    return -1;
  }

  struct sockaddr_in sa_in;
  bzero(&sa_in, sizeof(sa_in));
  sa_in.sin_family = AF_INET;
  sa_in.sin_port = htons(port);
  sa_in.sin_addr.s_addr = INADDR_ANY;

  socklen_t len = sizeof(sa_in);
  res = bind(sockfd, (sockaddr*)&sa_in, len);
  if(res < 0) {
    perror("bind on 127.0.0.1:3456 failed!");
    return -1;
  }

  res = listen(sockfd, 10);
  if(res < 0) {
    perror("listen failed!");
    return -1;
  }

  printf("Datetime server is on, pid:%d\n",getpid());
  int maxfdp1 = sockfd + 1;
  fd_set rd_set;
  int clients[CLIENT_MAX_NUM] = {-1};
  while(1) {
    FD_ZERO(&rd_set);
    FD_SET(sockfd, &rd_set);

    select(maxfdp1, &rd_set, nullptr, nullptr, nullptr);
    if(FD_ISSET(sockfd, &rd_set)) {
      sockaddr csa;
      socklen_t csa_len;
      int csock = accept(sockfd, &csa, &csa_len);
      printf("accept: csock:%d errno:%s\n",csock,strerror(errno));
      if(csock<0 && errno == EINTR) {
        printf("accept interrupt by sigchld  cscock:%d errno:%s\n", csock, strerror(errno));

        continue;
      }
      clients[(unsigned)csock] = csock;
    }
    for(unsigned i=0; i<CLIENT_MAX_NUM; i++) {
      if(clients[i] != -1) {
        if(FD_ISSET(clients[i], &rd_set)) {
          char buf[BUF_SIZE] = {0};
          try_again:
          int nread = read(clients[i], buf, sizeof(buf));
          if(nread > 0) {
            buf[nread+1] = 0;
            writen(clients[i], buf, sizeof(buf));
          } else if(nread == 0) {
            printf("sockfd:%d EOF\n", clients[i]);
            close(clients[i]);
            clients[i] = -1;
          } else if(errno == EINTR){
            printf("read interrupted\n");
            goto try_again;
          }
        }
      }
    }
  }
}
