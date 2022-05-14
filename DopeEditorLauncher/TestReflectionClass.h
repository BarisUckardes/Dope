#pragma once
#include <Engine/Reflection/Reflection.h>

class TestReflectionClass : public DopeEngine::ReflectableObject
{
public:
	GENERATE_REFLECTABLE_OBJECT(TestReflectionClass);
	TestReflectionClass() = default;

	int myInt;
	void my_test_function();
};

GENERATE_REFLECTION_ACCESSOR(TestReflectionClass);