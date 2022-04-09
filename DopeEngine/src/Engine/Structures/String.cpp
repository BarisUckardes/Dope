#include "String.h"
#include <stdio.h>
#include <string>
#include <sstream>
#define MAX_INT_DIGITS 10

namespace DopeEngine
{
	unsigned int GetCharPointerSize(const char* target)
	{
		unsigned int size = 0;
		while (target[size] != '\0')
			size++;
		return size;
	}

	String::String()
	{
		m_Source = nullptr;
		m_Cursor = 0;
	}
	String::String(const char* target)
	{
		/*
		* Allocate
		*/
		m_Cursor = GetCharPointerSize(target);
		m_Source = new char[(double)m_Cursor + 1];

		/*
		* Copy
		*/
		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			m_Source[i] = target[i];
		}

		/*
		* Set escape
		*/
		m_Source[m_Cursor] = '\0';

	}
	String::String(unsigned int size)
	{
		/*
		* Allocate
		*/
		m_Cursor = size;
		m_Source = new char[m_Cursor + 1];

		/*
		* Set escape
		*/
		m_Source[m_Cursor] = '\0';
	}
	String::String(const char* target, unsigned int size)
	{
		/*
		* Allocate
		*/
		m_Cursor = size - 1;
		m_Source = new char[(double)m_Cursor + 1];

		/*
		* Copy
		*/
		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			m_Source[i] = target[i];
		}

		/*
		* Set escape
		*/
		m_Source[m_Cursor] = '\0';

	}
	String::String(const String& target)
	{
		/*
		* Allocate
		*/
		m_Cursor = target.m_Cursor;
		m_Source = new char[(double)m_Cursor + 1];

		/*
		* Copy Elements
		*/
		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			m_Source[i] = target.m_Source[i];
		}

		/*
		* Set escape char
		*/
		m_Source[m_Cursor] = '\0';
	}
	String::~String()
	{
		m_Cursor = 0;
		delete[] m_Source;
		m_Source = nullptr;
	}
	String String::GetSubset(unsigned int start, unsigned  int length) const
	{
		/*
		* Normalize cursor
		*/
		unsigned int end = start + length;
		/*if (end >= m_Cursor)
			end = m_Cursor - 1;*/

			/*
			* Create required variables
			*/
		unsigned int gap = end - start;

		/*
		* Create new source for subset
		*/
		char* subsetSource = new char[(double)gap + 1];

		/*
		* Get subset data from the source
		*/
		int subsetIndex = 0;
		for (unsigned int i = start; i < end; i++)
		{
			subsetSource[subsetIndex] = m_Source[i];
			subsetIndex++;
		}

		/*
		* Set escape char
		*/
		subsetSource[gap] = '\0';

		return String(subsetSource);
	}

	char* String::GetSource() const
	{
		return m_Source;
	}

	unsigned int String::GetCursor() const
	{
		return m_Cursor;
	}



	Array<String> String::SplitByChar(char targetChar) const
	{
		/*
		* Initialize array
		*/
		Array<String> fragments;

		/*
		* itarate
		*/
		unsigned int startLocation = 0;
		for (unsigned int letterIndex = 0; letterIndex < m_Cursor; letterIndex++)
		{
			/*
			* Validate equality
			*/
			if (m_Source[letterIndex] == targetChar)
			{
				/*
				* Validate splite requirements
				*/
				const unsigned int difference = letterIndex - startLocation;
				if (difference == 0)
					continue;

				/*
				* Split
				*/
				String fragment(&m_Source[startLocation], difference + 1);

				/*
				* Update start location
				*/
				startLocation = letterIndex + 1;

				/*
				* Register fragment
				*/
				fragments.Add(fragment);
			}

		}

		/*
		* Split to end
		*/
		const unsigned int difference = m_Cursor - startLocation;
		if (difference != 0)
		{
			String fragment(&m_Source[startLocation], difference + 1);
			fragments.Add(fragment);
		}


		return fragments;
	}
	int String::FindIndex(const String& targetString, unsigned int startIndex, unsigned int targetCount) const
	{
		/*
		* Validate remaining chars
		*/
		const unsigned int searchLength = targetString.GetCursor();

		/*
		* Look for sequence of chars
		*/
		unsigned int foundSoFar = 0;
		int index = -1;
		for (unsigned int charIndex = startIndex; charIndex < m_Cursor; charIndex++)
		{
			/*
			* Validate if first letter is matched
			*/
			if (m_Source[charIndex] == targetString[0])
			{
				/*
				* A match found first validate the length
				*/
				if (charIndex + targetString.GetCursor() > m_Cursor) // discard
				{
					continue;
				}

				/*
				* Get subset string
				*/
				String subset = GetSubset(charIndex, searchLength);

				/*
				* Check if its equal
				*/
				if (subset == targetString && foundSoFar == targetCount)
				{
					index = charIndex;
					foundSoFar++;
				}
			}
		}

		return index;
	}
	unsigned int String::FindIndex(char targetChar) const
	{
		/*
		* Look for char
		*/
		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			if (m_Source[i] == targetChar)
			{
				return i;
			}

		}

		return 0;
	}

	unsigned int String::GetCount(char targetChar) const
	{
		/*
		* Look for char
		*/
		unsigned int count = 0;
		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			if (m_Source[i] == targetChar)
			{
				count++;
			}

		}

		return count;
	}

	int String::FindLastIndex(const String& targetString, unsigned int startIndex) const
	{
		/*
		* Validate remaining chars
		*/
		const unsigned int searchLength = targetString.GetCursor();

		/*
		* Look for sequence of chars
		*/
		unsigned int lastIndexFound = -1;
		for (unsigned int charIndex = startIndex; charIndex < m_Cursor; charIndex++)
		{
			/*
			* Validate if first letter is matched
			*/
			if (m_Source[charIndex] == targetString[0])
			{
				/*
				* A match found first validate the length
				*/
				if (charIndex + targetString.GetCursor() > m_Cursor) // discard
				{
					continue;
				}

				/*
				* Get subset string
				*/
				String subset = GetSubset(charIndex, searchLength);

				/*
				* Check if its equal
				*/
				if (subset == targetString)
				{
					lastIndexFound = charIndex;
				}
			}
		}

		return lastIndexFound;
	}


	void String::Clear()
	{
		/*
		* Free the whole array
		*/
		delete[] m_Source;

		/*
		* Create new source
		*/
		m_Source = new char[1];

		/*
		* Set escape
		*/
		m_Source[0] = '\0';

		/*
		* Set cursor
		*/
		m_Cursor = 0;
	}
	/*
	* Operators
	*/
	const char* String::operator*() const
	{
		return m_Source;
	}
	char String::operator[](unsigned int index) const
	{
		return m_Source[index];
	}

	void String::operator=(const String& target)
	{
		/*
		* Check for empty string
		*/
		if (target.m_Cursor == 0)
		{
			m_Cursor = 1;
			m_Source = new char[1];
			m_Source[0] = '\0';
			return;
		}

		/*
		* Clear old source
		*/
		delete[] m_Source;

		/*
		* Allocate
		*/
		m_Cursor = target.m_Cursor;
		m_Source = new char[(double)m_Cursor + 1];

		/*
		* Copy Elements
		*/
		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			m_Source[i] = target.m_Source[i];
		}

		/*
		* Set escape char
		*/
		m_Source[m_Cursor] = '\0';
	}
	void String::operator+=(char target)
	{
		/*
		* Get new length;
		*/
		const unsigned int targetLength = m_Cursor + 1;

		/*
		* Allocate new source
		*/
		char* newSource = new char[targetLength + 1];

		/*
		* Set former elementss
		*/
		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			newSource[i] = m_Source[i];
		}

		/*
		* Set target
		*/
		newSource[m_Cursor] = target;

		/*
		* Set escape
		*/
		newSource[m_Cursor + 1] = '\0';

		/*
		* Free old source
		*/
		delete[] m_Source;

		/*
		* Set new source
		*/
		m_Source = newSource;

		/*
		* Set new length
		*/
		m_Cursor = targetLength;
	}
	void String::operator+=(const char* target)
	{
		/*
		* Get lengths
		*/
		unsigned int targetSourceCharLength = GetCharPointerSize(target);
		unsigned int newLength = targetSourceCharLength + m_Cursor;

		/*
		* Create new source and allocate
		*/
		char* newSource = new char[newLength + (unsigned int)1];

		/*
		* Copy original string
		*/
		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			newSource[i] = m_Source[i];
		}

		/*
		* Copy target char pointer
		*/
		{
			int targetIndex = 0;
			for (unsigned int i = m_Cursor; i < newLength; i++)
			{
				newSource[i] = target[targetIndex];
				targetIndex++;
			}
		}

		/*
		* Set escape
		*/
		newSource[newLength] = '\0';

		/*
		* Free old source
		*/
		delete[] m_Source;

		/*
		* Set new length and source
		*/
		m_Cursor = newLength;
		m_Source = newSource;

	}
	void String::operator+=(const String& target)
	{
		/*
		* Get new length
		*/
		const unsigned int targetLength = m_Cursor + target.GetCursor();

		/*
		* Allocate new source
		*/
		char* newSource = new char[targetLength + 1];

		/*
		* Set former elements
		*/
		for (unsigned int i = 0; i < m_Cursor; i++)
		{
			newSource[i] = m_Source[i];
		}

		/*
		* Copy the target
		*/
		int targetIndex = 0;
		for (unsigned int i = m_Cursor; i < targetLength; i++)
		{
			newSource[i] = target[targetIndex];
			targetIndex++;
		}

		/*
		* Set escape
		*/
		newSource[targetLength] = '\0';

		/*
		* Free old source
		*/
		delete[] m_Source;

		/*
		* Set new source
		*/
		m_Source = newSource;

		/*
		* Set new length
		*/
		m_Cursor = targetLength;
	}
	String operator+(const String& target0, const String& target1)
	{
		/*
		* Get Lengths
		*/
		unsigned int newLength = target0.GetCursor() + target1.GetCursor() + 1;

		/*
		* Allocate new source
		*/
		char* newSource = new char[newLength + 1];

		/*
		* Copy original string
		*/
		{
			int targetIndex = 0;
			for (unsigned int i = 0; i < target0.GetCursor(); i++)
			{
				newSource[i] = target0[targetIndex];
				targetIndex++;
			}
		}

		/*
		* Copy target char pointer
		*/
		{
			int targetIndex = 0;
			for (unsigned int i = target0.GetCursor(); i < newLength; i++)
			{
				newSource[i] = target1[targetIndex];
				targetIndex++;
			}
		}

		newSource[newLength] = '\0';
		/*
		* Create new str and return
		*/
		String newStr(newSource);
		return newStr;
	}
	bool operator==(const String& target0, const String& target1)
	{
		/*
		* Collect length and source
		*/
		unsigned int target0Length = target0.GetCursor();
		unsigned int target1Length = target1.GetCursor();
		const char* target0Source = *target0;
		const char* target1Source = *target1;

		/*
		* First validate lengths
		*/
		if (target0Length != target1Length)
			return false;

		/*
		* Validate chars
		*/
		for (unsigned int i = 0; i < target0Length; i++)
		{
			if (target0Source[i] != target1Source[i])
			{
				return false;
			}
		}

		return true;
	}
	bool operator!=(const String& target0, const String& target1)
	{
		/*
		* Collect length and source
		*/
		unsigned int target0Length = target0.GetCursor();
		unsigned int target1Length = target1.GetCursor();
		const char* target0Source = *target0;
		const char* target1Source = *target1;

		/*
		* First validate lengths
		*/
		if (target0Length != target1Length)
			return true;

		/*
		* Validate chars
		*/
		for (unsigned int i = 0; i < target0Length; i++)
		{
			if (target0Source[i] != target1Source[i])
			{
				return true;
			}
		}

		return false;
	}

	String String::GetFromFloat(float value)
	{
		char* chars = new char[MAX_INT_DIGITS];

		sprintf(chars, "%f", value);

		return chars;
	}

	float String::ToFloat(const String& str)
	{
		float value = -1;
		std::stringstream stream(*str);
		stream >> value;
		return value;
	}
}