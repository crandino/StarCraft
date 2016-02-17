#ifndef __DYNARRAY_H__
#define __DYNARRAY_H__

#include <assert.h> 
#include "DList.h"

#define DYN_ARRAY_BLOCK_SIZE 16

template <class TYPE>
class DynArray {

private:

	TYPE *data;
	unsigned int allocated_memory;
	unsigned int num_elements;

	void reallocate(unsigned int new_mem_size)
	{
		allocated_memory = new_mem_size;
		TYPE *tmp = new TYPE[allocated_memory];

	/*	if (num_elements > allocated_memory)
			num_elements = allocated_memory;*/

		if (data != NULL)
		{
			for (unsigned int i = 0; i < num_elements; i++)
				tmp[i] = data[i];

			delete[] data;
		}
		data = tmp;
	}

public:

	// Constructors
	DynArray<TYPE>() : data(NULL), allocated_memory(0), num_elements(0)
	{
		reallocate(DYN_ARRAY_BLOCK_SIZE);
	}

	DynArray<TYPE>(unsigned int new_memory_size) : data(NULL), num_elements(0)
	{
		reallocate(new_memory_size);
	}

	DynArray<TYPE>(const DynArray &array) : data(NULL), allocated_memory(0), num_elements(0)
	{
		reallocate(array.allocated_memory);
		for (unsigned int i = 0; i < array.num_elements; i++)
			pushBack(array.data[i]);
	}

	~DynArray<TYPE>()
	{
		delete[] data;
	}

	const DynArray &operator+= (const DynArray &array_to_cat)
	{
		if (getNumElements() + array_to_cat.getNumElements() > allocated_memory)
			reallocate(getNumElements() + array_to_cat.getNumElements());

		for (unsigned int i = 0; i < array_to_cat.getNumElements(); i++)
			pushBack(array_to_cat[i]);

		return (*this);
	}

	void pushBack(TYPE new_value)
	{
		if (num_elements == allocated_memory)
			reallocate(allocated_memory + 1);

		data[num_elements] = new_value;
		num_elements++;
	}

	bool pop(TYPE &value)
	{
		// When the element is deleted, it is necessary to return a copy of that element.
		if (data != NULL && num_elements > 0)
		{
			value = data[--num_elements];
			return true;
		}
		return false;
	}

	bool insert(int new_value, unsigned int position)
	{
		if (position <= num_elements)
		{
			TYPE *tmp = new TYPE[allocated_memory];
			for (unsigned int i = 0; i < num_elements; i++)
			{
				tmp[i] = data[i];
			}

			if (num_elements == allocated_memory)
				reallocate(allocated_memory + 1);

			for (unsigned int i = 0; i < position; i++)
			{
				data[i] = tmp[i];
			}
			data[position] = new_value;
			for (unsigned int i = position; i < num_elements; i++)
			{
				data[i + 1] = tmp[i];
			}
			num_elements++;
			delete[] tmp;
			return true;
		}
		return false;
	}

	bool insert(const DynArray &array_inserted, unsigned int position)
	{
		if (position <= num_elements)
		{ 
			unsigned int num_elements_inserted = array_inserted.getNumElements();
			TYPE *tmp = new TYPE[num_elements + num_elements_inserted];

			if (num_elements + num_elements_inserted > allocated_memory)
				reallocate(num_elements + num_elements_inserted);
			
			for (unsigned int i = position; i < num_elements; i++)
				tmp[num_elements_inserted + i] = data[i];

			for (unsigned int i = 0; i < num_elements_inserted; i++)
			{
				data[position + i] = array_inserted[i];
				num_elements++;
			}

			for (unsigned int i = position + num_elements_inserted; i < num_elements; i++)
				data[i] = tmp[i];

			delete[] tmp;
			return true;
		}
		return false;
	}

	void flip()
	{
		unsigned int loops = num_elements / 2;
		for (unsigned int i = 0; i < loops; i++)
			swap(data[i], data[num_elements - (1 + i)]);
	}

	bool clear()
	{
		if (data != NULL)
		{
			num_elements = 0;
			return true;
		}
		return false;
	}

	unsigned int bubble_sort()
	{
		// BUBBLE SORT
		unsigned int changes;
		unsigned int counter = 0;
		do
		{
			changes = 0;
			for (unsigned int i = 0; i < num_elements - 1; i++)
			{
				counter++;
				if (data[i] > data[i + 1])
				{
					swap(data[i], data[i + 1]);
					changes++;
				}
			}
		} while (changes != 0);

		return counter;
	}

	unsigned int bubble_sort2()
	{
		// BUBBLE SORT OPTIMIZED
		// Number of iterations is reduced by 2. Each pair of values 
		// are compared only once.

		unsigned int counter = 0;

		for (unsigned int i = 0; i < num_elements - 1; i++)
		{
			for (unsigned int j = i + 1; j < num_elements; j++)
			{
				counter++;
				if (data[i] > data[j])
				{
					swap(data[i], data[j]);
				}
			}
		}

		return counter;
	}

	unsigned int sort_super_opt()
	{
		// BUBBLE SORT SUPER OPTIMIZED
		// Otra forma de optimizarlo es saber donde se produce el último swap. 
		// Hasta ese punto, todo estará ordenado a la derecha.

		// Otra forma es recorrer la array en dos sentidos a cada paso por la array.

		// Comsort?  Existeix un GAP que es la diferencia que hi ha entre dos números que
		// es comproven. Al inici és el 70% de l'array. Després va baixant.

		unsigned int counter = 0;
		unsigned int last = num_elements;

		for (unsigned int i = 0; i < last - 1; i++)
		{
			for (unsigned int j = i + 1; j < last; j++)
			{
				counter++;
				if (data[i] > data[j])
				{
					swap(data[i], data[j]);
					last = j;
				}
			}
		}

		return counter;
	}

	unsigned int combsort()
	{
		unsigned int counter = 0;

		float shrink_factor = 1.3f;
		unsigned int gap = (int)(num_elements / shrink_factor);
		bool swapped = true;

	    while (swapped == true)
		{			
			swapped = false;

			if (gap < 1)
				gap = 1;
			
			for (unsigned int i = 0; i + gap < num_elements; i++)
			{
				counter++;
				if (data[i] > data[i + gap])
				{
					swap(data[i], data[i + gap]);
					swapped = true;
				}
			}
			gap = (int)(gap / shrink_factor);
		}
		return counter;
	}

	unsigned int cocktailSort()
	{
		unsigned int counter = 0; 
		int begin = -1;
		int end = num_elements - 1;
		bool swapped = true;

		while (swapped)
		{
			swapped = false;
			begin++;
			for (int i = begin; i < end; i++)
			{
				counter++;
				if (data[i] > data[i + 1])
				{
					swap(data[i], data[i + 1]);
					swapped = true;
				}
			}

			end--;
			for (int i = end; i >= begin; i--)
			{
				counter++;
				if (data[i] > data[i + 1])
				{
					swap(data[i], data[i + 1]);
					swapped = true;
				}
			}
		}

		return counter;
	}

	// Auxiliar method useful to represent all the information.
	// It won't have its correspoding Unittest test. 
	void info() const
	{
		for (unsigned int i = 0; i < num_elements; i++)
		{
			printf("%s %d => %d\n", "Position", i, data[i]);
		}
		printf("%s: %d\n", "Number of elements", num_elements);
		printf("%s: %d\n\n", "Allocated memory", allocated_memory);
	}

	TYPE& operator[] (unsigned int index)
	{
		// For p[1] = 15;
		assert(index < num_elements);
		return data[index];
	}

	const TYPE& operator[] (unsigned int index) const
	{
		// For printf("%d", p[1]);
		assert(index < num_elements);
		return data[index];
	}

	unsigned int getMemory() const
	{
		return allocated_memory;
	}

	unsigned int getNumElements() const
	{
		return num_elements;
	}
};

#endif // !__DYNARRAY_H__
