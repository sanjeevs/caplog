#pragma once

#include <cstdint>
#include <cstddef>
//
// Stores messages in a log file.
//

// Call the init once with the path to the log file.
// Returns id that can be used in subsequent access
int log_init(const char* path);

// Write log message
void log_msg(int id, uint8_t* data, size_t data_size);
