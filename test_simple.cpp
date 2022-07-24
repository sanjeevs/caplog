#include "logger.h"
#include <string>

int main() {
    int h = log_init("test1.bin");
    std::string msg = "Hello World";

    log_msg(h, (uint8_t*) msg.c_str(), msg.size());
    return 0;
}