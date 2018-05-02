#include <string.h>
#include <stdio.h>
#include <time.h>

#include <cstdlib>


#include "uni.h"
#include "rwops.h"

const int BUF_SIZE = 2048;

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
  memset(buf, 0, sizeof(buf));
}

int main(int argc, char *argv[])
{
  int res = 0;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
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
  while(1) {
    sockaddr csa;
    socklen_t csa_len;
    int csock = accept(sockfd, &csa, &csa_len);
    int pid = fork();
    if(pid == 0) {
      close(sockfd);
      if(csock > 0) {
//        inet_ntop(AF_INET, &csa, ip, csa_len);
//        printf("child:pid:%d connect from %s:%d\n", getpid(), ip, ntohs(((struct sockaddr_in*)(&csa))->sin_port));
//        time_t now = time(nullptr);
//        char buf[2048];
//        snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&now));
//        write(csock, buf, strlen(buf));
        str_echo(csock);
        close(csock);
        exit(0);
      }
    } else {
      close(csock);
    }
  }

  return 0;
}
