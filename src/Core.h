#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>

#define ASSERT(condition, message) if (!(condition)) { std::cout << message << std::endl; system("pause"); exit(-1); }
#define print(message) printf("%s\n", message);
