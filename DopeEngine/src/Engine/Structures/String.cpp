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
		/*
		* Allocate
		*/
		Cursor = get_char_pointer_size(target);
		Source = new char[(double)Cursor + 1];

		/*
		* Copy
		*/
		for (unsigned int i = 0; i < Cursor; i++)
		{
			Source[i] = target[i];
		}

		/*
		* Set escape
		*/
		Source[Cursor] = '\0';

	}
	String::String(const unsigned int size)
	{
		/*
		* Allocate
		*/
		Cursor = size;
		Source = new char[Cursor + 1];

		/*
		* Set escape
		*/
		Source[Cursor] = '\0';
	}
	String::String(const char* target, const unsigned int size)
	{
		/*
		* Allocate
		*/
		Cursor = size - 1;
		Source = new char[(double)Cursor + 1];

		/*
		* Copy
		*/
		for (unsigned int i = 0; i < Cursor; i++)
		{
			Source[i] = target[i];
		}

		/*
		* Set escape
		*/
		Source[Cursor] = '\0';

	}
	String::String(const String& target)
	{
		/*
		* Allocate
		*/
		Cursor = target.Cursor;
		Source = new char[(double)Cursor + 1];

		/*
		* Copy Elements
		*/
		for (unsigned int i = 0; i < Cursor; i++)
		{
			Source[i] = target.Source[i];
		}

		/*
		* Set escape char
		*/
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
		/*
		* Normalize cursor
		*/
		unsigned int end = start + length;
		/*if (end >= Cursor)
			end = Cursor - 1;*/

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
			subsetSource[subsetIndex] = Source[i];
			subsetIndex++;
		}

		/*
		* Set escape char
		*/
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
		/*
		* Initialize array
		*/
		Array<String> fragments;

		/*
		* itarate
		*/
		unsigned int startLocation = 0;
		for (unsigned int letterIndex = 0; letterIndex < Cursor; letterIndex++)
		{
			/*
			* Validate equality
			*/
			if (Source[letterIndex] == targetChar)
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
				String fragment(&Source[startLocation], difference + 1);

				/*
				* Update start location
				*/
				startLocation = letterIndex + 1;

				/*
				* Register fragment
				*/
				fragments.add(fragment);
			}

		}

		/*
		* Split to end
		*/
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
		/*
		* Validate remaining chars
		*/
		const unsigned int searchLength = targetString.get_cursor();

		/*
		* Look for sequence of chars
		*/
		unsigned int foundSoFar = 0;
		int index = -1;
		for (unsigned int charIndex = startIndex; charIndex < Cursor; charIndex++)
		{
			/*
			* Validate if first letter is matched
			*/
			if (Source[charIndex] == targetString[0])
			{
				/*
				* A match found first validate the length
				*/
				if (charIndex + targetString.get_cursor() > Cursor) // discard
				{
					continue;
				}

				/*
				* Get subset string
				*/
				String subset = get_subset(charIndex, searchLength);

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
	unsigned int String::find_index(const char targetChar) const
	{
		/*
		* Look for char
		*/
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
		/*
		* Look for char
		*/
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
		/*
		* Validate remaining chars
		*/
		const unsigned int searchLength = targetString.get_cursor();

		/*
		* Look for sequence of chars
		*/
		unsigned int lastIndexFound = -1;
		for (unsigned int charIndex = startIndex; charIndex < Cursor; charIndex++)
		{
			/*
			* Validate if first letter is matched
			*/
			if (Source[charIndex] == targetString[0])
			{
				/*
				* A match found first validate the length
				*/
				if (charIndex + targetString.get_cursor() > Cursor) // discard
				{
					continue;
				}

				/*
				* Get subset string
				*/
				String subset = get_subset(charIndex, searchLength);

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


	void String::clear()
	{
		/*
		* Free the whole array
		*/
		delete[] Source;

		/*
		* Create new source
		*/
		Source = new char[1];

		/*
		* Set escape
		*/
		Source[0] = '\0';

		/*
		* Set cursor
		*/
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
		/*
		* Check for empty string
		*/
		if (target.Cursor == 0)
		{
			Cursor = 1;
			Source = new char[1];
			Source[0] = '\0';
			return;
		}

		/*
		* Clear old source
		*/
		if(Source != nullptr)
			delete[] Source;

		/*
		* Allocate
		*/
		Cursor = target.Cursor;
		Source = new char[(double)Cursor + 1];

		/*
		* Copy Elements
		*/
		for (unsigned int i = 0; i < Cursor; i++)
		{
			Source[i] = target.Source[i];
		}

		/*
		* Set escape char
		*/
		Source[Cursor] = '\0';
	}
	void String::operator+=(const char target)
	{
		/*
		* Get new length;
		*/
		const unsigned int targetLength = Cursor + 1;

		/*
		* Allocate new source
		*/
		char* newSource = new char[targetLength + 1];

		/*
		* Set former elementss
		*/
		for (unsigned int i = 0; i < Cursor; i++)
		{
			newSource[i] = Source[i];
		}

		/*
		* Set target
		*/
		newSource[Cursor] = target;

		/*
		* Set escape
		*/
		newSource[Cursor + 1] = '\0';

		/*
		* Free old source
		*/
		delete[] Source;

		/*
		* Set new source
		*/
		Source = newSource;

		/*
		* Set new length
		*/
		Cursor = targetLength;
	}
	void String::operator+=(const char* target)
	{
		/*
		* Get lengths
		*/
		unsigned int target_sourceCharLength = get_char_pointer_size(target);
		unsigned int newLength = target_sourceCharLength + Cursor;

		/*
		* Create new source and allocate
		*/
		char* newSource = new char[newLength + (unsigned int)1];

		/*
		* Copy original string
		*/
		for (unsigned int i = 0; i < Cursor; i++)
		{
			newSource[i] = Source[i];
		}

		/*
		* Copy target char pointer
		*/
		{
			int targetIndex = 0;
			for (unsigned int i = Cursor; i < newLength; i++)
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
		delete[] Source;

		/*
		* Set new length and source
		*/
		Cursor = newLength;
		Source = newSource;

	}
	void String::operator+=(const String& target)
	{
		/*
		* Get new length
		*/
		const unsigned int targetLength = Cursor + target.get_cursor();

		/*
		* Allocate new source
		*/
		char* newSource = new char[targetLength + 1];

		/*
		* Set former elements
		*/
		for (unsigned int i = 0; i < Cursor; i++)
		{
			newSource[i] = Source[i];
		}

		/*
		* Copy the target
		*/
		int targetIndex = 0;
		for (unsigned int i = Cursor; i < targetLength; i++)
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
		delete[] Source;

		/*
		* Set new source
		*/
		Source = newSource;

		/*
		* Set new length
		*/
		Cursor = targetLength;
	}
	String operator+(const String& target0, const String& target1)
	{
		/*
		* Get Lengths
		*/
		unsigned int newLength = target0.get_cursor() + target1.get_cursor() + 1;

		/*
		* Allocate new source
		*/
		char* newSource = new char[newLength + 1];

		/*
		* Copy original string
		*/
		{
			int targetIndex = 0;
			for (unsigned int i = 0; i < target0.get_cursor(); i++)
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
			for (unsigned int i = target0.get_cursor(); i < newLength; i++)
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
		unsigned int target0Length = target0.get_cursor();
		unsigned int target1Length = target1.get_cursor();
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
		unsigned int target0Length = target0.get_cursor();
		unsigned int target1Length = target1.get_cursor();
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