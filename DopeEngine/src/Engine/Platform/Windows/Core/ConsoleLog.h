#pragma once
#include <stdio.h>

#define LOG_IMPL(header,content,...) printf("[%s]: ",header); printf(content,__VA_ARGS__); printf("\n");