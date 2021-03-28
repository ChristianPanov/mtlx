#pragma once

#include <cstdint>
#include <type_traits>

namespace mtlx
{
	template<std::uint8_t Dims, typename Type = float>
	struct vector
	{
	public:
		vector() = default;
		template<typename... Args, 
			typename = std::enable_if_t<sizeof...(Args) == Dims>>
		vector(Args&&... args);
		vector(Type (&arr)[Dims]);
		vector(const vector& other);
		vector& operator=(const vector& other);

	public:
		Type& operator[](std::uint8_t index);
		const Type& operator[](std::uint8_t index) const;

	public:
		vector& operator+=(const vector& other);
		vector& operator-=(const vector& other);
		vector& operator*=(Type scalar);
		vector& operator/=(Type scalar);
		vector& operator-();

	public:
		Type values[Dims]{};
		Type& x{ values[0] };
	};

	template<
		std::uint8_t Dims,
		typename Type = float
	> struct vec : public vector<Dims, Type> {};

	template<typename Type> struct vec<2, Type>;
	template<typename Type> struct vec<3, Type>;
	template<typename Type> struct vec<4, Type>;

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> operator+(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2);

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> operator-(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2);

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> operator*(const vec<Dims, Type>& vec1, Type scalar);

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> operator/(const vec<Dims, Type>& vec1, Type scalar);

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> normalize(const vec<Dims, Type>& vec1);

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> project(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2);

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> reject(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2);

	template<typename Type>
	vec<3, Type> cross(const vec<3, Type>& vec1, const vec<3, Type>& vec2);

	template<std::uint8_t Dims, typename Type>
	Type magnitude(const vec<Dims, Type>& vec1);

	template<std::uint8_t Dims, typename Type>
	Type dot(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2);

	using vec1 = vec<1, float>;
	using vec2 = vec<2, float>;
	using vec3 = vec<3, float>;
	using vec4 = vec<4, float>;

	using vec1i = vec<1, int>;
	using vec2i = vec<2, int>;
	using vec3i = vec<3, int>;
	using vec4i = vec<4, int>;

	using vec1u = vec<1, unsigned int>;
	using vec2u = vec<2, unsigned int>;
	using vec3u = vec<3, unsigned int>;
	using vec4u = vec<4, unsigned int>;

	using vec1b = vec<1, bool>;
	using vec2b = vec<2, bool>;
	using vec3b = vec<3, bool>;
	using vec4b = vec<4, bool>;
}

#include "vector_impl.h"