#include "ofxSharedMemoryExt.h"

//---------------------------------------------------------------------------
void ofxSharedMemoryExt::setup_as_sender(string memory_key, int memory_size, float reconnect_time_sec) {
	setup(true, memory_key, memory_size, reconnect_time_sec);
}

//---------------------------------------------------------------------------
void ofxSharedMemoryExt::setup_as_receiver(string memory_key, int memory_size, float reconnect_time_sec) {
	setup(false, memory_key, memory_size, reconnect_time_sec);
}

//---------------------------------------------------------------------------
void ofxSharedMemoryExt::setup(bool is_server, string memory_key, int memory_size, float reconnect_time_sec) {
	if (inited_) {
		ofLogError("ofxSharedMemory error, already inited " + memory_key);
	}
	inited_ = true;

	is_server_ = is_server;
	memory_key_ = memory_key;
	memory_size_ = memory_size;

	if (is_server) cout << "ofxSharedMemory - Starting shared memory sender " << memory_key_ << " " << memory_size_ << " bytes" << endl;
	else cout << "ofxSharedMemory - Starting shared memory receiver " << memory_key_ << " " << memory_size_ << " bytes" << endl;
	memory_file_.setup(memory_key, memory_size, is_server);
	is_connected_ = memory_file_.connect();

	cout << "    connection: " << is_connected_ << endl;

}


//---------------------------------------------------------------------------
bool ofxSharedMemoryExt::is_connected() {
	return is_connected_;
}

//---------------------------------------------------------------------------
void ofxSharedMemoryExt::close() {
	inited_ = false;
	memory_file_.close();
}

//---------------------------------------------------------------------------
void ofxSharedMemoryExt::update() {
	if (inited_) {
		float time = ofGetElapsedTimef();
		if (!is_connected_) {
			if (time >= time_ + reconnect_time_sec) {
				is_connected_ = memory_file_.connect();
				time_ = time;
			}
		}
		else {
			time_ = time;
		}
	}
}

//---------------------------------------------------------------------------
void ofxSharedMemoryExt::send(vector<unsigned char> &data) {
	if (is_connected_) memory_file_.setData(&data[0]);
}

//---------------------------------------------------------------------------
void ofxSharedMemoryExt::receive(vector<unsigned char> &data) {
	if (is_connected_) {
		unsigned char* pdata = memory_file_.getData();
		data.resize(memory_size_);
		for (int i = 0; i < memory_size_; i++) {
			data[i] = pdata[i];
		}
	}

}

//---------------------------------------------------------------------------
