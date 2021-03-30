#include "vector.h"
#include "matrix.h"

#include <iostream>

int main()
{
	mtlx::vec3 vec(1.0f, 5.0f, 1.0f);
	mtlx::vec3 vec2(2.0f, 3.0f, 4.0f);

	mtlx::mat3 mat(
		1.0f, 5.0f, 1.0f,
		2.0f, 5.0f, 1.0f,
		3.0f, 5.0f, 1.0f
	);
	mtlx::mat3 mat2(mat);

	mtlx::vec3 vec3 = vec + vec2;

	mtlx::magnitude(vec);

	std::cout << mat2(0, 1) << "\n";
	std::cout << mat2(1, 0) << "\n";

	return 0;
}