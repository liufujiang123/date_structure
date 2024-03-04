#ifndef _CIRCULAR_CHAIN_H_
#define _CIRCULAR_CHAIN_H_
#include"chain.h"
template<class T>
class circular_chain :public linearList<T> {
public:
	//circular_chain(int capacity);
	//circular_chain(const chcircular_chainain<T>& other_chain);
	~circular_chain();
	bool empty() { return size == 0; }
	int getSize() const { return size; }
	T& get(int index)const;
	int index_of(T element)const;
	//对0-listSize范围内的修改
	void set(int index, T val);
	void erase(int index);
	// 插入新的元素
	void insert(int index, const T& element);
	void checkIndex(int index)const;

protected:
	int size;
	Node<T>* head_node;
};
template<class T>
T& circular_chain<T>::get(int index)const
{
	checkIndex(index);
	Node<T>* new_node = head_node;
	for (int i = 0; i < index+1; i++)
	{
		new_node = new_node->next;
	}
	return (*new_node).element;
}
template<class T>
void circular_chain<T>::checkIndex(int index) const {
	if (index < 0 || index >= size) {
		stringstream s;
		s << "index = " << index << "size = " << getSize();
		cout << s.str() << endl;
		throw logic_error(s.str());
	}
}
template<class T>
void circular_chain<T>::set(int index, T val)
{
	checkIndex(index);
	Node<T>* new_node = head_node;
	for (int i = 0; i < index+1; i++)
	{
		new_node = new_node->next;
	}
	(*new_node).element = val;
}
template<class T>
circular_chain<T>::~circular_chain() {
	int i = 0;
	while (i<size+1)
	{
		Node<T>* next = head_node->next;
		delete head_node;
		head_node = next;
	}
}
template<class T>
int circular_chain<T>::index_of(T element)const 
{
	head_node->element = element;
	Node<T>* current_node = head_node->next;
	int index = 0;
	while (current_node->element != element)
	{
		current_node = current_node->next;
		index++;
	}
	if (current_node == head_node)
		return -1;
	else return index;
}
//第一次更改

#endif // !_CIRCULAR_CHAIN_H_

