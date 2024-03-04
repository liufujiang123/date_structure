#ifndef _QUEUE_H_
#define _QUEUE_H_
template<class T>
class queue {
public:
	virtual bool empty()const = 0;
	virtual int get_size()const = 0;
	virtual T& front() = 0;
	virtual T& back() = 0;
	virtual void pop() = 0;
	virtual void push(const T& element) = 0;

};
template<class T>
class array_queue :public queue<T> {
public:
	array_queue(int length=10);
	bool empty()const { return front_ptr == back_ptr; }
	T& front();
	void pop();
	void push(const T& element);
	T& back();
	int get_size()const { return size; }

private:
	int size;
	int length;
	T* queue;
	int front_ptr;
	int back_ptr;
};
template<class T>
T& array_queue<T>::back()
{
	if (!empty()) { return queue[back_ptr]; }
	else {
		throw logic_error("empty queue");
	}
}
template<class T>
T& array_queue<T>::front() { 
	if (!empty()) { return queue[(front_ptr + 1) % length]; }
	else {
		throw logic_error("empty queue");
	}
}
template<class T>
void array_queue<T>::pop() { 
	if (!empty()) {
		front_ptr = (front_ptr + 1) % length; size--;
	}
	else{
		throw logic_error("empty queue");
	}
}
template<class T>
array_queue<T>::array_queue(int length) {
	size = 0;
	this->length = length;
	queue = new T[length];
	int front_ptr = 0;
	int back_ptr = 0;
}
template<class T>
void array_queue<T>::push(const T& element)
{
	if ((back_ptr + 1) % length == front_ptr) {
		T* new_queue =new T[2*length];
		int start = (front_ptr + 1) % length;
		if (start < 2)
		{
			copy(queue + start, queue + start + length - 1, new_queue);
		}
		else {
			copy(queue + start, queue + length, new_queue);
			copy(queue, queue + back_ptr+1, new_queue + length - start);
		}
		front_ptr = 2 * length - 1;
		back_ptr = length - 2;
		length *= 2;
		delete[]queue;
		queue = new_queue;
	}
	
	back_ptr = (back_ptr + 1) % length;
	queue[back_ptr] = element;
	
	
	size++;
}

#endif // !_QUEUE_H_

