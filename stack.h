#ifndef _STACK_H_
#define _STACK_H_
#include"arrayList.h"
template<class T>
class stack {
public:
	virtual ~stack() {};
	virtual bool empty() = 0;
	virtual int get_size()const = 0;
	virtual void push(const T& element) = 0;
	virtual void pop() = 0;
	virtual T& top() = 0;
};
template<class T>
class array_stack:public stack<T>,private arrayList<T> {
public:
	array_stack(int capacity = 10) :arrayList<T>(capacity) {}
	bool empty() { return arrayList<T>::empty(); }
	int get_size()const { return arrayList<T>::getSize(); }
	T& top() {
		if (arrayList<T>::empty()) throw logic_error("empty stack"); 		
		return arrayList<T>::get(arrayList<T>::getSize() - 1);
		
	}
	void push(const T& element)
	{
		arrayList<T>::insert(arrayList<T>::getSize(), element);
	}
	void pop()
	{
		if (arrayList<T>::empty())throw logic_error("empty stack");
		arrayList<T>::erase(arrayList<T>::getSize() - 1);
	}
	//friend  ostream& operator<<(ostream& out, array_stack<T> sta);
	
};
//template<class T>
//ostream& operator<<(ostream& out, array_stack<T> sta)
//{
//	for (int i = 0; i < sta.get_size(); i++)
//	{
//		out <<sta.arrayList<T>::get(i) << " ";
//	}
//	return out;
//}
#endif // !_STACK_H_



