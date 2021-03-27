#include "vector.h"

#include <iostream>

int main()
{
	mtlx::vector<3, float> vec(1.0f, 5.0f, 1.0f);
	mtlx::vector<3, float> vec2(2.0f, 3.0f, 4.0f);

	mtlx::project(vec, vec2);

	std::cout << vec[1] << "\n";

	return 0;
}