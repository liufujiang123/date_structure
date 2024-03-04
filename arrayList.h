#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H
#include<iostream>
#include"linearList.h"
#include<sstream>
using namespace std;

template<class T>
class arrayList :public linearList<T> {
public:
	arrayList(int size = 10);
	arrayList(const arrayList<T>&);
	~arrayList() {};

	bool empty() { return listSize == 0; }
	int getSize() const { return listSize; }
	int getLength()const { return arrayLength; }
	T& get(int index)const { return array[index]; };
	//对0-listSize范围内的修改
	void set(int index, T val);
	void erase(int index);
	// 插入新的元素
	void insert(int index, const T& element);
	//void output(ostream& out)const;
	void checkIndex(int index);
	T& operator[](int index) { return *(array + index); }
	template<class D>friend ostream& operator<<(ostream& out, const arrayList<D>& arr);
	bool operator==(arrayList<T>& arr);

	class iterator
	{
	public:
		iterator(T* pos = 0) { position = pos; }
		iterator& operator=(iterator right) { this->position = right.position; return *this; }
		iterator& operator++() { ++position; return *this; }
		iterator operator++(int) {
			iterator old = *this;
			++position;
			return old;
		}
		iterator& operator--() { --position; return *this; }
		iterator operator--(int) {
			iterator old = *this;
			--position;
			return old;
		}
		T& operator*()const { return *position; }
		T* operator->()const { return &*position; }
		bool operator==(const iterator right)const { return position == right.position; }
		bool operator!=(const iterator right)const { return position != right.position; }

	protected:
		T* position;
	};
	iterator begin() { return iterator(array); }
	iterator end() { return iterator(array + listSize); }


protected:
	int listSize;//实际大小
	int arrayLength;//容量
	T* array;
};
template<class T>
bool arrayList<T>::operator==(arrayList<T>& arr) {
	if (getSize() == arr.getSize())
	{
		arrayList<T>::iterator it1, it2;
		for (it1 = begin(), it2 = arr.begin(); *it1 == *it2 && it1 != end(); it1++, it2++);

		if (it1 == end())return true;
	}
	return false;
}

template<class T>
ostream& operator<<(ostream& out, const arrayList<T>& arr)
{
	copy(arr.array, arr.array + arr.getSize(), ostream_iterator<T>(out, " "));
	return out;
}

template<class T>
void changeLength(T* a, int oldLength, int newLength)
{
	if (newLength < 0)throw logic_error("new length must be >=0");
	T* temp = new T[newLength];
	int length = min(oldLength, newLength);
	copy(a, a + length, temp);
	a = temp;
	delete[] a;
}
template<class T>
void arrayList<T>::set(int index, T val)
{
	checkIndex(index);
	array[index] = val;
}

template<class T>
void arrayList<T>::erase(int index) {
	checkIndex(index);
	copy(array + index + 1, array + listSize, array + index);
	//不留痕迹
	array[--listSize].~T();
};
template<class T>
void arrayList<T>::insert(int index, const T& element) {
	if (index<0 || index>arrayLength)
	{
		throw logic_error("wrong index");
	}
	if (listSize == arrayLength)
	{
		changeLength(array, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}

	copy_backward(array + index, array + listSize, array + listSize + 1);

	array[index] = element;


	listSize++;
};
//template<class T>
//void arrayList<T>::output(ostream& out)const {
//	
//	copy(array, array + listSize, ostream_iterator<T>(cout, " "));
//};
template<class T>
void arrayList<T>::checkIndex(int index) {
	if (index < 0 || index >= getLength()) {
		stringstream s;
		s << "index = " << index << "size = " << getSize();
		cout << s.str() << endl;
		throw logic_error(s.str());
	}
}

template<class T>
arrayList<T>::arrayList(int size)
{
	try
	{
		if (size < 1)
			throw "size must be > 0";
		array = new T[size];
		listSize = 0;
		arrayLength = size;
	}
	catch (char* e)
	{
		cout << e << endl;
	}
}
template<class T>
arrayList<T>::arrayList(const arrayList<T>& arr)
{
	arrayLength = arr.arrayLength;
	listSize = arr.getSize();
	array = new T[arrayLength];
	copy(arr.array, arr.array + arr.getSize(), array);
}

#endif // !_ARRAY_LIST_H
