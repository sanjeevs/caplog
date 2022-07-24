# Overview
Uses [capnproto](https://capnproto.org/) for generting structured messages to a file. 

Basic logging is done by creating a logging library. This library allows binary messages to be saved to a log file and
is thread safe.

# Compiling On Linux
Uses CMake. 
```
mkdir out && cd out
cmake ..
cmake --build .
```

# Testing
The capnproto for an audio app is created in *audiolog.capnp*. The test code *test_audiomsg.cpp* generates the message to a log file *test3.bin*. This binary file can be dumped to stdout by *print_audiomsg.cpp*.

```
cd out
test_audiomsg
print_audiomsg
```
