#pragma once

short CountBits(unsigned int x);
short Parity(unsigned long long x);
long long SwapBits(long long x, int i, int j);

namespace helper
{
	constexpr long long unsigned powerBase2(unsigned int exp)
	{
		if (exp == 1)
			return 2;
		if (exp == 0)
			return 1;
		return 2 * powerBase2(exp - 1);
	}
}