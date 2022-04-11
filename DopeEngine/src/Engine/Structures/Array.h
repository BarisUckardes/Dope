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

		/// <summary>
		/// Allocates a fixed sized capacity
		/// <para>Deletes the former elements</para>
		/// </summary>
		/// <param name="capacity"></param>
		void reserve(unsigned int capacity);

		/// <summary>
		/// Returns a slice of this array(does not copy the contents)
		/// </summary>
		/// <typeparam name="TValue"></typeparam>
		void copy(const TValue* data, unsigned int count);

		/// <summary>
		/// Returns a slice of this array(does not copy the contents)
		/// </summary>
		/// <typeparam name="TValue"></typeparam>
		void copy(const Array<TValue>& data, unsigned int start, unsigned int end);

		/// <summary>
		/// moves the target source to this array
		/// </summary>
		/// <param name="targetSource"></param>
		/// <param name="numberOfElements"></param>
		void move(TValue* targetSource, unsigned long numberOfElements);

		/// <summary>
		/// adds a new element to the array
		/// </summary>
		/// <param name="element"></param>
		void add(const TValue& element);

		/// <summary>
		/// adds a new array to array
		/// </summary>
		/// <param name="elements"></param>
		void add_range(const Array<TValue>& elements);

		/// <summary>
		/// Insert the item
		/// </summary>
		/// <param name="index"></param>
		/// <param name="element"></param>
		void insert(unsigned int index, const TValue& element);

		/// <summary>
		/// Clears the whole array
		/// <para>Invokes the deconstructors if the TValue is a value type</para>
		/// </summary>
		void clear();

		/// <summary>
		/// Removes the target index
		/// </summary>
		/// <param name="index"></param>
		void remove_index(unsigned int index);

		/// <summary>
		/// Removes the target value
		/// </summary>
		/// <param name="element"></param>
		void remove(const TValue& element);

		/// <summary>
		/// Removes the spare space
		/// </summary>
		void compact();

		/// <summary>
		/// Sets the value which determines how large the next array size is when array size is insufficient
		/// </summary>
		/// <param name="amount"></param>
		void set_allocate_multiplier(unsigned int amount);

		/// <summary>
		/// Returns the value of max elements which this array can take at this instant
		/// </summary>
		/// <returns></returns>
		unsigned int get_capacity() const { return Capacity; }

		/// <summary>
		/// Returns the current cursor of this array thus returning the number of elements inside the array
		/// </summary>
		/// <returns></returns>
		unsigned int get_cursor() const { return Cursor; }

		/// <summary>
		/// Returns a pointer to the const source
		/// </summary>
		/// <returns></returns>
		TValue* get_data() const { return m_Source; }

		/// <summary>
		/// Returns the array allocation multiplier
		/// </summary>
		/// <returns></returns>
		unsigned int get_allocate_multiplier() const { return AllocateMultiplier; }

		/// <summary>
		/// Returns whether the element exists in this array
		/// </summary>
		/// <param name="element"></param>
		/// <returns></returns>
		bool has(const TValue& element) const;

		/// <summary>
		/// Returns the index of the element
		/// </summary>
		/// <param name="element"></param>
		/// <returns></returns>
		int find_index(const TValue& element) const;
	public:
		TValue& operator[](unsigned int index) const;
		void operator=(const Array<TValue>& targetSource);
	private:
		/// <summary>
		/// Clears the source memory
		/// <para>Invokes element deconstructors if the TValue is a value type</para>
		/// </summary>
		void clear_memory();
	private:
		TValue* m_Source;
		unsigned int Capacity;
		unsigned int Cursor;
		unsigned int AllocateMultiplier;
	};

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
}