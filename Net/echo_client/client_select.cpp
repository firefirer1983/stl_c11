#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include "uni.h"
#include "rwops.h"

const int BUF_SIZE = 64;

void str_cli(FILE *fp, int sockfd) {
  char send_line[BUF_SIZE], recv_line[BUF_SIZE];
  bool stdin_eof = false;
  while(1) {
    fd_set rd_set;
    FD_ZERO(&rd_set);
    FD_SET(sockfd, &rd_set);
    if(!stdin_eof) {
      FD_SET(fileno(fp), &rd_set);
    }
    int maxfdp1 = (fileno(fp)>sockfd?fileno(fp):sockfd) + 1;
    select(maxfdp1, &rd_set, nullptr, nullptr, nullptr);
    if(FD_ISSET(sockfd, &rd_set)) {
      ssize_t nread = _read(sockfd, recv_line, sizeof(recv_line));
      if(nread == 0) {
        printf("EOF for sockfd\n");
        break;
      } else if(nread < 0) {
        perror("srv terminate connection\n");
        break;
      } else {
        _write(fileno(stdout), recv_line, nread);
      }
    }

    if(FD_ISSET(fileno(fp), &rd_set)) {
      ssize_t nread = _read(fileno(fp), send_line, sizeof(send_line));
      if(nread == 0) {
        printf("EOF for stdin\n");
        stdin_eof = true;
        shutdown(sockfd, SHUT_WR);
        FD_CLR(sockfd, &rd_set);
        continue;
      } else if (nread < 0){
        printf("read file error!\n");
      } else {
        _write(sockfd, send_line,  nread);
      }
//      printf("-> %s\n",send_line);
    }
    memset(send_line, 0, sizeof(send_line));
    memset(recv_line, 0, sizeof(recv_line));
  }
}

char ip[] = "255.255.255.255";
char port[] = "12345";
const char host_ip[] = "192.168.127.127";
const char host_port[] = "3456";
int main(int argc, char *argv[])
{
  memset(ip, 0, sizeof(ip));
  memset(port, 0, sizeof(port));
  if(argc == 3) {
    snprintf(ip, strlen(argv[1])+1, "%s", argv[1]);
    snprintf(port, strlen(argv[2])+1, "%s", argv[2]);
    printf("%s:%s\n", ip, port);
  } else {
    snprintf(ip, strlen(host_ip)+1,  "%s", host_ip);
    snprintf(port, strlen(host_port)+1,  "%s", host_port);
    printf("%s:%s\n",ip,port);
  }
  char *ptr;
  unsigned short port_num = (unsigned short)strtol(port, &ptr, 10);
  struct sockaddr_in sa_in;
  bzero(&sa_in, sizeof(sa_in));
  sa_in.sin_family = AF_INET;
  sa_in.sin_port = htons(port_num);
  int res = inet_pton(AF_INET, ip, &sa_in.sin_addr);
  if(res < 0) {
    perror("pton failed!");
    return -1;
  }
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("sockfd:%d sizeof(fd_set):%lu\n", sockfd, sizeof(fd_set));
  if(sockfd < 0) {
    perror("socket create failed!");
    return -1;
  }
  socklen_t len = sizeof(sa_in);
  res = connect(sockfd, (sockaddr *)&sa_in, len);
  if(res < 0) {
    perror("connect failed!");
    return -1;
  }
  FILE *fp = fopen("cmake_install.cmake", "rb");
  if(fp) {
    str_cli(fp, sockfd);
  } else {
    perror("fopen error\n");
    exit(-1);
  }

  exit(0);
}
