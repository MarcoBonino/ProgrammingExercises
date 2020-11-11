#include "Problems.h"
#include "gtest/gtest.h"

TEST(PrimitiveTypes, CountBits) {
	auto count = CountBits(0b10001001);
	ASSERT_EQ(count, 3);

	count = CountBits(0xFFFFFFFF);
	ASSERT_EQ(count, 32);

	count = CountBits(0);
	ASSERT_EQ(count, 0);
}

TEST(PrimitiveTypes, Parity) {
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
}