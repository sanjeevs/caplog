#include "log_utils.h"

#include <cassert>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


// keep trying if x gets interrupted by a signal
#define HANDLE_EINTR(x)                                       \
  ({                                                          \
    decltype(x) ret;                                          \
    int try_cnt = 0;                                          \
    do {                                                      \
      ret = (x);                                              \
    } while (ret == -1 && errno == EINTR && try_cnt++ < 100); \
    ret;                                                      \
  })

int write_file(const char* path, const void* data, size_t size, int flags, 
              mode_t mode) {
  int fd = HANDLE_EINTR(open(path, flags, mode));
  if (fd == -1) {
    return -1;
  }
  ssize_t n = HANDLE_EINTR(write(fd, data, size));
  close(fd);
  return (n >= 0 && (size_t)n == size) ? 0 : -1;
}

FILE* safe_fopen(const char* filename, const char* mode) {
  FILE* fp = NULL;
  do {
    fp = fopen(filename, mode);
  } while ((nullptr == fp) && (errno == EINTR));
  return fp;
}

size_t safe_fwrite(const void* ptr, size_t size, size_t count, FILE* stream) {
  size_t written = 0;
  do {
    size_t ret = ::fwrite((void*)((char *)ptr + written * size), size, count - written, stream);
    if (ret == 0 && errno != EINTR) break;
    written += ret;
  } while (written != count);
  return written;
}

int safe_fflush(FILE *stream) {
  int ret = EOF;
  do {
    ret = fflush(stream);
  } while ((EOF == ret) && (errno == EINTR));
  return ret;
}

