#include "workthreadpool.h"
#include <sstream>
#include <unistd.h>

namespace bfd {

WorkThreadPool::WorkThreadPool(int size){
	if (size <= 0) {
		size_ = 1;
	} else {
		size_ = size;
	}
}

WorkThreadPool::~WorkThreadPool() {

}

int WorkThreadPool::SendMessage(const string &msg) {
	msg_queue_.push(msg);
	return 0;
}

void WorkThreadPool::Worker() {
	unsigned int msg_count = 0;
	while (1) {
		string msg = msg_queue_.pop();
		if (msg.empty()) {
			printf("no msg got, sleep for 0.1 sec\n");
			usleep(100000);
			continue;
		}

		if (msg == "__exit__") {
			stringstream ss;
			ss << "exit worker: " << std::this_thread::get_id() << ", processed: " << msg_count << "..";
			printf("%s\n", ss.str().c_str());
			return;
		}

		Handle(msg);
		msg_count++;
		if (msg_count % 1000 == 0) {
			printf("every 1000 msg count\n");
		}
	}
}

int WorkThreadPool::Start() {
	for (int i=0; i< size_; i++) {
		thread_pool_.push_back(thread(&WorkThreadPool::Worker, this));
	}
	return 0;
}

int WorkThreadPool::Stop() {
	for (int i=0; i< size_; i++){
		SendMessage("__exit__");
	}
	for (int i=0; i< size_; i++){
		thread_pool_[i].join();
	}
	return 0;
}
	
}//namespace bfd
