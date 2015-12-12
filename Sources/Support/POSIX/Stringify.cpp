//
// Copyright (c) 2014, Facebook, Inc.
// All rights reserved.
//
// This source code is licensed under the University of Illinois/NCSA Open
// Source License found in the LICENSE file in the root directory of this
// source tree. An additional grant of patent rights can be found in the
// PATENTS file in the same directory.
//

#include "DebugServer2/Support/Stringify.h"
#include "DebugServer2/Utils/Log.h"

#include <errno.h>
#include <signal.h>
#include <sys/ptrace.h>

namespace ds2 {
namespace Support {
namespace POSIX {

#define DO_STRINGIFY(VALUE)                                                    \
  case VALUE:                                                                  \
    return #VALUE;

#define DO_DEFAULT(MESSAGE, VALUE)                                             \
  default:                                                                     \
    if (dieOnFail)                                                             \
      DS2BUG(MESSAGE ": %#x", VALUE);                                          \
    else                                                                       \
      return nullptr;

char const *Stringify::Signal(int signal, bool dieOnFail) {
  switch (signal) {
    DO_STRINGIFY(SIGHUP)
    DO_STRINGIFY(SIGINT)
    DO_STRINGIFY(SIGQUIT)
    DO_STRINGIFY(SIGILL)
    DO_STRINGIFY(SIGTRAP)
    DO_STRINGIFY(SIGABRT)
    DO_STRINGIFY(SIGBUS)
    DO_STRINGIFY(SIGFPE)
    DO_STRINGIFY(SIGKILL)
    DO_STRINGIFY(SIGUSR1)
    DO_STRINGIFY(SIGSEGV)
    DO_STRINGIFY(SIGUSR2)
    DO_STRINGIFY(SIGPIPE)
    DO_STRINGIFY(SIGALRM)
    DO_STRINGIFY(SIGTERM)
#if defined(OS_LINUX)
    DO_STRINGIFY(SIGSTKFLT)
#endif
    DO_STRINGIFY(SIGCHLD)
    DO_STRINGIFY(SIGCONT)
    DO_STRINGIFY(SIGSTOP)
    DO_STRINGIFY(SIGTSTP)
    DO_STRINGIFY(SIGTTIN)
    DO_STRINGIFY(SIGTTOU)
    DO_STRINGIFY(SIGURG)
    DO_STRINGIFY(SIGXCPU)
    DO_STRINGIFY(SIGXFSZ)
    DO_STRINGIFY(SIGVTALRM)
    DO_STRINGIFY(SIGPROF)
    DO_STRINGIFY(SIGWINCH)
    DO_STRINGIFY(SIGIO)
#if defined(OS_LINUX)
    DO_STRINGIFY(SIGPWR)
#endif
    DO_STRINGIFY(SIGSYS)
    DO_DEFAULT("unknown signal", signal);
  }
}

char const *Stringify::SignalCode(int signal, int code, bool dieOnFail) {
  switch (signal) {
  case SIGILL:
    switch (code) {
      DO_STRINGIFY(ILL_ILLOPC)
      DO_STRINGIFY(ILL_ILLOPN)
      DO_STRINGIFY(ILL_ILLADR)
      DO_STRINGIFY(ILL_ILLTRP)
      DO_STRINGIFY(ILL_PRVOPC)
      DO_STRINGIFY(ILL_PRVREG)
      DO_STRINGIFY(ILL_COPROC)
      DO_STRINGIFY(ILL_BADSTK)
      DO_DEFAULT("unknown code", code);
    };

  case SIGBUS:
    switch (code) {
      DO_STRINGIFY(BUS_ADRALN)
      DO_STRINGIFY(BUS_ADRERR)
      DO_STRINGIFY(BUS_OBJERR)
      DO_DEFAULT("unknown code", code);
    };

  case SIGSEGV:
    switch (code) {
      DO_STRINGIFY(SEGV_MAPERR)
      DO_STRINGIFY(SEGV_ACCERR)
      DO_DEFAULT("unknown code", code);
    };

    DO_DEFAULT("unknown signal", signal);
  }
}

char const *Stringify::Errno(int error, bool dieOnFail) {
  switch (error) {
    DO_STRINGIFY(EPERM)
    DO_STRINGIFY(ENOENT)
    DO_STRINGIFY(ESRCH)
    DO_STRINGIFY(EINTR)
    DO_STRINGIFY(EIO)
    DO_STRINGIFY(ENXIO)
    DO_STRINGIFY(E2BIG)
    DO_STRINGIFY(ENOEXEC)
    DO_STRINGIFY(EBADF)
    DO_STRINGIFY(ECHILD)
    DO_STRINGIFY(EAGAIN)
    DO_STRINGIFY(ENOMEM)
    DO_STRINGIFY(EACCES)
    DO_STRINGIFY(EFAULT)
    DO_STRINGIFY(ENOTBLK)
    DO_STRINGIFY(EBUSY)
    DO_STRINGIFY(EEXIST)
    DO_STRINGIFY(EXDEV)
    DO_STRINGIFY(ENODEV)
    DO_STRINGIFY(ENOTDIR)
    DO_STRINGIFY(EISDIR)
    DO_STRINGIFY(EINVAL)
    DO_STRINGIFY(ENFILE)
    DO_STRINGIFY(EMFILE)
    DO_STRINGIFY(ENOTTY)
    DO_STRINGIFY(ETXTBSY)
    DO_STRINGIFY(EFBIG)
    DO_STRINGIFY(ENOSPC)
    DO_STRINGIFY(ESPIPE)
    DO_STRINGIFY(EROFS)
    DO_STRINGIFY(EMLINK)
    DO_STRINGIFY(EPIPE)
    DO_STRINGIFY(EDOM)
    DO_STRINGIFY(ERANGE)
    DO_STRINGIFY(EDEADLK)
    DO_STRINGIFY(ENAMETOOLONG)
    DO_STRINGIFY(ENOLCK)
    DO_STRINGIFY(ENOSYS)
    DO_STRINGIFY(ENOTEMPTY)
    DO_STRINGIFY(ELOOP)
    DO_STRINGIFY(ENOMSG)
    DO_STRINGIFY(EIDRM)
#if defined(OS_LINUX)
    DO_STRINGIFY(ECHRNG)
    DO_STRINGIFY(EL2NSYNC)
    DO_STRINGIFY(EL3HLT)
    DO_STRINGIFY(EL3RST)
    DO_STRINGIFY(ELNRNG)
    DO_STRINGIFY(EUNATCH)
    DO_STRINGIFY(ENOCSI)
    DO_STRINGIFY(EL2HLT)
    DO_STRINGIFY(EBADE)
    DO_STRINGIFY(EBADR)
    DO_STRINGIFY(EXFULL)
    DO_STRINGIFY(ENOANO)
    DO_STRINGIFY(EBADRQC)
    DO_STRINGIFY(EBADSLT)
    DO_STRINGIFY(EBFONT)
    DO_STRINGIFY(ENOSTR)
    DO_STRINGIFY(ENODATA)
    DO_STRINGIFY(ETIME)
    DO_STRINGIFY(ENOSR)
    DO_STRINGIFY(ENONET)
    DO_STRINGIFY(ENOPKG)
#endif
    DO_STRINGIFY(EREMOTE)
    DO_STRINGIFY(ENOLINK)
#if defined(OS_LINUX)
    DO_STRINGIFY(EADV)
    DO_STRINGIFY(ESRMNT)
    DO_STRINGIFY(ECOMM)
#endif
    DO_STRINGIFY(EPROTO)
    DO_STRINGIFY(EMULTIHOP)
#if defined(OS_LINUX)
    DO_STRINGIFY(EDOTDOT)
#endif
    DO_STRINGIFY(EBADMSG)
    DO_STRINGIFY(EOVERFLOW)
#if defined(OS_LINUX)
    DO_STRINGIFY(ENOTUNIQ)
    DO_STRINGIFY(EBADFD)
    DO_STRINGIFY(EREMCHG)
    DO_STRINGIFY(ELIBACC)
    DO_STRINGIFY(ELIBBAD)
    DO_STRINGIFY(ELIBSCN)
    DO_STRINGIFY(ELIBMAX)
    DO_STRINGIFY(ELIBEXEC)
#endif
    DO_STRINGIFY(EILSEQ)
#if defined(OS_LINUX)
    DO_STRINGIFY(ERESTART)
    DO_STRINGIFY(ESTRPIPE)
#endif
    DO_STRINGIFY(EUSERS)
    DO_STRINGIFY(ENOTSOCK)
    DO_STRINGIFY(EDESTADDRREQ)
    DO_STRINGIFY(EMSGSIZE)
    DO_STRINGIFY(EPROTOTYPE)
    DO_STRINGIFY(ENOPROTOOPT)
    DO_STRINGIFY(EPROTONOSUPPORT)
    DO_STRINGIFY(ESOCKTNOSUPPORT)
    DO_STRINGIFY(EOPNOTSUPP)
    DO_STRINGIFY(EPFNOSUPPORT)
    DO_STRINGIFY(EAFNOSUPPORT)
    DO_STRINGIFY(EADDRINUSE)
    DO_STRINGIFY(EADDRNOTAVAIL)
    DO_STRINGIFY(ENETDOWN)
    DO_STRINGIFY(ENETUNREACH)
    DO_STRINGIFY(ENETRESET)
    DO_STRINGIFY(ECONNABORTED)
    DO_STRINGIFY(ECONNRESET)
    DO_STRINGIFY(ENOBUFS)
    DO_STRINGIFY(EISCONN)
    DO_STRINGIFY(ENOTCONN)
    DO_STRINGIFY(ESHUTDOWN)
    DO_STRINGIFY(ETOOMANYREFS)
    DO_STRINGIFY(ETIMEDOUT)
    DO_STRINGIFY(ECONNREFUSED)
    DO_STRINGIFY(EHOSTDOWN)
    DO_STRINGIFY(EHOSTUNREACH)
    DO_STRINGIFY(EALREADY)
    DO_STRINGIFY(EINPROGRESS)
    DO_STRINGIFY(ESTALE)
#if defined(OS_LINUX)
    DO_STRINGIFY(EUCLEAN)
    DO_STRINGIFY(ENOTNAM)
    DO_STRINGIFY(ENAVAIL)
    DO_STRINGIFY(EISNAM)
    DO_STRINGIFY(EREMOTEIO)
#endif
    DO_STRINGIFY(EDQUOT)
#if defined(OS_LINUX)
    DO_STRINGIFY(ENOMEDIUM)
    DO_STRINGIFY(EMEDIUMTYPE)
#endif
    DO_STRINGIFY(ECANCELED)
#if defined(OS_LINUX)
    DO_STRINGIFY(ENOKEY)
    DO_STRINGIFY(EKEYEXPIRED)
    DO_STRINGIFY(EKEYREVOKED)
    DO_STRINGIFY(EKEYREJECTED)
#endif
    DO_STRINGIFY(EOWNERDEAD)
    DO_STRINGIFY(ENOTRECOVERABLE)
#if defined(OS_LINUX)
    DO_STRINGIFY(ERFKILL)
    DO_STRINGIFY(EHWPOISON)
#endif
    DO_DEFAULT("unknown error", error);
  }
}

char const *Stringify::Ptrace(int code, bool dieOnFail) {
  switch (code) {
#if defined(OS_LINUX)
    DO_STRINGIFY(PTRACE_ATTACH)
    DO_STRINGIFY(PTRACE_CONT)
    DO_STRINGIFY(PTRACE_DETACH)
    DO_STRINGIFY(PTRACE_GETEVENTMSG)
#if defined(PTRACE_GETHBPREGS)
    DO_STRINGIFY(PTRACE_GETHBPREGS)
#endif
#if defined(PTRACE_GETREGS)
    DO_STRINGIFY(PTRACE_GETREGS)
#endif
    DO_STRINGIFY(PTRACE_GETREGSET)
    DO_STRINGIFY(PTRACE_GETSIGINFO)
    DO_STRINGIFY(PTRACE_INTERRUPT)
    DO_STRINGIFY(PTRACE_KILL)
    DO_STRINGIFY(PTRACE_LISTEN)
    DO_STRINGIFY(PTRACE_PEEKDATA)
    DO_STRINGIFY(PTRACE_PEEKTEXT)
    DO_STRINGIFY(PTRACE_PEEKUSER)
    DO_STRINGIFY(PTRACE_POKEDATA)
    DO_STRINGIFY(PTRACE_POKETEXT)
    DO_STRINGIFY(PTRACE_POKEUSER)
    DO_STRINGIFY(PTRACE_SEIZE)
#if defined(PTRACE_SETHBPREGS)
    DO_STRINGIFY(PTRACE_SETHBPREGS)
#endif
    DO_STRINGIFY(PTRACE_SETOPTIONS)
#if defined(PTRACE_SETREGS)
    DO_STRINGIFY(PTRACE_SETREGS)
#endif
    DO_STRINGIFY(PTRACE_SETREGSET)
    DO_STRINGIFY(PTRACE_SETSIGINFO)
    DO_STRINGIFY(PTRACE_SINGLESTEP)
    DO_STRINGIFY(PTRACE_SYSCALL)
    DO_STRINGIFY(PTRACE_TRACEME)
#endif
    DO_DEFAULT("unknown ptrace command", code);
  }
}
}
}
}
