Lightweight linear algebra template library for computer graphics
# Install
```
git clone --recursive https://github.com/ChristianPanov/mtlx
```
# Design Highlights
- Based(currently loosely) on the OpenGL Shading Language (GLSL) specifications
- Very lightweight - mtlx is designed to be small and compact, and at the same time, to provide a modern interface for all of the functonality you will need in computer graphics
- Generic - all the mtlx classes are templates which allows for elegant non-repeating flexible solutions
# Features
- Written in modern C++17
- Vectors
- Matrices (Currently working on it)
- Quaternions (NOT ADDED)
- Trigonometric functions (NOT ADDED)
# To be implemented
- Matrices
- Quaternions
- Trigonometric functions
- Policy-based design for switching at compile-time between conventional arithmetic and SIMD instructions
# Usage
## Basic Usage
```cpp
#include <mtlx.h>

int main()
{
	mtlx::vec3 vec(1.0f, 5.0f, 1.0f);
	mtlx::vec3 vec2(vec.x, vec.y, vec.z);
	mtlx::vec3 vec3 = vec + vec2;
  
	auto mag = mtlx::magnitude(vec)

	return 0;
}
```
