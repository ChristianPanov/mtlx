#pragma once

#include "vector.h"
#include "vector_operator.h"

namespace mtlx
{
	template<std::uint8_t Dims, typename Type>
	template<typename... Args, typename>
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
		details::operator_add_asgmt<Dims, Type>::call(*this, other);
		return *this;
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type>& vector<Dims, Type>::operator-=(const vector& other)
	{
		details::operator_sub_asgmt<Dims, Type>::call(*this, other);
		return *this;
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type>& vector<Dims, Type>::operator*=(Type scalar)
	{
		details::operator_mult_asgmt<Dims, Type>::call(*this, other);
		return *this;
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type>& vector<Dims, Type>::operator/=(Type scalar)
	{
		details::operator_div_asgmt<Dims, Type>::call(*this, other);
		return *this;
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type>& vector<Dims, Type>::operator-()
	{
		details::operator_negation<Dims, Type>::call(*this);
		return *this;
	}
}