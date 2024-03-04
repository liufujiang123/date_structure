#ifndef _LINEARLIST_
#define _LINEARLIST_
#include<iostream>
using namespace std;
template<class T>
class linearList {
public:
	virtual ~linearList() {};
	virtual T& get(int index) const =0;
	virtual bool empty() = 0;
	virtual void set(int index,T val) = 0;
	virtual int getSize() const = 0;
	virtual void erase(int index) = 0;
	virtual void insert(int index, const T& element) = 0;
	//virtual void output(ostream& out)const = 0;

};

#endif // 

