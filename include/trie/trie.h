
#ifndef __TRIE_H__
#define __TRIE_H__

#include <CVector.h>
#include <util/util.h>

template <typename T>
struct TrieNode
{
	unsigned char value;
	CVector<TrieNode*> vec;
	T* object;
	TrieNode* parent;

	TrieNode* find(unsigned char search_value)
	{
		typename CVector<TrieNode*>::iterator it = vec.begin();

		while(it != vec.end())
		{
			if((*it)->value == search_value)
				return *it;

			it++;
		}

		return NULL;
	}

	TrieNode* add(unsigned char value)
	{
		TrieNode* newTrieNode = new TrieNode;
		newTrieNode->value = value;
		newTrieNode->parent = this;
		newTrieNode->object = NULL;

		vec.push_back(newTrieNode);

		return newTrieNode;
	}

	bool remove(unsigned char value)
	{
		typename CVector<TrieNode*>::iterator it = vec.begin();

		while(it != vec.end())
		{
			if((*it)->value == value)
			{
				vec.erase(it);
				return true;
			}

			it++;
		}

		return false;
	}

	void clear()
	{
		if(this->object)
			delete this->object;

		typename CVector<TrieNode*>::iterator it = vec.begin();

		while(it != vec.end())
		{
			TrieNode* node = *it;
			node->clear();
			delete node;
			it++;
		}

		vec.clear();
	}

	int n_childs()
	{
		return vec.size();
	}

	void display(unsigned char* str,int len)
	{
		int value = 0;
		int mul = 1;

		for(int i=0;i<len;i++)
		{
			value += str[i] * mul;
			mul *=10;
		}

		Util::WriteToConsole("Number %d",value);
	}

	void show(unsigned char* current,int n)
	{
		assert(n<=10);

		if( (vec.size() == 0) && n>0)
		{
			display(current,n);
			return;
		}

		typename CVector<TrieNode*>::iterator it = vec.begin();

		while(it != vec.end())
		{
			TrieNode* node = (*it);

			unsigned char* now = new unsigned char[10];
			memcpy(now,current,10);

			now[n] = node->value;

			node->show(now,n+1);
			
			it++;
		}
	}

	int count()
	{
		int i = 0;

		typename CVector<TrieNode*>::iterator it = vec.begin();

		while(it != vec.end())
		{
			TrieNode* node = (*it);
			
			if(node->n_childs() == 0)
				i += 1;
			else
				i += node->count();

			it++;
		}

		return i;
	}
};

template <typename T>
class Trie
{
	TrieNode<T> root;
	static const int cuts = 10;

	public :

		Trie()
		{
			root.object = NULL;
		}

		bool add(int value,T object)
		{
			TrieNode<T>* node = find_node(value);

			if(node != NULL)
				return false;

			TrieNode<T>* current = &root;

			for(int i=1;i<=cuts;i++)
			{
				unsigned char digit = value % 10;
				value /= 10;

				TrieNode<T>* node = current->find(digit);

				if(!node)
				{
					node = current->add(digit);
				}

				current = node;
			}

			current->object = new T;
			*current->object = object;

			return true;
		}

		T* find(int value)
		{
			TrieNode<T>* node = find_node(value);

			if(node == NULL)
				return NULL;
			else
				return node->object;
		}

		TrieNode<T>* find_node(int value)
		{
			TrieNode<T>* current = &root;

			for(int i=1;i<=cuts;i++)
			{
				unsigned char digit = value % 10;
				value /= 10;

				TrieNode<T>* node = current->find(digit);

				if(!node)
				{
					return NULL;
				}

				current = node;
			}

			return current;
		}

		bool remove(int value)
		{
			TrieNode<T>* node_to_remove = this->find_node(value);

			if(!node_to_remove)
				return false;

			delete node_to_remove->object;
		
			TrieNode<T>* current = node_to_remove;

			while(true)
			{
				if(current == &root)
					break;

				TrieNode<T>* parent = current->parent;

				parent->remove(current->value);

				delete current;

				if(parent->n_childs() == 0)
				{
					current = parent;
				}
				else
				{
					break;
				}
			}

			return true;
		}

		void clear()
		{
			this->root.clear();
		}

		int count()
		{
			return this->root.count();
		}

		void show()
		{
			unsigned char* begin = new unsigned char[10];
			memset(begin,0,10);

			this->root.show(begin,0);

			Util::WriteToConsole("\n");
		}
};

#endif