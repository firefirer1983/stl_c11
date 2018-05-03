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

#endif //_RWOPS_H_
