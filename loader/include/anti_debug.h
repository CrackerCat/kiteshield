#ifndef __KITESHIELD_ANTI_DEBUG_H
#define __KITESHIELD_ANTI_DEBUG_H

#include "loader/include/types.h"
#include "loader/include/syscalls.h"
#include "loader/include/signal.h"
#include "loader/include/debug.h"

#define TRACED_MSG "We're being traced, exiting (-DNO_ANTIDEBUG to suppress)"

static int strncmp(const char *s1, const char *s2, size_t n)
{
  for (int i = 0; i < n; i++) {
    if (s1[i] != s2[i]) {
      return 1;
    }
  }

  return 0;
}

static const char *nextline(const char *curr_line)
{
  const char *ptr = curr_line;
  while (*ptr != '\0') {
    if (*ptr == '\n') return ptr + 1;
    ptr++;
  }

  return NULL; /* EOF */
}

/* Always inline this function so that a reverse engineer doesn't have to
 * simply neuter a single function in the compiled code to defeat calls to it
 * everywhere. */
static inline int __attribute__((always_inline)) check_traced()
{
#ifdef NO_ANTIDEBUG
  return 0;
#endif

  int fd =  sys_open("/proc/self/status", O_RDONLY, 0);
  DIE_IF_FMT(fd < 0, "could not open /proc/self/status, error %d", fd);

  char buf[4096]; /* Should be enough to hold any /proc/<pid>/status */
  int ret = sys_read(fd, buf, sizeof(buf) - 1);
  DIE_IF_FMT(ret < 0, "read failed with error %d", ret);
  buf[ret] = '\0';

  const char *line = buf;
  do {
    if (strncmp(line, "TracerPid:", 10) != 0) continue;

    /* Strip spaces between : and the pid */
    const char *curr = line + 10;
    while (*curr != '\0') {
      if (*curr != ' ' && *curr != '\t') break;
      curr++;
    }

    if (curr[0] == '0' && curr[1] == '\n') return 0;
    else return 1;
  } while ((line = nextline(line)) != NULL);

  DEBUG(
      "Could not find TracerPid in /proc/self/status, assuming we're traced");
  return 1;
}

/* Always inline antidebug_signal_check() for the same reasons as
 * check_traced() above. */
extern int sigtrap_counter;
static inline int __attribute__((always_inline)) antidebug_signal_check()
{
#ifdef NO_ANTIDEBUG
  return 0;
#endif

  int oldval = sigtrap_counter;
  asm volatile ("int3");

  return sigtrap_counter != oldval + 1;
}

void signal_antidebug_init();
void antidebug_set_nondumpable();

#endif /* __KITESHIELD_ANTI_DEBUG_H */
