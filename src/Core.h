#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <string>

#define ASSERT(condition, message) if (!(condition)) { std::cout << message << std::endl; system("pause"); exit(-1); }

#endif // CORE_H_INCLUDED
