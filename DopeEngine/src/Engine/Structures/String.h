#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	/// <summary>
	/// Basic string implementation
	/// </summary>
	class DOPE_ENGINE_API String final
	{
	public:
		static String get_from_float(const float value);
		static String get_from_integer(const int value);
		static float to_float(const String& value);
		static int to_integer(const String& value);

		String();
		String(const String& other);
		String(const char* other);
		String(unsigned int size);
		String(const char* target, unsigned int size);

		~String();

		FORCEINLINE unsigned int get_cursor() const;
		FORCEINLINE char* get_source() const;
		int find_index(const String& targetString,const unsigned int startIndex,const unsigned int count = 0) const;
		int find_last_index(const String& targetString,const unsigned int startIndex) const;
		unsigned int find_index(const char targetChar) const;
		unsigned int get_count(const char targetChar) const;
		Array<String> splity_by_char(const char targetChar) const;
		String get_subset(const unsigned int start,const unsigned  int length) const;

		void clear();

		/*
		* Operators
		*/
		const char* operator*() const;
		void operator+=(const String& other);
		void operator+=(const char* other);
		void operator+=(const char other);
		char operator[](const unsigned int index) const;
		void operator=(const String& other);

	private:
		char* Source;
		unsigned int Cursor;
	};

	DOPE_ENGINE_API String operator+(const String& target0, const String& target1);
	DOPE_ENGINE_API bool operator==(const String& target0, const String& target1);
	DOPE_ENGINE_API bool operator!=(const String& target0, const String& target1);
}