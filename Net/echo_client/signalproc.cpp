#ifndef _SIGNAL_PROC_C_
#define _SIGNAL_PROC_C_

#include "signalproc.h"

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
  struct sigaction sa;
  struct sigaction sa_prev;
  sigemptyset(&(sa.sa_mask));
  sa.sa_sigaction = act;
  int res = sigaction(sig, &sa, &sa_prev);
  if(res < 0) {
    return (SIG_ERR);
  }
  return (sa_prev.sa_handler);
}


#endif //_SIGNAL_PROC_C_
