#ifndef _SIGNAL_PROC_H_
#define _SIGNAL_PROC_H_

#include <signal.h>

#ifdef _SIGNAL_PROC_C_
#define SIGNAL_PROC_EXT
#else
#define SIGNAL_PROC_EXT extern
#endif

typedef void (*SignalAct)(int sig, siginfo_t *ifo, void *ptr);
typedef void (*SignalProc)(int sig);

SIGNAL_PROC_EXT SignalProc Signal(int sig, SignalProc func);
SIGNAL_PROC_EXT SignalProc Signal(int sig, SignalAct act);


#endif //_SIGNAL_PROC_H_
