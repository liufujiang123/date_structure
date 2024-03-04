#include "LinkQueue.h"

LinkQueue::LinkQueue() {
    len = 0;
    head = new node;
    tail = new node;
    tail = head;
}

LinkQueue::~LinkQueue() {
    node* p = head;
    for (int i = 0; i < len; i++)
    {
        p = p->next;
        delete p;
    }
    delete head;
}

void LinkQueue::push_back(int data) {
    node* add=new node;
    add->dataa = data;
    tail->next = add;
    tail = add;
    len++;
}

void LinkQueue::pop_front() {
    node* p = head->next;
    head->next = p->next;
    delete p;
    len--;
}


int LinkQueue::front() const {
    return head->next->dataa;
}