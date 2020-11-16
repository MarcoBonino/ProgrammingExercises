#include "Problems.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <limits>
#include <vector>

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

TEST(Arrays_EvenOdd, emptyArray)
{
	std::vector<int> v;
	EvenOdd(&v);
	ASSERT_TRUE(v.empty());
}

TEST(Arrays_EvenOdd, alreadyOrdered)
{
	const std::vector<int> v_orig{ 2, 6, 10, 2, 0, 4, 7, 19, 23, 5, 5, 5, 7, 9 };
	std::vector<int> v_mod(v_orig);
	EvenOdd(&v_mod);
	ASSERT_THAT(v_mod, ::testing::ElementsAreArray(v_orig));
}

MATCHER(first_odd_implies_second_odd, "first element is odd and second even!")
{
	auto isOdd = [](auto x) -> bool { return x & 1; };
	//std::cout << "Compring " << arg[0] << " " << arg[1] << std::endl;
	return !isOdd(arg[0]) || isOdd(arg[1]);
}

TEST(Arrays_EvenOdd, simpleTest_lambda)
{
	std::vector<int> v{ 1, 2, 7, 4, 8, 9, 6, 3 };
	EvenOdd(&v);
	auto isOdd = [](auto x) -> bool { return x & 1; };
	for (size_t i = 0; i < v.size() - 1; ++i)
	{
		ASSERT_TRUE(!isOdd(v[i]) || isOdd(v[i + 1]));
	}
}

TEST(Arrays_EvenOdd, simpleTest_matcher_with_iterator)
{
	std::vector<int> v{ 1, 2, 7, 4, 8, 9, 6, 3 };
	EvenOdd(&v);
	for (auto it = v.begin(); it != v.end() - 1; ++it)
	{
		ASSERT_THAT(it, first_odd_implies_second_odd());
	}
}