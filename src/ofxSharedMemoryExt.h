#pragma once

//Rady-to-use shared memory sender and receiver with auto connection.
//NOTE: Currently it wait for connection, but later doesn't reconnect


#include "ofMain.h"

#include "ofxSharedMemory.h"

struct ofxSharedMemoryExt {
	//for example, memory_key = "myApp_mask"
	void setup_as_sender(string memory_key, int memory_size, float reconnect_time_sec = 1);
	void setup_as_receiver(string memory_key, int memory_size, float reconnect_time_sec = 1);

	void close();

	void update();	//call 'update' for auto reconnection
	void send(vector<unsigned char> &data);

	//use for "faster" receiving, without copying
	const unsigned char *get_data();
	//receive with copying - more thread safe
	bool receive(vector<unsigned char> &data);

	bool is_connected();

protected:
	bool inited_ = false;

	void setup(bool is_server, string memory_key, int memory_size, float reconnect_time_sec = 1);
	bool is_server_ = false;

	string memory_key_;

	ofxSharedMemory<unsigned char*> memory_file_;

	bool is_connected_;

	int memory_size_;


	float reconnect_time_sec = 1;

	float time_;	//last reconnect time

};

