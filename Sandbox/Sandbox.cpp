#include "vector.h"

#include <iostream>

int main()
{
	vector<3, float> vec(1.0f, 5.0f, 1.0f);
	vector<3, float> vec2(2.0f, 3.0f, 4.0f);

	std::cout << vec[1] << "\n";

	return 0;
}