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
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("listenfd:%d\n", listenfd);
  if(listenfd < 0) {
    perror("socket create failed!");
    return -1;
  }

  struct sockaddr_in sa_in;
  bzero(&sa_in, sizeof(sa_in));
  sa_in.sin_family = AF_INET;
  sa_in.sin_port = htons(port);
  sa_in.sin_addr.s_addr = INADDR_ANY;

  socklen_t len = sizeof(sa_in);
  res = _bind(listenfd, (sockaddr*)&sa_in, len);
  if(res < 0) {
    perror("bind on 127.0.0.1:3456 failed!");
    return -1;
  }

  res = _listen(listenfd, 10);
  if(res < 0) {
    perror("listen failed!");
    return -1;
  }

  printf("Datetime server is on, pid:%d\n",getpid());
  fd_set rd_set;
  int clients[CLIENT_MAX_NUM] = {-1};
  int maxfdp1 = sizeof(clients) + 1;
  FD_ZERO(&rd_set);
  while(1) {
    FD_SET(listenfd, &rd_set);
    int nready = select(maxfdp1, &rd_set, nullptr, nullptr, nullptr);

    if(FD_ISSET(listenfd, &rd_set)) {
      sockaddr csa;
      socklen_t csa_len = sizeof(sockaddr);
      int csock = _accept(listenfd, &csa, &csa_len);

      if(csock > 0) {
        clients[(unsigned)csock] = csock;
        FD_SET(csock, &rd_set);
      }  else {
        perror("accept failed!\n");
        break;
      }
      nready --;
      if(!nready) {
        continue;
      }
    }
    for(unsigned i=0; i<CLIENT_MAX_NUM; i++) {
      if(clients[i] != -1) {
        if(FD_ISSET(clients[i], &rd_set)) {
          char buf[BUF_SIZE] = {0};
          memset(buf, 0, sizeof(buf));
          ssize_t nread = _read(clients[i], buf, sizeof(buf));
          if(nread > 0) {
            ssize_t nwrite = _write(clients[i], buf, nread);

            if(nwrite < 0) {
              printf("write error csock:%d\n",clients[i]);
              perror("shit happen in %d write!");
            }
            FD_SET(clients[i], &rd_set);
          } else if(nread == 0) {
            printf("csock:%d EOF\n", clients[i]);
            close(clients[i]);
            clients[i] = -1;
            FD_CLR(clients[i], &rd_set);
          } else{
            perror("read error\n");
            close(clients[i]);
            clients[i] = -1;
            FD_CLR(clients[i], &rd_set);
          }
          nready --;
          if(!nread) {
            break;

          }
        }
      }
    }
  }
  exit(0);
}
