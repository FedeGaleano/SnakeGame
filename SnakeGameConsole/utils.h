#pragma once

#include <random>

template <typename T>
constexpr T switchValuesByTimeLapse(T valueA, T valueB, int ticks)
{
	return (game::ticks / ticks) % 2 == 0 ? valueA : valueB;
}

namespace random
{
	short between(int a, int b);
}