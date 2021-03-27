#pragma once

#include "vector.h"

namespace mtlx
{
	template<std::uint8_t Dims, typename Type>
	template<typename ...Args, typename>
	vector<Dims, Type>::vector(Args&&... args)
		: values{ std::forward<Args>(args)... }
	{}

	template<std::uint8_t Dims, typename Type>
	Type& vector<Dims, Type>::operator[](std::uint8_t index)
	{
		return values[index];
	}

	template<std::uint8_t Dims, typename Type>
	const Type& vector<Dims, Type>::operator[](std::uint8_t index) const
	{
		return values[index];
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type>& vector<Dims, Type>::operator+=(const vector& other)
	{
		for (std::uint8_t i = 0; i < Dims; ++i)
			values[i] += other[i];
		return *this;
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type>& vector<Dims, Type>::operator-=(const vector& other)
	{
		for (std::uint8_t i = 0; i < Dims; ++i)
			values[i] -= other[i];
		return *this;
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type>& vector<Dims, Type>::operator*=(Type scalar)
	{
		for (std::uint8_t i = 0; i < Dims; ++i)
			values[i] *= scalar;
		return *this;
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type>& vector<Dims, Type>::operator/=(Type scalar)
	{
		scalar = 1.0f / scalar;
		for (std::uint8_t i = 0; i < Dims; ++i)
			values[i] *= scalar;
		return *this;
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type>& vector<Dims, Type>::operator-()
	{
		for (std::uint8_t i = 0; i < Dims; ++i)
			values[i] *= -1;
		return *this;
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator+(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
	{
		return [&]() {
			for (std::uint8_t i = 0; i < Dims; ++i)
				vec1[i] += vec2[i];
			return vector<Dims, Type>(vec1);
		}();
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator-(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
	{
		return [&]() {
			for (std::uint8_t i = 0; i < Dims; ++i)
				vec1[i] -= vec2[i];
			return vector<Dims, Type>(vec1);
		}();
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator*(const vector<Dims, Type>& vec, Type scalar)
	{
		return [&]() {
			for (std::uint8_t i = 0; i < Dims; ++i)
				vec[i] *= scalar;
			return vector<Dims, Type>(vec);
		}();
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator/(const vector<Dims, Type>& vec, Type scalar)
	{
		return [&]() {
			scalar = 1.0f / scalar;
			for (std::uint8_t i = 0; i < Dims; ++i)
				vec[i] *= scalar;
			return vector<Dims, Type>(vec);
		}();
	}

	template<std::uint8_t Dims, typename Type>
	Type magnitude(const vector<Dims, Type>& vec)
	{
		return [vec]() {
			Type mag{};
			for (std::uint8_t i = 0; i < Dims; ++i)
				mag += vec[i] * vec[i];
			return std::sqrt(mag);
		}();
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> normalize(const vector<Dims, Type>& vec)
	{
		return (vec / magnitude(vec));
	}
}