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
	class Array
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
		void Reserve(unsigned int capacity);

		/// <summary>
		/// Returns a slice of this array(does not copy the contents)
		/// </summary>
		/// <typeparam name="TValue"></typeparam>
		void Copy(const TValue* data, unsigned int count);

		/// <summary>
		/// Returns a slice of this array(does not copy the contents)
		/// </summary>
		/// <typeparam name="TValue"></typeparam>
		void Copy(const Array<TValue>& data, unsigned int start, unsigned int end);

		/// <summary>
		/// Moves the target source to this array
		/// </summary>
		/// <param name="targetSource"></param>
		/// <param name="numberOfElements"></param>
		void Move(TValue* targetSource, unsigned long numberOfElements);

		/// <summary>
		/// Adds a new element to the array
		/// </summary>
		/// <param name="element"></param>
		void Add(const TValue& element);

		/// <summary>
		/// Adds a new array to array
		/// </summary>
		/// <param name="elements"></param>
		void AddRange(const Array<TValue>& elements);

		/// <summary>
		/// Insert the item
		/// </summary>
		/// <param name="index"></param>
		/// <param name="element"></param>
		void Insert(unsigned int index, const TValue& element);

		/// <summary>
		/// Clears the whole array
		/// <para>Invokes the deconstructors if the TValue is a value type</para>
		/// </summary>
		void Clear();

		/// <summary>
		/// Removes the target index
		/// </summary>
		/// <param name="index"></param>
		void RemoveIndex(unsigned int index);

		/// <summary>
		/// Removes the target value
		/// </summary>
		/// <param name="element"></param>
		void Remove(const TValue& element);

		/// <summary>
		/// Removes the spare space
		/// </summary>
		void Compact();

		/// <summary>
		/// Sets the value which determines how large the next array size is when array size is insufficient
		/// </summary>
		/// <param name="amount"></param>
		void SetAllocateMultiplier(unsigned int amount);

		/// <summary>
		/// Returns the value of max elements which this array can take at this instant
		/// </summary>
		/// <returns></returns>
		unsigned int GetCapacity() const { return m_Capacity; }

		/// <summary>
		/// Returns the current cursor of this array thus returning the number of elements inside the array
		/// </summary>
		/// <returns></returns>
		unsigned int GetCursor() const { return m_Cursor; }

		/// <summary>
		/// Returns a pointer to the const source
		/// </summary>
		/// <returns></returns>
		TValue* GetData() const { return m_Source; }

		/// <summary>
		/// Returns the array allocation multiplier
		/// </summary>
		/// <returns></returns>
		unsigned int GetAllocateMultiplier() const { return m_AllocateMultiplier; }

		/// <summary>
		/// Returns whether the element exists in this array
		/// </summary>
		/// <param name="element"></param>
		/// <returns></returns>
		bool Has(const TValue& element) const;

		/// <summary>
		/// Returns the index of the element
		/// </summary>
		/// <param name="element"></param>
		/// <returns></returns>
		int FindIndex(const TValue& element) const;
	public:
		TValue& operator[](unsigned int index) const;
		void operator=(const Array<TValue>& targetSource);
	private:
		/// <summary>
		/// Clears the source memory
		/// <para>Invokes element deconstructors if the TValue is a value type</para>
		/// </summary>
		void ClearMemory();
	private:
		TValue* m_Source;
		unsigned int m_Capacity;
		unsigned int m_Cursor;
		unsigned int m_AllocateMultiplier;
	};

	/*
	* Implementation
	*/
	template<typename TValue>
	Array<TValue>::Array(unsigned int allocateMultiplier)
	{
		m_Capacity = 0;
		m_Cursor = 0;
		m_Source = nullptr;
		m_AllocateMultiplier = allocateMultiplier;
	}

	template<typename TValue>
	Array<TValue>::Array(const Array<TValue>& targetSource)
	{
		/*
		* Get target source properties
		*/
		m_Cursor = targetSource.m_Cursor;
		m_Capacity = targetSource.m_Capacity;
		m_AllocateMultiplier = targetSource.m_AllocateMultiplier;

		/*
		* Allocate new source
		*/
		m_Source = new TValue[m_Capacity];

		for (unsigned int i = 0; i < m_Cursor; i++)
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
		m_Cursor = count;
		m_Capacity = count;

		/*
		* Allocate new source
		*/
		m_Source = new TValue[m_Capacity];

		for (unsigned int i = 0; i < m_Cursor; i++)
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
		m_Cursor = initializerList.size();
		m_Capacity = initializerList.size();
		/*
		* Copy
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
		ClearMemory();
	}
	template<typename TValue>
	void Array<TValue>::ClearMemory()
	{
		if (m_Source == nullptr)
			return;

		delete[] m_Source;
	}

	template<typename TValue>
	void Array<TValue>::Reserve(unsigned int capacity)
	{
		/*
		* Delete former source
		*/
		ClearMemory();

		/*
		* Allocate new source
		*/
		m_Source = new TValue[capacity];

		/*
		* Set new capacity
		*/
		m_Capacity = capacity;

		/*
		* Reset the cursor
		*/
		m_Cursor = 0;
	}
	template<typename TValue>
	inline void Array<TValue>::Copy(const TValue* data, unsigned int count)
	{
		/*
		* Get properties
		*/
		m_Cursor = count;
		m_Capacity = count;

		/*
		* Allocate new source
		*/
		m_Source = new TValue[m_Capacity];

		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			m_Source[i] = data[i];
		}
	}
	template<typename TValue>
	inline void Array<TValue>::Copy(const Array<TValue>& data, unsigned int start, unsigned int end)
	{
		/*
		* Get properties
		*/
		m_Cursor = end - start;
		m_Capacity = end - start;

		/*
		* Allocate new source
		*/
		m_Source = new TValue[m_Capacity];

		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			m_Source[i] = data[i];
		}
	}
	template<typename TValue>
	inline void Array<TValue>::Move(TValue* targetSource, unsigned long numberOfElements)
	{
		/*
		* Set properties
		*/
		m_Cursor = numberOfElements;
		m_Capacity = numberOfElements;
		m_Source = targetSource;

	}
	template<typename TValue>
	void Array<TValue>::Add(const TValue& element)
	{
		/*
		* Validate array bounds
		*/
		if (m_Cursor >= m_Capacity) // time to extend the bound of this array
		{
			/*
			* Determine the next capacity
			*/
			unsigned int targetCapacity = ((m_Capacity == 0) ? 1 : m_Capacity) * m_AllocateMultiplier;

			/*
			* Allocate new source
			*/
			TValue* newSource = new TValue[targetCapacity];

			/*
			* Fill the new source with the old source data
			*/
			for (unsigned int i = 0; i < m_Cursor; i++)
			{
				newSource[i] = m_Source[i];
			}

			/*
			* Delete the old source
			*/
			ClearMemory();

			/*
			* Set the new source
			*/
			m_Source = newSource;

			/*
			* Set Capacity
			*/
			m_Capacity = targetCapacity;
		}

		/*
		* Set the current cursor data
		*/
		m_Source[m_Cursor] = element;

		/*
		* Increment Cursor
		*/
		m_Cursor++;
	}

	template<typename TValue>
	void Array<TValue>::AddRange(const Array<TValue>& array)
	{
		/*
		* Validate array bounds
		*/
		const unsigned int increaseInSize = array.GetCursor();
		const unsigned int targetSize = m_Cursor + increaseInSize + 1;

		/*
		* Validate if it needs new array
		*/
		if (targetSize >= m_Capacity)
		{
			/*
			* Allocate new source
			*/
			TValue* newSource = new TValue[targetSize];

			/*
			* First set old source
			*/
			for (unsigned int sourceIndex = 0; sourceIndex < m_Cursor; sourceIndex++)
			{
				newSource[sourceIndex] = m_Source[sourceIndex];
			}

			/*
			* Set target array
			*/
			for (unsigned int sourceIndex = 0; sourceIndex < increaseInSize; sourceIndex++)
			{
				newSource[m_Cursor + sourceIndex] = array.m_Source[sourceIndex];
			}

			/*
			* Clear old array
			*/
			ClearMemory();

			/*
			* Set new source
			*/
			m_Source = newSource;

			/*
			* Set cursor
			*/
			m_Cursor = targetSize - 1;
			m_Capacity = m_Cursor;
		}
		else // just needs append
		{
			/*
			* Set target array
			*/
			unsigned int targetArrayIndex = 0;
			for (unsigned int sourceIndex = m_Cursor; sourceIndex < increaseInSize; sourceIndex++)
			{
				m_Source[sourceIndex] = array.m_Source[targetArrayIndex];
				targetArrayIndex++;
			}

			/*
			* Set cursor
			*/
			m_Cursor = targetSize - 1;
		}
	}

	template<typename TValue>
	void Array<TValue>::Insert(unsigned int index, const TValue& element)
	{
		/*
		* Validate array bounds
		*/
		if (m_Cursor >= m_Capacity) // time to extend the bound of this array
		{
			/*
			* Determine the next capacity
			*/
			unsigned int targetCapacity = ((m_Capacity == 0) ? 1 : m_Capacity) * m_AllocateMultiplier;

			/*
			* Allocate new source
			*/
			TValue* newSource = new TValue[targetCapacity];

			/*
			* Fill the new source with the old source data
			*/
			for (unsigned int i = 0; i < m_Cursor; i++)
			{
				newSource[i] = m_Source[i];
			}

			/*
			* Delete the old source
			*/
			ClearMemory();

			/*
			* Set the new source
			*/
			m_Source = newSource;

			/*
			* Set Capacity
			*/
			m_Capacity = targetCapacity;
		}

		/*
		* Shift elements
		*/
		for (unsigned int i = m_Cursor; i > index; i--)
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
		m_Cursor++;
	}
	template<typename TValue>
	void Array<TValue>::SetAllocateMultiplier(unsigned int multiplier)
	{
		/*
		* Set multiplier
		*/
		m_AllocateMultiplier = multiplier;
	}

	template<typename TValue>
	void Array<TValue>::Clear()
	{
		/*
		* Delete source
		*/
		ClearMemory();

		/*
		* Set variables
		*/
		m_Source = nullptr;
		m_Capacity = 0;
		m_Cursor = 0;
	}

	template<typename TValue>
	void Array<TValue>::RemoveIndex(unsigned int index)
	{
		/*
		* Shift elements
		*/
		for (unsigned int i = index + 1; i < m_Cursor; i++)
		{
			m_Source[i - 1] = m_Source[i];
		}

		/*
		* Decrement cursor
		*/
		m_Cursor--;
	}

	template<typename TValue>
	void Array<TValue>::Remove(const TValue& element)
	{
		/*
		* Find it
		*/
		int index = -1;
		for (unsigned int i = 0; i < m_Cursor; i++)
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
		for (unsigned int i = index + 1; i < m_Cursor; i++)
		{
			m_Source[i - 1] = m_Source[i];
		}

		/*
		* Decrement cursor
		*/
		m_Cursor--;
	}
	template<typename TValue>
	void Array<TValue>::Compact()
	{
		/*
		* Create new source
		*/
		TValue* newSource = new TValue[m_Cursor];

		/*
		* Copy the contens
		*/
		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			newSource[i] = m_Source[i];
		}

		/*
		* Update variables
		*/
		m_Capacity = m_Cursor;
	}

	template<typename TValue>
	bool Array<TValue>::Has(const TValue& element) const
	{
		/*
		* Iterator all elements
		*/
		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			if (m_Source[i] == element) // has
				return true;
		}

		return false;
	}

	template<typename TValue>
	int Array<TValue>::FindIndex(const TValue& element) const
	{
		int index = -1;

		/*
		* Iterator all elements
		*/
		for (unsigned int i = 0; i < m_Cursor; i++)
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
		m_Cursor = targetSource.m_Cursor;
		m_Capacity = targetSource.m_Capacity;
		m_AllocateMultiplier = targetSource.m_AllocateMultiplier;

		/*
		* Allocate new source
		*/
		m_Source = new TValue[m_Capacity];

		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			m_Source[i] = targetSource.m_Source[i];
		}
	}
}