#pragma once

#include "vector.h"

namespace mtlx
{
	template<std::uint8_t Dims, typename Type>
	template<typename Arg, typename ...Args, typename>
	vector<Dims, Type>::vector(Arg&& arg, Args&&... args)
	{
		values[0] = arg;
		std::uint8_t counter{ 1 };
		for (auto&& val : { args... })
			values[counter++] = val;
	}

	template<std::uint8_t Dims, typename Type>
	Type& vector<Dims, Type>::operator[](std::uint8_t index)
	{
		return (&x)[index];
	}

	template<std::uint8_t Dims, typename Type>
	const Type& vector<Dims, Type>::operator[](std::uint8_t index) const
	{
		return (&x)[index];
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
		vector<Dims, Type> temp;
		return [&]() {
			for (std::uint8_t i = 0; i < Dims; ++i)
				temp[i] += vec2[i];
			return vector<Dims, Type>(temp);
		}();
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator-(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
	{
		vector<Dims, Type> temp;
		return [&]() {
			for (std::uint8_t i = 0; i < Dims; ++i)
				temp[i] -= vec2[i];
			return vector<Dims, Type>(temp);
		}();
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator*(const vector<Dims, Type>& vec, Type scalar)
	{
		vector<Dims, Type> temp;
		return [&]() {
			for (std::uint8_t i = 0; i < Dims; ++i)
				temp[i] *= scalar;
			return vector<Dims, Type>(temp);
		}();
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator/(const vector<Dims, Type>& vec, Type scalar)
	{
		vector<Dims, Type> temp;
		return [&]() {
			scalar = 1.0f / scalar;
			for (std::uint8_t i = 0; i < Dims; ++i)
				temp[i] *= scalar;
			return vector<Dims, Type>(temp);
		}();
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> normalize(const vector<Dims, Type>& vec)
	{
		return (vec / magnitude(vec));
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> project(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
	{
		return (vec2 * (dot(vec1, vec2) / dot(vec2, vec2)));
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> reject(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
	{
		return (vec1 - vec2 * (dot(vec1, vec2) / dot(vec2, vec2)));
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
	Type dot(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
	{
		return [&]() {
			Type dot_product{};
			for (std::uint8_t i = 0; i < Dims; ++i)
				dot_product += vec1[i] * vec2[i];
			return dot_product;
		}();
	}

	template<typename Type>
	struct vec<2, Type> : public vector<2, Type>
	{
		using vector<2, Type>::vector;
		Type& y{ values[1] };
	};

	template<typename Type>
	struct vec<3, Type> : public vector<3, Type>
	{
		using vector<3, Type>::vector;
		Type& y{ values[1] };
		Type& z{ values[2] };
	};

	template<typename Type>
	struct vec<4, Type> : public vector<4, Type>
	{
		using vector<4, Type>::vector;
		Type& y{ values[1] };
		Type& z{ values[2] };
		Type& w{ values[3] };
	};
}