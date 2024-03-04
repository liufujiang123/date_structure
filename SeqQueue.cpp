#include "SeqQueue.h"



SeqQueue::SeqQueue() {
	len = 0;
	head = new int[MAX_ELEMENTS];

}
SeqQueue::~SeqQueue() {
	delete[]head;
}
void SeqQueue::pop_front() {
	for (int i = 1; i <= len - 1; i++)
	{
		head[i - 1] = head[i];
	}
	len--;
}
void SeqQueue::push_back(int data) {
	if (len == MAX_ELEMENTS)
	{
		head = new int[2 * len];
	}
	head[len] = data;
	len++;
}
int SeqQueue::front() const {
	if (len > 0)return head[0];
	else return -1;
}