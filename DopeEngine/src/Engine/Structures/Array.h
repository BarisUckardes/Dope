#pragma once
#include <Engine/Core/Symbols.h>
#include <initializer_list>

namespace DopeEngine
{
	template <typename TValue>
	/// <summary>
	/// Basic Dope array implementation
	/// </summary>
	/// <typeparam name="T"></typeparam>
	class Array final
	{
	public:
		Array(unsigned int allocateMultiplier = 2);
		Array(const Array<TValue>& targetSource);
		Array(const TValue* data, unsigned int count);
		Array(std::initializer_list<TValue> initializerList);
		~Array();


		unsigned int get_capacity() const { return Capacity; }
		unsigned int get_cursor() const { return Cursor; }
		TValue* get_data() const { return m_Source; }
		unsigned int get_allocate_multiplier() const { return AllocateMultiplier; }
		bool has(const TValue& element) const;
		bool hasAll(const Array<TValue>& other);
		int find_index(const TValue& element) const;

		void reserve(unsigned int capacity);
		void reserve(unsigned int capacity, const TValue& defaultValue);
		void copy(const TValue* data, unsigned int count);
		void copy(const Array<TValue>& data, unsigned int start, unsigned int end);
		void move(TValue* targetSource, unsigned long numberOfElements);
		void add(const TValue& element);
		void add_range(const Array<TValue>& elements);
		void insert(unsigned int index, const TValue& element);
		void clear();
		void remove_index(unsigned int index);
		void remove(const TValue& element);
		void compact();
		void set_allocate_multiplier(unsigned int amount);

	public:
		TValue& operator[](unsigned int index) const;
		void operator=(const Array<TValue>& targetSource);
	private:
		void clear_memory();
	private:
		TValue* m_Source;
		unsigned long Capacity;
		unsigned int Cursor;
		unsigned int AllocateMultiplier;
	};

	template<typename TValue>
	static bool operator==(const Array<TValue>& a, const Array<TValue>& b);
	template<typename TValue>
	static bool operator!=(const Array<TValue>& a, const Array<TValue>& b);

	/*
	* Implementation
	*/
	template<typename TValue>
	Array<TValue>::Array(unsigned int allocateMultiplier)
	{
		Capacity = 0;
		Cursor = 0;
		m_Source = nullptr;
		AllocateMultiplier = allocateMultiplier;
	}

	template<typename TValue>
	Array<TValue>::Array(const Array<TValue>& targetSource)
	{
		/*
		* Get target source properties
		*/
		Cursor = targetSource.Cursor;
		Capacity = targetSource.Capacity;
		AllocateMultiplier = targetSource.AllocateMultiplier;

		/*
		* Allocate new source
		*/
		m_Source = new TValue[Capacity];

		for (unsigned int i = 0; i < Cursor; i++)
		{
			m_Source[i] = targetSource.m_Source[i];
		}
	}
	template<typename TValue>
	Array<TValue>::Array(const TValue* data, unsigned int count)
	{
		/*
		* Get properties
		*/
		Cursor = count;
		Capacity = count;

		/*
		* Allocate new source
		*/
		m_Source = new TValue[Capacity];

		for (unsigned int i = 0; i < Cursor; i++)
		{
			m_Source[i] = data[i];
		}
	}

	template<typename TValue>
	Array<TValue>::Array(std::initializer_list<TValue> initializerList)
	{

		/*
		* Allocate space
		*/
		m_Source = new TValue[initializerList.size()];
		Cursor = initializerList.size();
		Capacity = initializerList.size();
		/*
		* copy
		*/
		unsigned int index = 0;
		for (const TValue& value : initializerList)
		{
			m_Source[index] = value;
			index++;
		}
	}

	template<typename TValue>
	Array<TValue>::~Array()
	{
		clear_memory();
	}
	template<typename TValue>
	void Array<TValue>::clear_memory()
	{
		if (m_Source == nullptr)
			return;

		delete[] m_Source;
	}

	template<typename TValue>
	void Array<TValue>::reserve(unsigned int capacity)
	{
		/*
		* Delete former source
		*/
		clear_memory();

		/*
		* Allocate new source
		*/
		m_Source = new TValue[capacity];

		/*
		* Set new capacity
		*/
		Capacity = capacity;

		/*
		* Reset the cursor
		*/
		Cursor = 0;
	}
	template<typename TValue>
	inline void Array<TValue>::reserve(unsigned int capacity, const TValue& defaultValue)
	{
		/*
		* Delete format source
		*/
		clear_memory();

		/*
		* Allocate new source
		*/
		m_Source = new TValue[capacity];

		/*
		* Set new capacity
		*/
		Capacity = capacity;

		/*
		* Set cursor
		*/
		Cursor = capacity - 1;

		/*
		* Initialize default values
		*/
		for (unsigned int i = 0; i < Cursor; i++)
		{
			m_Source[i] = defaultValue;
		}
	}
	template<typename TValue>
	inline void Array<TValue>::copy(const TValue* data, unsigned int count)
	{
		/*
		* Get properties
		*/
		Cursor = count;
		Capacity = count;

		/*
		* Allocate new source
		*/
		m_Source = new TValue[Capacity];

		for (unsigned int i = 0; i < Cursor; i++)
		{
			m_Source[i] = data[i];
		}
	}
	template<typename TValue>
	inline void Array<TValue>::copy(const Array<TValue>& data, unsigned int start, unsigned int end)
	{
		/*
		* Get properties
		*/
		Cursor = end - start;
		Capacity = end - start;

		/*
		* Allocate new source
		*/
		m_Source = new TValue[Capacity];

		for (unsigned int i = 0; i < Cursor; i++)
		{
			m_Source[i] = data[i];
		}
	}
	template<typename TValue>
	inline void Array<TValue>::move(TValue* targetSource, unsigned long numberOfElements)
	{
		/*
		* Set properties
		*/
		Cursor = numberOfElements;
		Capacity = numberOfElements;
		m_Source = targetSource;

	}
	template<typename TValue>
	void Array<TValue>::add(const TValue& element)
	{
		/*
		* Validate array bounds
		*/
		if (Cursor >= Capacity) // time to extend the bound of this array
		{
			/*
			* Determine the next capacity
			*/
			unsigned int targetCapacity = ((Capacity == 0) ? 1 : Capacity) * AllocateMultiplier;

			/*
			* Allocate new source
			*/
			TValue* newSource = new TValue[targetCapacity];

			/*
			* Fill the new source with the old source data
			*/
			for (unsigned int i = 0; i < Cursor; i++)
			{
				newSource[i] = m_Source[i];
			}

			/*
			* Delete the old source
			*/
			clear_memory();

			/*
			* Set the new source
			*/
			m_Source = newSource;

			/*
			* Set Capacity
			*/
			Capacity = targetCapacity;
		}

		/*
		* Set the current cursor data
		*/
		m_Source[Cursor] = element;

		/*
		* Increment Cursor
		*/
		Cursor++;
	}

	template<typename TValue>
	void Array<TValue>::add_range(const Array<TValue>& array)
	{
		/*
		* Validate array bounds
		*/
		const unsigned int increaseInSize = array.GetCursor();
		const unsigned int targetSize = Cursor + increaseInSize + 1;

		/*
		* Validate if it needs new array
		*/
		if (targetSize >= Capacity)
		{
			/*
			* Allocate new source
			*/
			TValue* newSource = new TValue[targetSize];

			/*
			* First set old source
			*/
			for (unsigned int sourceIndex = 0; sourceIndex < Cursor; sourceIndex++)
			{
				newSource[sourceIndex] = m_Source[sourceIndex];
			}

			/*
			* Set target array
			*/
			for (unsigned int sourceIndex = 0; sourceIndex < increaseInSize; sourceIndex++)
			{
				newSource[Cursor + sourceIndex] = array.m_Source[sourceIndex];
			}

			/*
			* Clear old array
			*/
			clear_memory();

			/*
			* Set new source
			*/
			m_Source = newSource;

			/*
			* Set cursor
			*/
			Cursor = targetSize - 1;
			Capacity = Cursor;
		}
		else // just needs append
		{
			/*
			* Set target array
			*/
			unsigned int targetArrayIndex = 0;
			for (unsigned int sourceIndex = Cursor; sourceIndex < increaseInSize; sourceIndex++)
			{
				m_Source[sourceIndex] = array.m_Source[targetArrayIndex];
				targetArrayIndex++;
			}

			/*
			* Set cursor
			*/
			Cursor = targetSize - 1;
		}
	}

	template<typename TValue>
	void Array<TValue>::insert(unsigned int index, const TValue& element)
	{
		/*
		* Validate array bounds
		*/
		if (Cursor >= Capacity) // time to extend the bound of this array
		{
			/*
			* Determine the next capacity
			*/
			unsigned int targetCapacity = ((Capacity == 0) ? 1 : Capacity) * AllocateMultiplier;

			/*
			* Allocate new source
			*/
			TValue* newSource = new TValue[targetCapacity];

			/*
			* Fill the new source with the old source data
			*/
			for (unsigned int i = 0; i < Cursor; i++)
			{
				newSource[i] = m_Source[i];
			}

			/*
			* Delete the old source
			*/
			clear_memory();

			/*
			* Set the new source
			*/
			m_Source = newSource;

			/*
			* Set Capacity
			*/
			Capacity = targetCapacity;
		}

		/*
		* Shift elements
		*/
		for (unsigned int i = Cursor; i > index; i--)
		{
			m_Source[i] = m_Source[i - 1];
		}

		/*
		* Set item
		*/
		m_Source[index] = element;

		/*
		* Increment cursor
		*/
		Cursor++;
	}
	template<typename TValue>
	void Array<TValue>::set_allocate_multiplier(unsigned int multiplier)
	{
		/*
		* Set multiplier
		*/
		AllocateMultiplier = multiplier;
	}

	template<typename TValue>
	void Array<TValue>::clear()
	{
		/*
		* Delete source
		*/
		clear_memory();

		/*
		* Set variables
		*/
		m_Source = nullptr;
		Capacity = 0;
		Cursor = 0;
	}

	template<typename TValue>
	void Array<TValue>::remove_index(unsigned int index)
	{
		/*
		* Shift elements
		*/
		for (unsigned int i = index + 1; i < Cursor; i++)
		{
			m_Source[i - 1] = m_Source[i];
		}

		/*
		* Decrement cursor
		*/
		Cursor--;
	}

	template<typename TValue>
	void Array<TValue>::remove(const TValue& element)
	{
		/*
		* Find it
		*/
		int index = -1;
		for (unsigned int i = 0; i < Cursor; i++)
		{
			if (m_Source[i] == element)
			{
				index = i;
				break;
			}
		}

		/*
		* Validate index
		*/
		if (index == -1)
		{
			return;
		}

		/*
		* Shift elements
		*/
		for (unsigned int i = index + 1; i < Cursor; i++)
		{
			m_Source[i - 1] = m_Source[i];
		}

		/*
		* Decrement cursor
		*/
		Cursor--;
	}
	template<typename TValue>
	void Array<TValue>::compact()
	{
		/*
		* Create new source
		*/
		TValue* newSource = new TValue[Cursor];

		/*
		* copy the contens
		*/
		for (unsigned int i = 0; i < Cursor; i++)
		{
			newSource[i] = m_Source[i];
		}

		/*
		* Update variables
		*/
		Capacity = Cursor;
	}

	template<typename TValue>
	bool Array<TValue>::has(const TValue& element) const
	{
		/*
		* Iterator all elements
		*/
		for (unsigned int i = 0; i < Cursor; i++)
		{
			if (m_Source[i] == element) // has
				return true;
		}

		return false;
	}

	template<typename TValue>
	inline bool Array<TValue>::hasAll(const Array<TValue>& other)
	{
		/*
		* Iterate and check
		*/
		for (unsigned int i = 0; i < other.get_cursor(); i++)
		{
			if (!has(other[i]))
				return false;
		}

		return true;
	}

	template<typename TValue>
	int Array<TValue>::find_index(const TValue& element) const
	{
		int index = -1;

		/*
		* Iterator all elements
		*/
		for (unsigned int i = 0; i < Cursor; i++)
		{
			if (m_Source[i] == element)
			{
				index = i;
				break;
			}
		}

		return index;
	}
	template<typename TValue>
	TValue& Array<TValue>::operator[](unsigned int index) const
	{
		return m_Source[index];
	}
	template<typename TValue>
	void Array<TValue>::operator=(const Array<TValue>& targetSource)
	{
		/*
		* Get target source properties
		*/
		Cursor = targetSource.Cursor;
		Capacity = targetSource.Capacity;
		AllocateMultiplier = targetSource.AllocateMultiplier;

		/*
		* Allocate new source
		*/
		m_Source = new TValue[Capacity];

		for (unsigned int i = 0; i < Cursor; i++)
		{
			m_Source[i] = targetSource.m_Source[i];
		}
	}
	template<typename TValue>
	bool operator==(const Array<TValue>& a, const Array<TValue>& b)
	{
		/*
		* First check sizes
		*/
		if (a.get_cursor() != b.get_cursor())
			return false;

		/*
		* Iterate and check
		*/
		for (unsigned int i = 0; i < a.get_cursor(); i++)
		{
			if (a[i] != b[i])
				return false;
		}

		return true;
	}

	template<typename TValue>
	bool operator!=(const Array<TValue>& a, const Array<TValue>& b)
	{
		/*
		* First check sizes
		*/
		if (a.get_cursor() != b.get_cursor())
			return true;


		/*
		* Iterate and check
		*/
		for (unsigned int i = 0; i < a.get_cursor(); i++)
		{
			if (a[i] != b[i])
				return true;
		}

		return false;
	}

}