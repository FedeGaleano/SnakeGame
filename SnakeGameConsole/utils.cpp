#include "utils.h"

short random::between(int a, int b)
{
	return a + std::rand() % (b - a);
}