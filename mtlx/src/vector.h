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
		template<typename Arg, typename... Args,
			typename = std::enable_if_t<sizeof...(Args) + 1 == Dims>>
		vector(Arg&& arg, Args&&... args);

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

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator+(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2);

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator-(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2);

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator*(const vector<Dims, Type>& vec, Type scalar);

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator/(const vector<Dims, Type>& vec, Type scalar);

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> normalize(const vector<Dims, Type>& vec);

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> project(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2);

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> reject(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2);

	template<std::uint8_t Dims, typename Type>
	Type magnitude(const vector<Dims, Type>& vec);

	template<std::uint8_t Dims, typename Type>
	Type dot(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2);

	template<
		std::uint8_t Dims,
		typename Type = float
	> struct vec : public vector<Dims, Type> {};

	template<typename Type> struct vec<2, Type>;
	template<typename Type> struct vec<3, Type>;
	template<typename Type> struct vec<4, Type>;

	template<typename Type>
	inline vec<3, Type> cross(const vec<3, Type>& vec1, const vec<3, Type>& vec2);
}

#include "vector_impl.h"