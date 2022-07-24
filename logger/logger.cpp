#include "logger.h"
#include <stdio.h>
#include "log_utils.h"

#include <cassert>
#include <pthread.h>
#include <memory>


// Log file basic api
class LogFile {
public:
  LogFile(const char* path) {
      file = safe_fopen(path, "wb");
      assert(file != nullptr);
  }

  ~LogFile() {
      safe_fflush(file);
      int err = fclose(file);
      assert(err == 0);     
  }

  inline void write(void* data, size_t size) {
      int written = safe_fwrite(data, 1, size, file);
      assert(written == size);
  }

private:
  FILE *file = nullptr;

};

// Make logging thread safe
typedef struct LogHandle {
  pthread_mutex_t lock;
  std::unique_ptr<LogFile> log;
} LogHandle;

// Assume that there cannot be more than 16 open log files.
static LogHandle* handles[16];
static int num_handles;

int log_init(const char* path) {
  assert(num_handles < 16);
  LogHandle* h = new LogHandle;
  handles[num_handles] = h;
  num_handles += 1;
  h->log = std::make_unique<LogFile>(path);
  pthread_mutex_init(&h->lock, NULL);
  return (num_handles -1);
}

void log_msg(int handle, uint8_t* data, size_t data_size) {
  LogHandle* h = handles[handle];
  pthread_mutex_lock(&h->lock);
  h->log->write(data, data_size);
  pthread_mutex_unlock(&h->lock);
}
