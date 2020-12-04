#ifndef __KITESHIELD_SYSCALL_DEFINES_H
#define __KITESHIELD_SYSCALL_DEFINES_H

#include <stdint.h>

/* mmap syscall constants */
#define MAP_SHARED 0x01
#define MAP_PRIVATE 0x02
#define MAP_ANONYMOUS 0x20
#define MAP_FIXED 0x10

#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define PROT_EXEC 0x4
#define PROT_NONE 0x0

#define MAP_FAILED ((void *) -1)

/* open syscall constants */
#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02

/* lseek syscall constants */
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

/* ptrace syscall constants */
enum __ptrace_request {
  PTRACE_TRACEME = 0,
  PTRACE_PEEKTEXT = 1,
  PTRACE_PEEKDATA = 2,
  PTRACE_PEEKUSER = 3,
  PTRACE_POKETEXT = 4,
  PTRACE_POKEDATA = 5,
  PTRACE_POKEUSER = 6,
  PTRACE_CONT = 7,
  PTRACE_KILL = 8,
  PTRACE_SINGLESTEP = 9,
  PTRACE_GETREGS = 12,
  PTRACE_SETREGS = 13,
  PTRACE_GETFPREGS = 14,
  PTRACE_SETFPREGS = 15,
  PTRACE_ATTACH = 16,
  PTRACE_DETACH = 17,
  PTRACE_GETFPXREGS = 18,
  PTRACE_SETFPXREGS = 19,
  PTRACE_SYSCALL = 24,
  PTRACE_GET_THREAD_AREA = 25,
  PTRACE_SET_THREAD_AREA = 26,
  PTRACE_ARCH_PRCTL = 30,
  PTRACE_SYSEMU = 31,
  PTRACE_SYSEMU_SINGLESTEP = 32,
  PTRACE_SINGLEBLOCK = 33,
  PTRACE_SETOPTIONS = 0x4200,
  PTRACE_GETEVENTMSG = 0x4201,
  PTRACE_GETSIGINFO = 0x4202,
  PTRACE_SETSIGINFO = 0x4203,
  PTRACE_GETREGSET = 0x4204,
  PTRACE_SETREGSET = 0x4205,
  PTRACE_SEIZE = 0x4206,
  PTRACE_INTERRUPT = 0x4207,
  PTRACE_LISTEN = 0x4208,
  PTRACE_PEEKSIGINFO = 0x4209,
  PTRACE_GETSIGMASK = 0x420a,
  PTRACE_SETSIGMASK = 0x420b,
  PTRACE_SECCOMP_GET_FILTER = 0x420c,
  PTRACE_SECCOMP_GET_METADATA = 0x420c
};

enum __ptrace_setoptions {
  PTRACE_O_TRACESYSGOOD = 0x00000001,
  PTRACE_O_TRACEFORK = 0x00000002,
  PTRACE_O_TRACEVFORK = 0x00000004,
  PTRACE_O_TRACECLONE = 0x00000008,
  PTRACE_O_TRACEEXEC = 0x00000010,
  PTRACE_O_TRACEVFORKDONE = 0x00000020,
  PTRACE_O_TRACEEXIT = 0x00000040,
  PTRACE_O_TRACESECCOMP = 0x00000080,
  PTRACE_O_EXITKILL = 0x00100000,
  PTRACE_O_SUSPEND_SECCOMP = 0x00200000,
  PTRACE_O_MASK  = 0x003000ff
};

enum __ptrace_eventcodes {
  PTRACE_EVENT_FORK = 1,
  PTRACE_EVENT_VFORK = 2,
  PTRACE_EVENT_CLONE = 3,
  PTRACE_EVENT_EXEC = 4,
  PTRACE_EVENT_VFORK_DONE = 5,
  PTRACE_EVENT_EXIT = 6,
  PTRACE_EVENT_SECCOMP  = 7,
  PTRACE_EVENT_STOP = 128
};

struct __ptrace_peeksiginfo_args {
  uint64_t off;
  uint32_t flags;
  int32_t nr;
};

enum __ptrace_peeksiginfo_flags {
  PTRACE_PEEKSIGINFO_SHARED = (1 << 0)
};

struct __ptrace_seccomp_metadata {
  uint64_t filter_off;
  uint64_t flags;
};

/* wait syscall constants */
#define WEXITSTATUS(status) (((status) & 0xff00) >> 8)
#define WTERMSIG(status) ((status) & 0x7f)
#define WSTOPSIG(status) WEXITSTATUS(status)
#define WIFEXITED(status) (WTERMSIG(status) == 0)
#define WIFSIGNALED(status) \
  (((signed char) (((status) & 0x7f) + 1) >> 1) > 0)
#define WIFSTOPPED(status) (((status) & 0xff) == 0x7f)
#ifdef WCONTINUED
# define WIFCONTINUED(status) ((status) == W_CONTINUED)
#endif

#endif /* __KITESHIELD_SYSCALL_DEFINES_H */

