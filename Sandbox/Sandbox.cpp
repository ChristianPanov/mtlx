#include "vector.h"

#include <iostream>

int main()
{
	vector3d vec(1.0f, 5.0f, 1.0f);

	std::cout << vec.x << "\n";
	std::cout << vec[1] << "\n";

	return 0;
}