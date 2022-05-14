#include "TestReflectionClass.h"


GENERATE_REFLECTABLE_FIELD(TestReflectionClass, myInt, int, DopeEngine::ReflectionBindingFlags_None);
GENERATE_MEMBER_FUNCTION(TestReflectionClass, my_test_function, void, DopeEngine::ReflectionBindingFlags_None);
GENERATE_FUNCTION_PARAMETER(TestReflectionClass,my_test_function,TestParameter, void, DopeEngine::ReflectionBindingFlags_None);

void TestReflectionClass::my_test_function()
{

}
