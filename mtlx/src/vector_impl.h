#pragma once

#include "vector.h"
#include "vector_function.h"

namespace mtlx
{
	template<std::uint8_t Dims, typename Type>
	template<typename ...Args, typename>
	vector<Dims, Type>::vector(Args&&... args)
		: details::vector_storage<Dims, Type>{ args... }
	{}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type>::vector(Type (&arr)[Dims])
	{
		for (std::uint8_t i = 0; i < Dims; ++i)
			values[i] = arr[i];
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type>::vector(const vector& other)
	{
		std::memcpy(values, other.values, Dims * sizeof(Type));
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type>& vector<Dims, Type>::operator=(const vector& other)
	{
		std::memcpy(values, other.values, Dims * sizeof(Type));
		return *this;
	}

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
}