@0xcdc83ed35d2c8e31;

struct AudioPcmConfig {
    sampleSizeBits @0 :Int32;
    samplingRateHz @1 :Int32;
    numChannels @2 :Int32;
    bufSize @3 :Int32;
}

struct AudioSocketConfig {
    serverIP @0 :Text;
    udpPort @1 :Int32;
    audioBufSize @2 :Int32;
    socketStatus @3 :SocketStatus;
    
    enum SocketStatus {
        init @0;
        connected @1;
        failed @2;
        exited @3;
    }
    
}

struct Message {
    logMonoTime @0 :UInt64;
    valid @1 :Bool = true;

    union {
        audioPcmConfig @2 :AudioPcmConfig;
        audioSocketConfig @3 :AudioSocketConfig;
    }
}
