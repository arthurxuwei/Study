// WorkThreadPool.h
//
// distrbute msg to multi process, use multi-process lib.
//
#ifndef __WORK_THREAD_POOL_H__
#define __WORK_THREAD_POOL_H__

#include <stdio.h>
#include <thread>
#include <queue>
#include <string>
#include <vector>
#include "casqueue.h"

using namespace std;
namespace bfd {

class WorkThreadPool {
	public:
		WorkThreadPool(int size);
		virtual ~WorkThreadPool();

		//need child class to impl
		virtual void Init() {};
		virtual void Finish() {};
		virtual void Handle(const string &msg)=0;

		//push msg into queue
		int SendMessage(const string &msg);

		int Start();
		int Stop();

	private:
		void Worker();

		int size_;
		CASQueue msg_queue_;
		vector<thread> thread_pool_;
};

}//namespace bfd
#endif
