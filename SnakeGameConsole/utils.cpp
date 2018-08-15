#include "utils.h"

short utils::random::between(int a, int b)
{
	return a + std::rand() % (b - a);
}

unsigned int utils::math::modulus(int x, int base)
{
	return (x % base + base) % base;
}
