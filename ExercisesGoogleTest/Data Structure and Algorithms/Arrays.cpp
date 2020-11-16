#include "../Problems.h"

#include <vector>

// Do not import the full std namespace, but just use vector
template <typename T>
using vector = std::vector<T>;

inline bool isEven(int x);

/* Reorder array elements so that Even numbers are at the beginning */
void EvenOdd(vector<int>* A_ptr)
{
	if (A_ptr->empty())
		return;

	size_t evenIndex = 0;
	size_t oddIndex = A_ptr->size() - 1;

	while (evenIndex < oddIndex)
	{
		while (isEven(A_ptr->at(evenIndex)) && (evenIndex < oddIndex))
			++evenIndex;

		while (!isEven(A_ptr->at(oddIndex)) && (evenIndex < oddIndex))
			--oddIndex;

		if (evenIndex < oddIndex)
			std::swap(A_ptr->at(evenIndex), A_ptr->at(oddIndex));
	}
}

inline bool isEven(int x)
{
	return (x % 2) == 0;
}