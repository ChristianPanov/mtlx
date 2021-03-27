#pragma once

#include <cstdint>
#include <type_traits>

template<
	std::uint8_t Dims,
	typename Type = float
>
struct vector
{
public:
	template<typename... Args,
		typename = std::enable_if_t<sizeof...(Args) == Dims>>
	vector(Args&&... args);

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
Type magnitude(const vector<Dims, Type>& vec);

template<std::uint8_t Dims, typename Type>
vector<Dims, Type> normalize(const vector<Dims, Type>& vec);

#include "vector_impl.h"