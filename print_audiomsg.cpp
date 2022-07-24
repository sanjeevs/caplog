#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>  
#include <unistd.h>


#include "audiolog.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize.h>
#include <iostream>


//
// Uses capnproto to print the audio message.
//

int main() {
    const char* logfile = "test3.bin";

    int fd = open("test3.bin", O_RDONLY);
    ::capnp::StreamFdMessageReader message(fd);


    Message::Reader msg = message.getRoot<Message>();
    std::cout << "Valid=" << msg.getValid() << std::endl;
    std::cout << "Tstamp=" << msg.getLogMonoTime() << std::endl;
    if(msg.isAudioPcmConfig()) {
        std::cout << "SampleSize=" << msg.getAudioPcmConfig().getSampleSizeBits() << std::endl;
        std::cout << "NumChannels=" << msg.getAudioPcmConfig().getNumChannels() << std::endl;
    }
    close(fd);
    
    return 0;
}