#include <iostream>
#include <cassert>

int findMin(int a, int b, int c)
{
	if (a < b)
		if (a < c)
			return a;
		else
			return c;
	else
		if (b < c)
			return b;
		else
			return c;
}

void testFindMin()
{
	assert(findMin(7, 15, 3) == 3 && "wrong for 7, 15, 3");
	assert(findMin(15, 15, 3) == 3 && "wrong for 15, 15, 3");
	assert(findMin(7, 7, 7) == 7 && "wrong for 7, 7,7");
}

int main()
{
	int a, b, c;
	a = 2;
	b = 5;
	c = 7;
	testFindMin();
	std::cout << findMin(a, b, c);
}
