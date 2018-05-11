#include <string.h>
#include <stdio.h>
#include <time.h>
#include <poll.h>
#include <cstdlib>
#include <sys/wait.h>
#include <climits>

#include "uni.h"
#include "rwops.h"
#include "signalproc.h"

const int BUF_SIZE = 256;

char ip[] = "255.255.255.255";
const unsigned short port = 3456;

void str_echo(int fd) {
  char buf[BUF_SIZE] = {0};
  while(1) {
    ssize_t nread = _read(fd, buf, sizeof(buf));
    if(nread > 0) {
      _write(fd, buf, nread);
      memset(buf, 0, sizeof(buf));
    } else if(nread == 0) {
      printf("EOF of fd:%d\n", fd);
      return ;
    } else {
      printf("error in read fd:%d\n", fd);
      return ;
    }
  }
}

const unsigned CLIENT_MAX_NUM = 16;
typedef struct pollfd pollfd_t;
typedef pollfd_t* pollfd_ptr;
int main(int argc, char *argv[])
{
  int res = 0;
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("listenfd => %d\n", listenfd);
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
  pollfd_t *clients = new pollfd_t[CLIENT_MAX_NUM];
  memset(clients, 0, sizeof(pollfd_t)*CLIENT_MAX_NUM);
  for(unsigned n=0; n<CLIENT_MAX_NUM; n++) {
    clients[n].fd = -1;
  }
  unsigned npoll = 0;
  clients[npoll].events = POLLRDNORM;
  clients[npoll].fd = listenfd;
  ++ npoll;
  while(1) {
    int nready = poll(clients, npoll, -1);

    if(nready < 0) {
      perror("poll error!\n");
      break;
    }

    if(clients[0].revents & POLLRDNORM) {
      sockaddr csa;
      socklen_t csa_len = sizeof(sockaddr);
      int csock = _accept(listenfd, &csa, &csa_len);
      if(csock > 0) {
        if(npoll == CLIENT_MAX_NUM - 1) {
          printf("clients queue overflow\n");
          close(csock);
        } else {
          for(unsigned idx = 1; idx < CLIENT_MAX_NUM; idx ++) {
            if(clients[idx].fd == -1) {
              memset(&clients[idx], 0, sizeof(pollfd_t));
              clients[idx].fd = csock;
              clients[idx].events = POLLRDNORM;
              clients[idx].revents = 0;
              ++ npoll;
              printf("clients[%u]:%d connect req, %u clients\n", idx, csock, npoll);
              break;
            }
          }
        }
        nready --;
        if(!nready) {
          continue;
        }
      } else {
        perror("accept failed!\n");
        break;
      }

    }

    for(unsigned idx = 1; idx < CLIENT_MAX_NUM; idx ++) {
      pollfd_t *client_pollfd =  &clients[idx];
      if(client_pollfd->fd <= 0) {
        continue;
      }
//      printf("clients[%u]:%d revent:0x%02X\n", idx, clients[idx].fd, clients[idx].revents);
      if(client_pollfd->revents & (POLLRDNORM|POLLERR)) {
        char buf[BUF_SIZE] = {0};
        memset(buf, 0, sizeof(buf));
        ssize_t nread = _read(client_pollfd->fd, buf, sizeof(buf));

        if(nread > 0) {
          printf("wr:%s\n", buf);
          ssize_t nwrite = _write(client_pollfd->fd, buf, nread);

          if(nwrite < 0) {
            printf("write error csock:%d\n",client_pollfd->fd);
            perror("shit happen in %d write!");
          }
        } else if(nread == 0) {
          printf("csock:%d EOF\n", client_pollfd->fd);
          close(client_pollfd->fd);
          client_pollfd->fd = -1;
          client_pollfd->revents = 0;
          -- npoll;
        } else{
          if(errno == ECONNRESET) {
            -- npoll;
            printf("client:%d reset, %u clients\n", client_pollfd->fd, npoll);
            close(client_pollfd->fd);
            client_pollfd->fd = -1;
            client_pollfd->revents = 0;
          } else {
            printf("client:%d read error, %u clients\n", client_pollfd->fd, npoll);
          }
        }
        nready --;
        if(!nread) {
          break;
        }
      }
    }
  }
  delete[] clients;
  exit(0);
}
