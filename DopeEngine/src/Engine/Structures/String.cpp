#include "String.h"
#include <stdio.h>
#include <string>
#include <sstream>
#define MAX_INT_DIGITS 10

namespace DopeEngine
{
	unsigned int get_char_pointer_size(const char* target)
	{
		unsigned int size = 0;
		while (target[size] != '\0')
			size++;
		return size;
	}

	String::String()
	{
		Source = nullptr;
		Cursor = 0;
	}
	String::String(const char* target)
	{
		Cursor = get_char_pointer_size(target);

		Source = new char[(double)Cursor + 1];

		for (unsigned int i = 0; i < Cursor; i++)
		{
			Source[i] = target[i];
		}
		Source[Cursor] = '\0';

	}
	String::String(const unsigned int size)
	{
		Cursor = size;
		Source = new char[Cursor + 1];
		Source[Cursor] = '\0';
	}
	String::String(const char* target, const unsigned int size)
	{
		Cursor = size - 1;
		Source = new char[(double)Cursor + 1];

		for (unsigned int i = 0; i < Cursor; i++)
		{
			Source[i] = target[i];
		}
		Source[Cursor] = '\0';

	}
	String::String(const String& target)
	{

		Cursor = target.Cursor;
		Source = new char[(double)Cursor + 1];

		for (unsigned int i = 0; i < Cursor; i++)
		{
			Source[i] = target.Source[i];
		}
		Source[Cursor] = '\0';
	}
	String::~String()
	{
		Cursor = 0;
		delete[] Source;
		Source = nullptr;
	}
	String String::get_subset(const unsigned int start, const unsigned  int length) const
	{

		unsigned int end = start + length;
		/*if (end >= Cursor)
			end = Cursor - 1;*/

		unsigned int gap = end - start;

		char* subsetSource = new char[gap + 1];

		int subsetIndex = 0;
		for (unsigned int i = start; i < end; i++)
		{
			subsetSource[subsetIndex] = Source[i];
			subsetIndex++;
		}

		subsetSource[gap] = '\0';

		return String(subsetSource);
	}

	char* String::get_source() const
	{
		return Source;
	}

	unsigned int String::get_cursor() const
	{
		return Cursor;
	}



	Array<String> String::splity_by_char(const char targetChar) const
	{
		Array<String> fragments;

		unsigned int startLocation = 0;
		for (unsigned int letterIndex = 0; letterIndex < Cursor; letterIndex++)
		{
			if (Source[letterIndex] == targetChar)
			{
				const unsigned int difference = letterIndex - startLocation;
				if (difference == 0)
					continue;

				String fragment(&Source[startLocation], difference + 1);

				startLocation = letterIndex + 1;

				fragments.add(fragment);
			}

		}

		const unsigned int difference = Cursor - startLocation;
		if (difference != 0)
		{
			String fragment(&Source[startLocation], difference + 1);
			fragments.add(fragment);
		}


		return fragments;
	}
	int String::find_index(const String& targetString,const unsigned int startIndex,const unsigned int targetCount) const
	{
		const unsigned int searchLength = targetString.get_cursor();

		unsigned int foundSoFar = 0;
		int index = -1;
		for (unsigned int charIndex = startIndex; charIndex < Cursor; charIndex++)
		{
			if (Source[charIndex] == targetString[0])
			{
				if (charIndex + targetString.get_cursor() > Cursor) // discard
				{
					continue;
				}

				String subset = get_subset(charIndex, searchLength);
				if (subset == targetString && foundSoFar == targetCount)
				{
					index = charIndex;
					foundSoFar++;
				}
			}
		}

		return index;
	}
	unsigned int String::find_index(const char targetChar) const
	{
		for (unsigned int i = 0; i < Cursor; i++)
		{
			if (Source[i] == targetChar)
			{
				return i;
			}

		}

		return 0;
	}

	unsigned int String::get_count(const char targetChar) const
	{
		unsigned int count = 0;
		for (unsigned int i = 0; i < Cursor; i++)
		{
			if (Source[i] == targetChar)
			{
				count++;
			}

		}

		return count;
	}

	int String::find_last_index(const String& targetString,const unsigned int startIndex) const
	{
		const unsigned int searchLength = targetString.get_cursor();

		unsigned int lastIndexFound = -1;
		for (unsigned int charIndex = startIndex; charIndex < Cursor; charIndex++)
		{
			if (Source[charIndex] == targetString[0])
			{
				if (charIndex + targetString.get_cursor() > Cursor) // discard
				{
					continue;
				}

				String subset = get_subset(charIndex, searchLength);
				if (subset == targetString)
				{
					lastIndexFound = charIndex;
				}
			}
		}

		return lastIndexFound;
	}


	void String::clear()
	{
		delete[] Source;

		Source = new char[1];
		Source[0] = '\0';

		Cursor = 0;
	}

	/*
	* Operators
	*/
	const char* String::operator*() const
	{
		return Source;
	}
	char String::operator[](const unsigned int index) const
	{
		return Source[index];
	}

	void String::operator=(const String& target)
	{
		if (target.Cursor == 0)
		{
			Cursor = 1;
			Source = new char[1];
			Source[0] = '\0';
			return;
		}

		if(Source != nullptr)
			delete[] Source;

		Cursor = target.Cursor;
		Source = new char[(double)Cursor + 1];

		for (unsigned int i = 0; i < Cursor; i++)
		{
			Source[i] = target.Source[i];
		}
		Source[Cursor] = '\0';
	}
	void String::operator+=(const char target)
	{
		const unsigned int targetLength = Cursor + 1;

		char* newSource = new char[targetLength + 1];

		for (unsigned int i = 0; i < Cursor; i++)
		{
			newSource[i] = Source[i];
		}

		newSource[Cursor] = target;

		newSource[Cursor + 1] = '\0';

		delete[] Source;

		Source = newSource;

		Cursor = targetLength;
	}
	void String::operator+=(const char* target)
	{
		unsigned int target_sourceCharLength = get_char_pointer_size(target);
		unsigned int newLength = target_sourceCharLength + Cursor;

		char* newSource = new char[newLength + (unsigned int)1];

		for (unsigned int i = 0; i < Cursor; i++)
		{
			newSource[i] = Source[i];
		}

		{
			int targetIndex = 0;
			for (unsigned int i = Cursor; i < newLength; i++)
			{
				newSource[i] = target[targetIndex];
				targetIndex++;
			}
		}

		newSource[newLength] = '\0';

		delete[] Source;

		Cursor = newLength;
		Source = newSource;

	}
	void String::operator+=(const String& target)
	{
		const unsigned int targetLength = Cursor + target.get_cursor();

		char* newSource = new char[targetLength + 1];

		for (unsigned int i = 0; i < Cursor; i++)
		{
			newSource[i] = Source[i];
		}

		int targetIndex = 0;
		for (unsigned int i = Cursor; i < targetLength; i++)
		{
			newSource[i] = target[targetIndex];
			targetIndex++;
		}

		newSource[targetLength] = '\0';

		delete[] Source;

		Source = newSource;

		Cursor = targetLength;
	}
	String operator+(const String& target0, const String& target1)
	{
		unsigned int newLength = target0.get_cursor() + target1.get_cursor() + 1;

		char* newSource = new char[newLength + 1];

		{
			int targetIndex = 0;
			for (unsigned int i = 0; i < target0.get_cursor(); i++)
			{
				newSource[i] = target0[targetIndex];
				targetIndex++;
			}
		}

		{
			int targetIndex = 0;
			for (unsigned int i = target0.get_cursor(); i < newLength; i++)
			{
				newSource[i] = target1[targetIndex];
				targetIndex++;
			}
		}

		newSource[newLength] = '\0';

		String newStr(newSource);
		return newStr;
	}
	bool operator==(const String& target0, const String& target1)
	{
		unsigned int target0Length = target0.get_cursor();
		unsigned int target1Length = target1.get_cursor();
		const char* target0Source = *target0;
		const char* target1Source = *target1;

		if (target0Length != target1Length)
			return false;

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
		unsigned int target0Length = target0.get_cursor();
		unsigned int target1Length = target1.get_cursor();
		const char* target0Source = *target0;
		const char* target1Source = *target1;

		if (target0Length != target1Length)
			return true;

		for (unsigned int i = 0; i < target0Length; i++)
		{
			if (target0Source[i] != target1Source[i])
			{
				return true;
			}
		}

		return false;
	}

	String String::get_from_float(const float value)
	{
		char* chars = new char[MAX_INT_DIGITS];

		sprintf(chars, "%f", value);

		return chars;
	}
	String String::get_from_integer(const int value)
	{
		char* chars = new char[MAX_INT_DIGITS];

		sprintf(chars, "%d", value);

		return chars;
	}

	float String::to_float(const String& str)
	{
		float value = -1;
		std::stringstream stream(*str);
		stream >> value;
		return value;
	}
}