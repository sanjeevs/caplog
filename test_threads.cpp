#include "logger.h"
#include <cstring>
#include <pthread.h>
#include <iostream>
#include <chrono>
#include <thread>


//
// Multi threaded logging.
//

int log_handle;
#define NUM_THREADS 4

void *log_msg(void* ptr)  {
    char* msg = (char*) ptr;
    for(auto i = 0; i < 5; i++) {
        log_msg(log_handle, (uint8_t*) msg, strlen(msg));
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 3));
    }
    pthread_exit(0);
}

int main() {
    log_handle = log_init("test2.bin");

    char* msgs[NUM_THREADS];
    for(auto i = 0;i < NUM_THREADS; i++) {
        msgs[i] = (char*) malloc(256);
        if(i % 2) {
            strcpy(msgs[i], "Hello World");
        }
        else {
            strcpy(msgs[i], "Bye World");
        }
    }

    
    std::cout << "Creating " << NUM_THREADS << " threads." << std::endl;
    pthread_t thread_ids[NUM_THREADS];
    for(auto i = 0; i < NUM_THREADS; i++) {
        if(pthread_create(&thread_ids[i], NULL, log_msg, msgs[i])) {
            std::cout << "Creating thread failed" << std::endl;
            return -1;
        }
    }

    std::cout << "Waiting for all threads to finish" << std::endl;
    for(auto i = 0; i < NUM_THREADS; i++) {
        pthread_join(thread_ids[i], NULL);
    }



    return 0;
}