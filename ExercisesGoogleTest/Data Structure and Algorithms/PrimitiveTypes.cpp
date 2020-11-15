#include "../Problems.h"

#include <cmath>
#include <mutex>
#include <array>
#include <algorithm>
#include <cassert>
#include <cstdint>

#include <iostream>
#include <typeinfo>
#include <type_traits>

/* Count number of bits set to 1 */
short CountBits(unsigned int x)
{
	short count = 0;
	while (x != 0)
	{
		//if (x % 2) count++;  // branches are slowing down performances
		count += x & 0x1;
		x >>= 1;
	}
	return count;
}

short ParityImplBase(unsigned long long x);
short ParityImplEnhanced(unsigned long long x);
short ParityImplPrecomputed(unsigned long long x);

/* Return 1 if the number of bits set to 1 is odd, 0 otherwise */
short Parity(unsigned long long x)
{
	//return ParityImplBase(x);
	//return ParityImplEnhanced(x);
	return ParityImplPrecomputed(x);
}

/* Worst case time complexity = O(n) where n is the number of bits in x */
short ParityImplBase(unsigned long long x)
{
	short parity = 0;
	while (x != 0)
	{
		parity ^= x & 0x1;
		x >>= 1;
	}
	return parity;
}

/* Worst case time complexity = O(k) where k is the number of bits se to 1 in x */
short ParityImplEnhanced(unsigned long long x)
{
	short parity = 0;
	while (x != 0)
	{
		parity ^= 1;
		x = x & (x - 1); // it will clear the first bit set to one from the right
	}
	return parity;
}

template <size_t CACHE_SIZE>
std::array<bool, CACHE_SIZE> precomputeParityTable()
{
	std::array<bool, CACHE_SIZE> parityCache;
	std::generate(parityCache.begin(), parityCache.end(),
		[index = size_t(0)]() mutable { return ParityImplEnhanced(index++); });
	return parityCache;
}

/* Using pre-computed table */
short ParityImplPrecomputed(unsigned long long x)
{
	constexpr short BIT_WIDTH = 16;
	constexpr unsigned CACHE_SIZE = helper::powerBase2(BIT_WIDTH);
	constexpr unsigned mask = CACHE_SIZE - 1;
	static const std::array<bool, CACHE_SIZE> parityCache = precomputeParityTable<CACHE_SIZE>();

	bool parity = parityCache[x & mask];
	x >>= BIT_WIDTH;
	parity ^= parityCache[x & mask];
	x >>= BIT_WIDTH;
	parity ^= parityCache[x & mask];
	x >>= BIT_WIDTH;
	parity ^= parityCache[x & mask];

	return parity;
}

long long SwapBits(long long x, int i, int j)
{
	assert((i >= 0) && (i < 8 * sizeof(x)));
	assert((j >= 0) && (j < 8 * sizeof(x)));

	// if the 2 bits are different we swap them
	if (((x >> i) & 1) != ((x >> j) & 1))
	{
		long long mask_i = 1ULL << i;
		long long mask_j = 1ULL << j;
		/* x ^ 0 = x
		*  x ^ 1 = ~x
		*  if we negate both bits at position i and j we are swapping them
		*/
		x = x ^ (mask_i | mask_j);
	}

	return x;
}

template <size_t CACHE_SIZE>
std::array<uint8_t, CACHE_SIZE> precomputeReverseBitsTable()
{
	std::array<uint8_t, CACHE_SIZE> table;
	constexpr auto bit_width = 8 * sizeof(std::remove_pointer<decltype(table.data())>);
	for (auto i = 0; i < CACHE_SIZE; ++i)
	{
		uint8_t reverse = 0;
		for (auto bit_pos = 0; bit_pos < bit_width; ++bit_pos)
		{
			// extract bit in in position bit_pos from i
			bool set = ((i >> bit_pos) & 1) != 0;
			reverse |= static_cast<uint8_t>(set) << (bit_width - bit_pos - 1);
		}
		table[i] = reverse;
	}
	return table;
}

unsigned long long ReverseBits(unsigned long long x)
{
	constexpr short BIT_WIDTH = sizeof(uint8_t) * 8;
	constexpr unsigned CACHE_SIZE = helper::powerBase2(BIT_WIDTH);
	constexpr unsigned mask = CACHE_SIZE - 1;
	static const std::array<uint8_t, CACHE_SIZE> reverseBitsCache = precomputeReverseBitsTable<CACHE_SIZE>();

	unsigned long long reversed = 0;

	for (auto i = 0; i < 8 * sizeof(x) / BIT_WIDTH; ++i)
	{
		reversed <<= BIT_WIDTH;
		reversed |= reverseBitsCache[x & mask];
		x >>= BIT_WIDTH;
	}

	return reversed;
}