ofxSharedMemory
===============

openFrameworks addon for working with shared memory.
* Provided examples demonstrate using ofxSharedMemory template class for sending and receiving data and images.

* 'ofxSharedMemoryExt' is a simple-to-use class for sending and receiving fixed-lenght data via shared memory.
it supports auto-connection.

* 'src_use_without_oF' folder contains ofxSharedMemory_universal.h file, allowing to work with shared memory in any C++ project,
without openFrameworks, for example, in Unreal Engine 4 C++ project.

Tested on Windows 10, oF 0.10.1.

---------------------------------------

Addon originally made by trentbrooks.
Below his credits.

Thanks to sloopi & KJ1 on the openframeworks forum for introducing me to 'memory mapped files' - http://forum.openframeworks.cc/index.php/topic,11730.msg55510.html#msg55510
 
KJ1 created an excellent Windows/VS specific example for kinect (https://github.com/Kj1/ofxKinectMemoryMapped) which shares kinect data from a C# app with an OF app. I made this because I needed a pure C++ example that worked on osx and windows, and not necessarily tied to kinect.

