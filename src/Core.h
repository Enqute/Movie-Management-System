#pragma once

#include <iostream>
#include <stdlib.h>
#include <string>

#define ASSERT(condition, message) if (!(condition)) { std::cout << message << std::endl; system("pause"); exit(-1); }
#define ASSERT(condition, the_program, message) if (!(condition)) { std::cout << message << std::endl; system("pause"); goto the_program; }
