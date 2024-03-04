/*******************************************************************************
* FileName:         MyQueue.h
* Author:           XXX
* Student Number:   30222XXXXX
* Date:             2023/03/16 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #4
*                   �����������ɵ� MyQueue.h �ļ����벻Ҫ�������������
*******************************************************************************/

#ifndef MYQUEUE_H
#define MYQUEUE_H

class MyQueue {
private:
public:
    MyQueue() {}
    virtual ~MyQueue() {}
    /**
    ������У���data���뵽��β��
    @name vritual void push_back(dpname&);
    @param arg1 ��Ҫ���������
    @return void
    */
    virtual void push_back(int data) = 0;


    /**
    ��ö���Ԫ�� ������п��򷵻� 0
    @name virtual dpname front() const;
    @return datatype ����ջ��Ԫ��
    */
    virtual int front() const = 0;


    /**
    ����Ԫ�س��ӡ��������Ϊ��ֱ��return��
    @name virtual void pop_front();
    @return void
    */
    virtual void pop_front() = 0;
};

#endif
