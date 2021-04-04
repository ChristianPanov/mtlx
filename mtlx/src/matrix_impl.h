#pragma once

#include "matrix.h"
#include "vector.h"

namespace mtlx
{
	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	template<typename... Args, typename>
	matrix<Rows, Cols, Type>::matrix(Args&&... args)
	{
		Type temp[] = { args... };
		std::uint8_t offset{ 0 };
		for (std::uint8_t i = 0; i < Rows; ++i)
		{
			for (std::uint8_t j = 0; j < Cols; ++j)
			{
				entries[i][j] = temp[j + offset];
			}
			offset += Cols;
		}
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	matrix<Rows, Cols, Type>::matrix(Type(&arr)[Rows][Cols])
	{
		std::uint8_t offset{ 0 };
		for (std::uint8_t i = 0; i < Cols; ++i)
		{
			for (std::uint8_t j = 0; j < Rows; ++j)
			{
				entries[i][j] = arr[j + offset];
			}
			offset += Rows;
		}
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	Type& matrix<Rows, Cols, Type>::operator()(std::uint8_t col, std::uint8_t row)
	{
		return entries[row][col];
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	const Type& matrix<Rows, Cols, Type>::operator()(std::uint8_t col, std::uint8_t row) const
	{
		return entries[row][col];
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	vector<Cols, Type>& matrix<Rows, Cols, Type>::operator[](std::uint8_t index)
	{
		return vector<Cols, Type>(entries[index]);
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	const vector<Cols, Type>& matrix<Rows, Cols, Type>::operator[](std::uint8_t index) const
	{
		return vector<Cols, Type>(entries[index]);
	}
}