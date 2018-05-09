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

void waitchld(int sig) {
  int status;
  int pid = waitpid(-1, &status, WNOHANG);
  printf("pid:%d exit:%d\n", pid, status);
}

void waitact(int sig, siginfo_t *ifo, void *ptr) {
  int status;

  int pid = waitpid(-1, &status, WNOHANG);
  printf("pid:%d exit:%d\n", pid, status);
}


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
  res = bind(listenfd, (sockaddr*)&sa_in, len);
  if(res < 0) {
    perror("bind on 127.0.0.1:3456 failed!");
    return -1;
  }

  res = listen(listenfd, 10);
  if(res < 0) {
    perror("listen failed!");
    return -1;
  }

  printf("Datetime server is on, pid:%d\n",getpid());
  Signal(SIGCHLD, waitact);

  while(1) {
    sockaddr csa;
    socklen_t csa_len;
    int csock = _accept(listenfd, &csa, &csa_len);
    printf("accept: csock:%d errno:%s\n",csock,strerror(errno));

    int pid = fork();
    if(pid == 0) {
      close(listenfd);
      if(csock > 0) {
        str_echo(csock);
        close(csock);
        exit(0);
      }
    } else {
      printf("fork %d success!\n", pid);
      close(csock);
    }
  }
}
