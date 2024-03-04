#ifndef _CHAIN_H_
#define _CHAIN_H_
#include<iostream>
#include<sstream>
#include"linearList.h"
using namespace std;
template<class T>
struct Node
{
	T element;
	Node<T>* next;
	Node() {}
	Node(const T& element) { this->element = element; }
	Node(const T& element, Node<T>* next) { this->element = element; this->next = next; }
};

template<class T>
class chain :public linearList<T> {
public:
	chain(int capacity);
	chain(const chain<T>& other_chain);
	~chain();
	bool empty() { return size == 0; }
	int getSize() const { return size; }
	T& get(int index)const;
	//对0-listSize范围内的修改
	void set(int index, T val);
	void erase(int index);
	// 插入新的元素
	void insert(int index, const T& element);
	void checkIndex(int index)const;
	class iterator
	{
		typedef ptrdiff_t   difference_type;
		typedef Node<T>   value_type;
		typedef Node<T>* pointer;
		typedef Node<T>& reference;
		typedef forward_iterator_tag iterator_category;
	public:
		iterator(Node<T>* pos = 0) { position = pos; }
		iterator& operator=(iterator right) { this->position = right.position; return *this; }
		iterator& operator++() { position = position->next; return *this; }
		iterator operator++(int) {
			iterator old = *this;
			position = position->next;
			return old;
		}
		iterator& operator--() { position = position->next; return *this; }
		iterator operator--(int) {
			iterator old = *this;
			position = position->next;
			return old;
		}
		T& operator*()const { return (*position).element; }
		T* operator->()const { return &(*position); }
		bool operator==(const iterator right)const { return position == right.position; }
		bool operator!=(const iterator right)const { return position != right.position; }

	protected:
		Node<T>* position;
	};
	iterator begin() { return iterator(first_node); }
	iterator end() { return iterator(nullptr); }
	void output(ostream& out)const;
	template<class D> friend ostream& operator<<(ostream& out, chain<D> list);

protected:
	Node<T>* first_node;
	int size;
};
template<class T>
ostream& operator<<(ostream& out, chain<T>list)
{
	list.output(out);
	return out;
}
template<class T>
void chain<T>::output(ostream& out)const
{
	for (int i = 0; i < size; i++)
	{
		out << get(i) << " ";
	}
}
template<class T>
T& chain<T>::get(int index)const
{
	checkIndex(index);
	Node<T>* new_node = first_node;
	for (int i = 0; i < index; i++)
	{
		new_node = new_node->next;
	}
	return (*new_node).element;
}
template<class T>
void chain<T>::set(int index, T val)
{
	checkIndex(index);
	Node<T>* new_node = first_node;
	for (int i = 0; i < index; i++)
	{
		new_node = new_node->next;
	}
	(*new_node).element = val;
}
template<class T>
chain<T>::chain(int capacity)
{
	first_node = NULL;
	size = 0;
}
template<class T>
chain<T>::chain(const chain<T>& other_chain)
{
	size = other_chain.size;
	if (size == 0)
	{
		first_node = nullptr;
		return;
	}
	Node<T>* old = other_chain.first_node;
	first_node = new Node<T>(old->element);
	old = old->next;
	Node<T>* new_node = first_node;
	while (old != nullptr)
	{
		new_node->next = new Node<T>(old->element);
		new_node = new_node->next;
		old = old->next;
	}
	new_node->next = nullptr;
}
template<class T>
chain<T>::~chain() {
	while (first_node != nullptr)
	{
		Node<T>* next = first_node->next;
		delete first_node;
		first_node = next;
	}
}
template<class T>
void chain<T>::insert(int index, const T& val)
{
	if (index<0 || index>size)
	{
		throw logic_error("clas chain fuc insert wrong index");
	}
	if (index == 0)
	{
		Node<T>* new_node = new Node<T>(val, first_node);
		first_node = new_node;
		size++;
		return;
	}

	Node<T>* ahead, * new_node;
	ahead = first_node;
	for (int i = 0; i < index - 1; i++)
	{
		ahead = ahead->next;
	}
	new_node = new Node<T>(val, ahead->next);
	ahead->next = new_node;
	size++;
}
template<class T>
void chain<T>::erase(int index) {
	checkIndex(index);
	if (index == 0)
	{
		Node<T>* old = first_node;
		first_node = first_node->next;
		delete old;
		return;
	}
	Node<T>* behind = first_node;
	Node<T>* ahead = first_node;
	for (int i = 0; i < index; i++)
	{
		behind = ahead;
		ahead = ahead->next;
	}
	behind->next = ahead->next;
	size--;
}
template<class T>
void chain<T>::checkIndex(int index) const {
	if (index < 0 || index >= size) {
		stringstream s;
		s << "index = " << index << "size = " << getSize();
		cout << s.str() << endl;
		throw logic_error(s.str());
	}
}


#endif // !_CHAIN_H_

