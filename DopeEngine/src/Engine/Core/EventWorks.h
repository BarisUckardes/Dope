#pragma once
#include <functional>
#define BIND_EVENT(function) std::bind(&function,this,std::placeholders::_1)
#define BIND_TARGET_EVENT(object,function) std::bind(&function,object,std::placeholders::_1)