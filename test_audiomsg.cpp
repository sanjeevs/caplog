#include "logger.h"
#include <string>
#include "audiolog.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize.h>
#include <iostream>


//
// Uses capnproto to log the audio message.
//

int main() {
    int log_handle = log_init("test3.bin");
  
    ::capnp::MallocMessageBuilder message;
    Message::Builder msg = message.initRoot<Message>();
    msg.setLogMonoTime(100);
    msg.setValid(1);

    AudioPcmConfig::Builder pcm_cfg = msg.initAudioPcmConfig();
    pcm_cfg.setSampleSizeBits(32);
    pcm_cfg.setNumChannels(1);
  

    const auto m = capnp::messageToFlatArray(message);
    const auto c = m.asChars();
   
    log_msg(log_handle, (uint8_t*) c.begin(), c.size());
    return 0;
}