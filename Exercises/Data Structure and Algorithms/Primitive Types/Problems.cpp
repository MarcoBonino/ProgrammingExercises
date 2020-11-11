/* Count number of bits set to 1 */
short CountBits(unsigned int x)
{
	short count = 0;
	while (x != 0)
	{
		if (x % 2) count++;
		count >> 1;
	}
	return count;
}