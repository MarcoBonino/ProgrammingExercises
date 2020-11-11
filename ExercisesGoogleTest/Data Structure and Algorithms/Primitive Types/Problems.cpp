#include "../../Problems.h"

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

/* Return 1 if the number of bits set to 1 is odd, 0 otherwise */
short Parity(unsigned long long x)
{
	short parity = 0;
	while (x != 0)
	{
		parity ^= x & 0x1;
		x >>= 1;
	}
	return parity;
}