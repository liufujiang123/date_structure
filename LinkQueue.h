/*******************************************************************************
* FileName:         SeqQueue.h
* Author:           your_name
* Student Number:   3022244xxx
* Date:             2023/03/17 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #4
*                   需要完成的SeqQeuue.h，
*******************************************************************************/

#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "MyQueue.h"

class LinkQueue : public MyQueue {
private:
    int len;
    struct node {
        int dataa;
        node* next=nullptr;
    };
    node* head;
    node* tail;

public:
    LinkQueue();
    virtual ~LinkQueue();
    void push_back(int data);
    void pop_front();
    int front() const;
};

#endif
