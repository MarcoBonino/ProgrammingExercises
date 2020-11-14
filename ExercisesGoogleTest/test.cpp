#include "Problems.h"
#include "gtest/gtest.h"

#include <limits>

TEST(PrimitiveTypes, CountBits)
{
	auto count = CountBits(0b10001001);
	ASSERT_EQ(count, 3);

	count = CountBits(0xFFFFFFFF);
	ASSERT_EQ(count, 32);

	count = CountBits(0);
	ASSERT_EQ(count, 0);
}

TEST(PrimitiveTypes, Parity)
{
	auto parity = Parity(0b10001001);
	ASSERT_EQ(parity, 1);

	parity = Parity(0xFFFFFFFF);
	ASSERT_EQ(parity, 0);

	parity = CountBits(0);
	ASSERT_EQ(parity, 0);

	parity = Parity(0b10101010);
	ASSERT_EQ(parity, 0);

	parity = Parity(1);
	ASSERT_EQ(parity, 1);

	parity = Parity(std::numeric_limits<long long unsigned>::max());
	ASSERT_EQ(parity, 0);
}

TEST(PrimitiveTypes, powerOf2)
{
	ASSERT_EQ(helper::powerBase2(0), 1);
	ASSERT_EQ(helper::powerBase2(1), 2);
	ASSERT_EQ(helper::powerBase2(2), 4);
	ASSERT_EQ(helper::powerBase2(3), 8);
	ASSERT_EQ(helper::powerBase2(16), 65536);
}

TEST(PrimitiveTypes, SwapBits)
{
	long long value = 0xFFFF;
	long long swapped = SwapBits(value, 0, 15);
	ASSERT_EQ(swapped, value);

	swapped = SwapBits(value, 0, 16);
	ASSERT_NE(swapped, value);
	ASSERT_EQ(swapped, 0x1FFFE);

	value = 0;
	swapped = SwapBits(value, 2, 3);
	ASSERT_EQ(swapped, value);
	ASSERT_EQ(swapped, 0);

	value = 1ULL << 63; //MSB
	swapped = SwapBits(value, 63, 0);
	ASSERT_EQ(swapped, 0x1);
	swapped = SwapBits(value, 0, 63);
	ASSERT_EQ(swapped, 0x1);
}

TEST(PrimitiveTypes, ReverseBits)
{
	ASSERT_EQ(ReverseBits(1ULL << 63), 1);
	ASSERT_EQ(ReverseBits(1), 1ULL << 63);
	ASSERT_EQ(ReverseBits(0), 0);
	ASSERT_EQ(ReverseBits(0x123), 0xC480000000000000);
}