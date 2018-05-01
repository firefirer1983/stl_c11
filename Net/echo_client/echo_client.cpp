#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/fcntl.h>

const int BUF_SIZE = 2048;

static ssize_t readbf(int fd, char *vptr) {
  static size_t readed;
  static char *ptr;
  static char read_buf[2048];

  if(readed <= 0) {
    again:
      if( (readed = read(fd, read_buf, sizeof(read_buf))) <= 0 ) {
        if(errno == EINTR) {
          goto again;
        } else {
          return -1;
        }
      }
    ptr = read_buf;
  }

  *vptr = *ptr++;
  readed--;
  return 1;
}

ssize_t readline(int fd, char *vptr, size_t linesize) {
  char c;

  size_t readed = 0;
  int n = 0;
  for( ; linesize; linesize-=n) {
    n = readbf(fd,&c);
    if(n == 0) {
      break;
    } else if(n == 1) {
      *vptr = c;
      readed ++;
      if(c == '\n') {
        break;
      }
    } else {
      break;
    }
    vptr ++;
  }
  *vptr = '\0';
  if(n > 0){
    return readed;
  } else {
    return n;
  }
}

int readn(int fd, char *vptr, size_t n) {
  char *ptr = vptr;
  size_t left = n;
  ssize_t readed = 0;
  while(left > 0) {
    if( (readed = read(fd, ptr, left)) < 0) {
      if(readed < 0) {
        if( errno == EINTR) {
          readed = 0;
        } else {
          return -1;
        }
      } else if(readed == 0) {
        break;
      }
    }
    left -= readed;
    ptr += readed;
  }
  return (n-left);
}

int writen(int fd, char *vptr, size_t n) {
  char *ptr = vptr;
  size_t left = n;
  ssize_t writed = 0;
  while(left > 0) {
    if( (writed = write(fd, ptr, left)) <= 0) {
      if(writed <= 0) {
        if( errno == EINTR) {
          writed = 0;
        } else {
          return -1;
        }
      }
    }
    left -= writed;
    ptr += writed;
  }
  return (n-left);
}

void str_cli(FILE *fp, int sockfd) {
  char send_line[BUF_SIZE], recv_line[BUF_SIZE];
  while(fgets(send_line, sizeof(send_line), fp) != nullptr) {
    writen(sockfd, send_line,  strlen(send_line));
    if(readline(sockfd, recv_line, sizeof(recv_line)) == 0) {
      perror("echo server terminated!");
    }
    fputs(recv_line, stdout);
  }
}

char ip[] = "255.255.255.255";
char port[] = "12345";
const char host_ip[] = "127.0.0.1";
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
  FILE *rdfp = fopen("message.txt", O_RDONLY);
  str_cli(rdfp, sockfd);
  fclose(rdfp);
  return 0;
}
