
#ifndef _INCLUDE_MANAGER_H_
#define _INCLUDE_MANAGER_H_

#include <sm_trie_tpl.h>
#include <CVector.h>

template <typename T>
class Manager
{
	protected:

		KTrie<T> trie;
		KTrie<unsigned int> trieToID;
		CVector<T> vector;

	public:


		void add(T object)
		{
			vector.push_back(object);
		}

		bool add(char* label,T object)
		{
			if(trie.retrieve(label) != NULL)
			{
				return false;
			}

			char *label_ = new char[strlen(label)+1];
			strcpy(label_,label);

			trie.insert(label_,object);	
			trieToID.insert(label_,vector.size());

			this->add(object);

			return true;
		}

		T* get_by_label(char* label)
		{
			return trie.retrieve(label);
		}

		unsigned int get_id_of(char* label)
		{
			unsigned int* id_ptr = trieToID.retrieve(label);

			if(!id_ptr)
				return -1;
			else return *id_ptr;
		}

		T* get_by_id(unsigned int id)
		{
			if((id >= 0) && (id < vector.size()))
				return &vector.at(id);
			else
				return NULL;
		}

		CVector<T>& get_vector()
		{
			return this->vector;
		}

		Manager()
		{
		}
};

#endif