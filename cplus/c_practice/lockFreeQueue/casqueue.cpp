#include "casqueue.h"

namespace bfd {

CASQueue::CASQueue(): head_(NULL), tail_(NULL), empty_(true), length_(0) {
	head_ = new LinkNode;
	head_->next = NULL;
	tail_ = head_;
}

CASQueue::~CASQueue() {
	LinkNode *p = head_;
	if (p) {
		LinkNode *q = p->next;
		delete p;
		p = q;
	}
}

int CASQueue::push(const string &msg) {
	LinkNode *q = new LinkNode;
	q->data = msg;
	q->next = NULL;

	LinkNode *p = tail_;
	LinkNode *oldp = p;
	do {
		while (p->next != NULL)
			p = p->next;
	} while( __sync_bool_compare_and_swap(&(p->next), NULL, q) != true);

	__sync_bool_compare_and_swap(&tail_, oldp, q);
	return 0;
}

string CASQueue::pop() {
	LinkNode *p;
	do {
		p = head_;
		if (p->next == NULL) {
			return "";
		}
	} while (__sync_bool_compare_and_swap(&head_, p, p->next) != true);
	return p->next->data;
}

bool CASQueue::empty() {
	return empty_;
}


}// namespace bfd
