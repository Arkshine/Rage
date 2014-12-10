
#ifndef __STACK_H__
#define __STACK_H__

template <typename T>
struct StackNode
{
	StackNode* parent;
	T object;
};

template <typename T>
class Stack
{
	StackNode<T>* current;

	public:

	Stack() : current(NULL)
	{
		
	}

	bool pop(T& object)
	{
		if(current == NULL)
			return false;

		object = current->object;
		StackNode<T>* remove = current;
		current = current->parent;

		delete remove;

		return true;
	}

	bool pop_discard()
	{
		if(current == NULL)
			return false;

		StackNode<T>* remove = current;
		current = current->parent;

		delete remove;

		return true;
	}

	bool get(T& object)
	{
		if(current == NULL)
			return false;

		object = current->object;
		return true;
	}

	void push(T object)
	{
		StackNode<T>* node = new StackNode<T>;

		node->object = object;
		node->parent = current;

		current = node;
	}
};

#endif