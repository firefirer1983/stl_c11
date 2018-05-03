#ifndef _SIGNAL_PROC_C_
#define _SIGNAL_PROC_C_

#include "signalproc.h"
#include <stdio.h>

SignalProc Signal(int sig, SignalProc func)
{
  struct sigaction sa;
  struct sigaction sa_prev;
  sigemptyset(&(sa.sa_mask));
  sa.sa_handler = func;
  int res = sigaction(sig, &sa, &sa_prev);
  if(res < 0) {
    return (SIG_ERR);
  }
  return (sa_prev.sa_handler);
}

SignalProc Signal(int sig, SignalAct act)
{
  printf("sig act\n");
  struct sigaction sa;
  struct sigaction sa_prev;
  sigemptyset(&(sa.sa_mask));
  sa.sa_sigaction = act;
  sa.sa_flags = SA_SIGINFO; // this is important , because set this to use void (*sa_sigaction)(int, siginfo_t *, void *)
                            // otherwise use void (*sa_handler)(int) by default
                            // use sa_sigaction will reinstall signal handle automatically, sa_handle wouldn't
  int res = sigaction(sig, &sa, &sa_prev);
  if(res < 0) {
    return (SIG_ERR);
  }
  return (sa_prev.sa_handler);
}


#endif //_SIGNAL_PROC_C_
