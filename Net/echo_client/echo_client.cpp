#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include "uni.h"
#include "rwops.h"

const int BUF_SIZE = 2048;

void str_cli(FILE *fp, int sockfd) {
  char send_line[BUF_SIZE], recv_line[BUF_SIZE];
  while(fgets(send_line, sizeof(send_line), stdin) != nullptr) {
    perror("fgets");
    writen(sockfd, send_line,  strlen(send_line));
    ssize_t res = readline(sockfd, recv_line, sizeof(recv_line));
    printf("readline res:%ld\n",res);
    if(res <= 0) {
      perror("server terminated!\n");
    }
    fputs(recv_line, stdout);
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
  str_cli(nullptr, sockfd);
  exit(0);
}
