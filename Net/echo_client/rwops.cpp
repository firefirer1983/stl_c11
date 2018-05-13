#ifndef _RWOPS_C_
#define _RWOPS_C_

#include "uni.h"
#include "rwops.h"
#include <cstdlib>
#include <syslog.h>
#include <signal.h>

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
        break; //eof
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

ssize_t _read(int fd, char *vptr, size_t size) {
again:
  ssize_t nread = read(fd, vptr, size);
  if(nread >= 0) { // EOF of read
    return nread;
  } else {
    if(errno == EINTR) {
      goto again;
    } else {
      return nread;
    }
  }
}

ssize_t _write(int fd, char *vptr, size_t size) {
  again:
  ssize_t nwrite = write(fd, vptr, size);
  if(nwrite >= 0) { // EOF of read
    return nwrite;
  } else {
    if(errno == EINTR) {
      goto again;
    } else {
      return nwrite;
    }
  }
}

int _accept(int listenfd, struct sockaddr *peer, socklen_t * len) {
again:
  int naccept = accept(listenfd, peer, len);
  if(naccept == -1 && errno == EINTR) {
    goto again;
  }
  return naccept;
}

int _bind(int fd, const struct sockaddr *__my_addr, socklen_t __addrlen) {
again:
  int res = bind(fd, __my_addr, __addrlen);
  if(res < 0 && errno == EINTR) {
    goto again;
  }
  return res;
}
int _connect (int fd, const struct sockaddr * __my_addr, socklen_t __addrlen) {
again:
  int res = connect(fd, __my_addr, __addrlen);
  if(res < 0 && errno == EINTR) {
    goto again;
  }
  return res;
}

int _listen (int fd, int __n) {
again:
  int res = listen(fd, __n);
  if(res < 0 && errno == EINTR) {
    goto again;
  }
  return res;
}

ssize_t _recv(int fd, void *__buff, size_t __len, int __flags) {
again:
  ssize_t res = recv(fd, __buff, __len, __flags);
  if(res < 0 && errno == EINTR) {
    goto again;
  }
  return res;
}

ssize_t _recvfrom (int fd, void *__buff, size_t __len, int __flags,
                  struct sockaddr *__from, socklen_t *__fromlen) {
again:
  ssize_t res = recvfrom(fd, __buff, __len, __flags, __from, __fromlen);
  if(res < 0 && errno == EINTR) {
    goto again;
  }
  return res;
}

ssize_t _recvmsg(int s, struct msghdr *msg, int flags){
again:
  ssize_t res = recvmsg(s,msg,flags);
  if(res < 0 && errno == EINTR) {
    goto again;
  }
  return res;
}
ssize_t _send (int fd, const void *__buff, size_t __len, int __flags) {
again:
  ssize_t res = send (fd, __buff, __len,__flags);
  if(res < 0 && errno == EINTR) {
    goto again;
  }
  return res;
}

ssize_t _sendmsg(int s, const struct msghdr *msg, int flags){
again:
  ssize_t res = sendmsg(s,msg,flags);
  if(res < 0 && errno == EINTR) {
    goto again;
  }
  return res;
}
ssize_t _sendto (int fd, const void * __buf, size_t __len, int __flags,
                const struct sockaddr *__to, socklen_t __tolen) {
again:
  ssize_t res = sendto(fd, __buf, __len, __flags,__to, __tolen);
  if(res < 0 && errno == EINTR) {
    goto again;
  }
  return res;
}
int _shutdown (int fd, int __flag) {
again:
  int res = shutdown(fd, __flag);
  if(res < 0 && errno == EINTR) {
    goto again;
  }
  return res;
}
int _socket (int __family, int __type, int __protocol) {
again:
  int res = socket (__family, __type, __protocol);
  if(res < 0 && errno == EINTR) {
    goto again;
  }
  return res;
}
const unsigned FD_MAX = 64;
extern int daemon_proc;
int daemonize(const char *name, int facility) {
  pid_t pid;
  if((pid = fork()) < 0) {
    printf("fork failed!\n");
    return -1;
  } else if(pid > 0) {
    exit(0);
  }
  if(setsid() < 0) {
    printf("setsid failed!\n");
    exit(0);
  }
  signal(SIGHUP, SIG_IGN);
  if((pid = fork()) < 0) {
    printf("fork again failed!\n");
    exit(0);
  } else if(pid > 0) {
    exit(0);
  }
  /* change work directory to "/" */
  chdir("/");
  for(unsigned f=0;f<FD_MAX;f++) {
    close(f);
  }
  /* redirect stdin, stdout, stderr to /dev/null */
  open("/dev/null", O_RDONLY); // stdin = open("/dev/null",O_RDONLY) ==> (stdin=0)
  open("/dev/null", O_RDWR);   // stdout = open("/dev/null, O_RDWR) ==> (stdout=1）
  open("/dev/null", O_RDWR);   // stderr= open("/dev/null, O_RDWR) ==> (stdout=2)

  openlog(name, LOG_PID, facility);
  return 0;
}
#endif