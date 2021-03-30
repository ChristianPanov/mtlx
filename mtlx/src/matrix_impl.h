#pragma once

#include "matrix.h"

namespace mtlx
{
	template<std::uint8_t Cols, std::uint8_t Rows, typename Type>
	template<typename... Args, typename>
	matrix<Cols, Rows, Type>::matrix(Args&&... args)
	{
		Type temp[] = { args... };
		std::uint8_t offset{ 0 };
		for (std::uint8_t i = 0; i < Cols; ++i)
		{
			for (std::uint8_t j = 0; j < Rows; ++j)
			{
				entries[i][j] = temp[j + offset];
			}
			offset += Rows;
		}
	}

	template<std::uint8_t Cols, std::uint8_t Rows, typename Type>
	matrix<Cols, Rows, Type>::matrix(Type(&arr)[Cols][Rows])
	{
		std::uint8_t offset{ 0 };
		for (std::uint8_t i = 0; i < Rows; ++i)
		{
			for (std::uint8_t j = 0; j < Cols; ++j)
			{
				entries[i][j] = arr[j + offset];
			}
			offset += Cols;
		}
	}

	template<std::uint8_t Cols, std::uint8_t Rows, typename Type>
	Type& matrix<Cols, Rows, Type>::operator()(std::uint8_t col, std::uint8_t row)
	{
		return entries[row][col];
	}

	template<std::uint8_t Cols, std::uint8_t Rows, typename Type>
	const Type& matrix<Cols, Rows, Type>::operator()(std::uint8_t col, std::uint8_t row) const
	{
		return entries[row][col];
	}

	template<std::uint8_t Cols, std::uint8_t Rows, typename Type>
	vec<Rows, Type>& matrix<Cols, Rows, Type>::operator[](std::uint8_t index)
	{
		return vec<Rows, Type>(entries[index]);
	}

	template<std::uint8_t Cols, std::uint8_t Rows, typename Type>
	const vec<Rows, Type>& matrix<Cols, Rows, Type>::operator[](std::uint8_t index) const
	{
		return vec<Rows, Type>(entries[index]);
	}
}