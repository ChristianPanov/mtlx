#include "vector.h"

#include <iostream>

int main()
{
	mtlx::vec3 vec(1.0f, 5.0f, 1.0f);
	mtlx::vec3 vec2(2.0f, 3.0f, 4.0f);

	mtlx::vec3 vec3 = vec + vec2;

	mtlx::magnitude(vec);

	std::cout << vec3.y << "\n";
	std::cout << vec3.r << "\n";

	return 0;
}