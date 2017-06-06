// casQueue.h
//
// Implementation of lock free queue using CAS operations 
// for simple multi-threading use cases like:
// 1. multiple worker to process incoming messages
// 2. async processing using a thread pool
// 3. simple tcp server deal with async requests

#ifndef __CASQUEUE_H__
#define __CASQUEUE_H__

#include <string>
using namespace std;

namespace bfd {

struct LinkNode {
	string data;
	LinkNode* next;
};
typedef struct LinkNode LinkNode;

class CASQueue {
	public:
		CASQueue();
		~CASQueue();

		int push(const string &msg);
		string pop(); // non-blocking

		bool empty();

	private:
		LinkNode *head_;
		LinkNode *tail_;
		bool empty_;
		unsigned int length_;
};

}//namespage bfd
#endif
