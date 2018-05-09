//
// Created by 18377 on 2018/5/2.
//

#ifndef _RWOPS_H_
#define _RWOPS_H_

#ifdef _RWOPS_C_
#define _RWOPS_EXT_
#else
#define _RWOPS_EXT_ extern
#endif

_RWOPS_EXT_ ssize_t readbf(int fd, char *vptr);
_RWOPS_EXT_ ssize_t readline(int fd, char *vptr, size_t linesize);
_RWOPS_EXT_ int readn(int fd, char *vptr, size_t n);
_RWOPS_EXT_ int writen(int fd, char *vptr, size_t n);
_RWOPS_EXT_ ssize_t _read(int fd, char *vptr, size_t size);
_RWOPS_EXT_ ssize_t _write(int fd, char *vptr, size_t size);
_RWOPS_EXT_ int _accept(int listenfd, struct sockaddr *peer, socklen_t * len);
_RWOPS_EXT_ int _bind(int fd, const struct sockaddr *__my_addr, socklen_t __addrlen) ;
_RWOPS_EXT_ int _connect (int fd, const struct sockaddr * __my_addr, socklen_t __addrlen) ;
_RWOPS_EXT_ int _listen (int fd, int __n);
_RWOPS_EXT_ ssize_t _recv(int fd, void *__buff, size_t __len, int __flags) ;
_RWOPS_EXT_ ssize_t _recvfrom (int fd, void *__buff, size_t __len, int __flags,
                   struct sockaddr *__from, socklen_t *__fromlen) ;
_RWOPS_EXT_ ssize_t _recvmsg(int s, struct msghdr *msg, int flags);
_RWOPS_EXT_ ssize_t _send (int fd, const void *__buff, size_t __len, int __flags);
_RWOPS_EXT_ ssize_t _sendmsg(int s, const struct msghdr *msg, int flags);
_RWOPS_EXT_ ssize_t _sendto (int fd, const void * __buf, size_t __len, int __flags,
                 const struct sockaddr *__to, socklen_t __tolen);
_RWOPS_EXT_ int _shutdown (int fd, int __flag);
_RWOPS_EXT_ int _socket (int __family, int __type, int __protocol);
#endif //_RWOPS_H_
