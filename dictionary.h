#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_
#include"chain.h"
template<class K,class E >
class dictionary {
public:
	virtual bool empty()const = 0;
	virtual int size()const = 0;
	virtual pair<K,E>* find(const K& key)const = 0;
	virtual void insert(const pair<const K, E>& p) = 0;
	virtual void erase(const K& key) = 0;

};

template<class K,class E>
struct skip_node
{
	typedef pair<const K, E> pair_type;
	pair_type element;
	skip_node<K,E>** next;
	skip_node(const pair_type& the_pair, int size) :element(the_pair) { next = new skip_node<K,E> * [size]; }
};
template<class K,class E>
class skip_list {
public:	
	skip_list(K largest_key,int max_size,  float prob);
	pair<const K,E>* find(const K& key);
	void insert(pair<const K, E>the_pair);
	skip_node< K, E>* search(const K& key);
	int level()const;
	void erase(const K& key);
private:
	float cutoff;//由概率产生的边界值
	int levels;
	int max_level;
	int size;
	K max_key;
	skip_node<K,E>* head_node;
	skip_node<K,E>* tail_node;
	skip_node<K,E>** last;
};
template<class K,class E>
void skip_list<K, E>::erase(const K& key)
{
	if (key >= max_key)return;
	skip_node<K, E>* the_node = search(key);
	if (the_node->element.first != key)return;
	for (int i = 0; i <= levels && last[i]->next[i] == the_node; i++)
	{
		last[i]->next[i] = the_node->next[i];
	}
	while (levels > 0 && head_node->next[levels] == tail_node)levels--;
	delete the_node;
	size--;
}
template<class K,class E>
int skip_list<K, E>::level()const 
{
	int the_level = 0;
	while (rand() <= cutoff)the_level++;
	return the_level <= max_level ? the_level : max_level;
}
template<class K,class E>
skip_node< K, E>* skip_list<K, E>::search(const K& key)
{
	if (key >= max_key)return nullptr;
	skip_node<K, E>* current_node = head_node;
	for (int i = levels; i >= 0; i--)
	{
		while (current_node->next[i]->element.first < key)
		{
			current_node = current_node->next[i];
		}
		last[i] = current_node;
	}
	if (current_node->next[0]->element.first == key)return current_node->next[0];

	return nullptr;
}
template<class K,class E>
void skip_list<K, E>::insert(pair<const K, E> the_pair)
{
	skip_node< K, E>* current_node = search(the_pair.first);
	if (current_node!=nullptr&&current_node->element.first == the_pair.first)
	{
		current_node->element.second = the_pair.second;
		return;
	}
	skip_node<K, E>* new_node = new skip_node<K, E>(the_pair, max_level);
	int the_level = level();
	if (the_level > levels)
	{
		the_level = ++levels;
		last[the_level] = head_node;
	}
	for (int i = 0; i <= the_level; i++)
	{
		new_node->next[i] = last[i]->next[i];
		last[i]->next[i] = new_node;
	}
	size++;
	return;

}
template<class K,class E>
pair<const K, E>* skip_list<K, E>::find(const K& key)
{
	if (key >= max_key)return nullptr;
	skip_node<K, E>* current_node = head_node;
	for (int i = levels; i >= 0; i--)
	{
		while (current_node->next[i]->element.first< key)
		{
			current_node = current_node->next[i];
		}
	}
	if (current_node->next[0]->element.first == key)return &(current_node->next[0]->element);
	return nullptr;
}
template<class K,class E>
skip_list<K,E>::skip_list( K largest_key,int max_size,  float prob)
{
	int max_level = (int)ceil(logf(max_size) / logf(1 / prob));
	cutoff = prob * RAND_MAX;
	size = 0;
	levels = 0;
	
	max_key = largest_key;
	pair<K, E> tail_pair;
	tail_pair.first = max_key;
	head_node = new skip_node<K, E>(tail_pair, max_level + 1);
	tail_node = new skip_node<K, E>(tail_pair, 0);
	
	last = new skip_node<K, E>* [max_level + 1];

	for (int i = 0; i <= max_level; i++)
	{
		head_node->next[i] = tail_node;
	}
}
//template<class K,class E>

#endif // !_DICTIONARY_H_
