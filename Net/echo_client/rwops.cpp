#ifndef _RWOPS_C_
#define _RWOPS_C_

#include "uni.h"
#include "rwops.h"

ssize_t readbf(int fd, char *vptr) {

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
      if(c == '\0') {
        break;
      }
    } else {
      break;
    }
    vptr ++;
  }
  *vptr = 0;
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

#endif