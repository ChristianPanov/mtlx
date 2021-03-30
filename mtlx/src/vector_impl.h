#pragma once

#include "vector.h"
#include "vector_function.h"

#define MTLX_COLOR_ANALOG3 Type& r{ x }, &g{ y }, &b{ z }
#define MTLX_COLOR_ANALOG4 Type& r{ x }, &g{ y }, &b{ z }, &a{ w }

namespace mtlx
{
	template<std::uint8_t Dims, typename Type>
	template<typename ...Args, typename>
	vector<Dims, Type>::vector(Args&&... args)
		: values{ std::forward<Args>(args)... }
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
		MTLX_COLOR_ANALOG3;
	};

	template<typename Type>
	struct vec<4, Type> : public vector<4, Type>
	{
		using vector<4, Type>::vector;
		Type& y{ values[1] };
		Type& z{ values[2] };
		Type& w{ values[3] };
		MTLX_COLOR_ANALOG4;
	};
}