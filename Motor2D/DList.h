#ifndef __DLIST_H__
#define __DLIST_H__

#include <assert.h>

#ifndef NULL
#define NULL 0
#endif

template <class TYPE>
void swap(TYPE &a, TYPE &b) {

	TYPE tmp;
	tmp = a;
	a = b;
	b = tmp;
}

template <class TYPE>
struct doubleNode {
	TYPE data;
	doubleNode<TYPE>* next;
	doubleNode<TYPE>* previous;

	inline doubleNode(const TYPE &_data)
	{
		data = _data;
		next = previous = NULL;
	}

	~doubleNode()
	{ }
};

template <class TYPE>
class DList {

private:

	doubleNode<TYPE>* start;
	doubleNode<TYPE>* end;
	unsigned int size;

public:

	inline DList()
	{
		start = end = NULL;
		size = 0;
	}

	~DList()
	{
		clear();
	}

	/* If this method won't be constant, we will be able to do something like:
	(b += c).add("hola");

	If this method is const, so:
	b += c;    --> Here is the important step, the object returned.
	b.add("hola");
	*/
	 
	const DList<TYPE>& operator+= (DList &list_to_add)
	{
		doubleNode<TYPE> *item_to_add = list_to_add.getFirst();

		while (item_to_add != NULL)
		{
			add(item_to_add->data);
			item_to_add = item_to_add->next;
		}

		return (*this);		
	}

	unsigned int count() const
	{
		return size;
	}

	unsigned int add(const TYPE &new_data)
	{
		doubleNode<TYPE> *new_node;
		new_node = new doubleNode<TYPE>(new_data);
		new_node->data = new_data;

		if (start != NULL)
		{
			new_node->previous = end;
			end->next = new_node;
			end = new_node;
		}
		else
		{
			start = end = new_node;
		}
			
		return (++size);
	
	}

	doubleNode<TYPE>* getNodeAtPos(unsigned int _pos) const
	{
		// Node 1 is zero, node 2 is one, etc.
		if (start != NULL && _pos < count())
		{
			unsigned int pos_counter = 0;
			doubleNode<TYPE>* tmp = start;
			
			while (pos_counter != _pos)
			{
				tmp = tmp->next;
				pos_counter++;
			}
			return tmp;
		}
		return NULL;
	}

	/**
	* Find by index (by Ricard)
	*/
	bool at(unsigned int index, TYPE &new_data) const
	{
		bool ret = false;
		unsigned int i = 0;
		doubleNode<TYPE>*   searching_node = start;

		for (unsigned int i = 0; i < index - 1 && searching_node != NULL; ++i)
			searching_node = searching_node->next;

		if (searching_node != NULL)
		{
			ret = true;
			new_data = searching_node->data;
		}

		return ret;
	}

	bool del(doubleNode<TYPE> *node_to_delete)
	{
		if (start != NULL && node_to_delete != NULL)
		{
			if (node_to_delete->previous != NULL)
			{
				node_to_delete->previous->next = node_to_delete->next;
				if (node_to_delete->next != NULL)
					node_to_delete->next->previous = node_to_delete->previous;
				else
					end = node_to_delete->previous;
			}
			else
			{
				if (node_to_delete->next != NULL)
				{
					start = node_to_delete->next;
					node_to_delete->next->previous = NULL;
				}
				else
					start = end = NULL;
			}

			delete node_to_delete;
			--size;
			return true;
		}
		return false;
	}

	void clear()
	{
		doubleNode<TYPE> *item = start;
		doubleNode<TYPE> *item_next;

		while (item != NULL)
		{
			item_next = item->next;
			delete item;
			item = item_next;			
		}

		start = end = NULL;
		size = 0;
	
	}

	bool isOnList(const doubleNode<TYPE> *node_to_check) const
	{
		if (start != NULL && node_to_check != NULL)
		{
			doubleNode<TYPE> *item = start;
			while (item != NULL)
			{
				if (item->data == node_to_check->data)
					return true;
				item = item->next;
			}
		}
		return false;
	}

	bool insert(const DList &inserted_list, unsigned int position)
	{
		if (position < count())
		{
			DList<TYPE> tmp_list;
			for (unsigned int i = position; i < count(); i++)
			{
				tmp_list.add(getNodeAtPos(i)->data);
				del(getNodeAtPos(i));
			}

			for (unsigned int i = 0; i < inserted_list.count(); i++)
				add(inserted_list.getNodeAtPos(i)->data);

			for (unsigned int i = 0; i < tmp_list.count(); i++)
				add(tmp_list.getNodeAtPos(i)->data);

			return true;
		}
		return false;
	}

	unsigned int sort_copy()
	{
		unsigned int counter = 0;
		for (unsigned int i = 0; i < size - 1; i++)
		{
			for (unsigned int j = i + 1; j < size; j++)
			{
				counter++;
				if (getNodeAtPos(i)->data > getNodeAtPos(j)->data)
					swap(getNodeAtPos(i)->data, getNodeAtPos(j)->data);
			}
		}
		return counter;
	}

	unsigned int sort_reference()
	{
		unsigned int counter = 0;
		doubleNode<TYPE> *first_node;
		doubleNode<TYPE> *second_node;

		for (unsigned int i = 0; i < size - 1; i++)
		{
			first_node = getNodeAtPos(i);
			for (unsigned int j = i + 1; j < size; j++)
			{
				second_node = getNodeAtPos(j);
				counter++;
				if (first_node->data > second_node->data)
				{
					// millor fer un SWAP propi per la classe DList.

					if (first_node->previous = NULL)
					{
						first_node->previous = second_node->previous;
						second_node->previous = NULL;
					}
					else
						swap(first_node->previous->next, second_node->previous->next);

					if (second_node->next = NULL)
					{
						second_node->next = first_node->next;
						first_node->next = NULL;
					}
					else
						swap(first_node->next->previous, second_node->next->previous);

					swap(first_node->next, second_node->next);
					swap(first_node->previous, second_node->previous);

				}
			}
		}
		return counter;
	}


	TYPE& operator[] (unsigned int index)
	{
		assert(index < size);
		return getNodeAtPos(index)->data;
	}

	const TYPE& operator[] (unsigned int index) const
	{
		assert(index < size);
		return getNodeAtPos(index)->data;
	}

	doubleNode<TYPE>* getFirst() const
	{
		return start;
	}

	doubleNode<TYPE>* getLast() const
	{
		return end;
	}

	void info() const
	{
		if (start != NULL) {
			doubleNode<TYPE>* tmp = start;
			unsigned int node_num = 1;
			while (tmp != NULL)
			{
				printf("%s %d: %s %d | %s %p | %s %p | %s %p\n",
					    "Number", node_num,
						"Data", tmp->data,
						"Node", tmp,
						"Next", tmp->next,
						"Previous", tmp->previous);
				tmp = tmp->next;
				node_num++;
			}	
			printf("%s\n", "--------------------------------");
		}
		else
			printf("%s\n", "Empty Double Linked List");
	}

};

#endif // !__DLIST_H__
