#pragma once

#include "vector.h"
#include "matrix.h"

namespace mtlx
{
	using vec1 = vector<1, float>;
	using vec2 = vector<2, float>;
	using vec3 = vector<3, float>;
	using vec4 = vector<4, float>;

	using vec1i = vector<1, int>;
	using vec2i = vector<2, int>;
	using vec3i = vector<3, int>;
	using vec4i = vector<4, int>;

	using vec1u = vector<1, unsigned int>;
	using vec2u = vector<2, unsigned int>;
	using vec3u = vector<3, unsigned int>;
	using vec4u = vector<4, unsigned int>;

	using vec1b = vector<1, bool>;
	using vec2b = vector<2, bool>;
	using vec3b = vector<3, bool>;
	using vec4b = vector<4, bool>;

	using mat2 = matrix<2, 2, float>;
	using mat3 = matrix<3, 3, float>;
	using mat4 = matrix<4, 4, float>;
}