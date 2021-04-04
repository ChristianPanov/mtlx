#pragma once

#include <cstdint>
#include <type_traits>

namespace mtlx
{
	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	class matrix
	{
	public:
		matrix() = default;
		template<typename... Args,
			typename = std::enable_if_t<sizeof...(Args) == Rows * Cols>>
		matrix(Args&&... args);
		matrix(Type (&arr)[Rows][Cols]);

	public:
		Type& operator()(std::uint8_t col, std::uint8_t row);
		const Type& operator()(std::uint8_t col, std::uint8_t row) const;
		vector<Cols, Type>& operator[](std::uint8_t index);
		const vector<Cols, Type>& operator[](std::uint8_t index) const;

	public:
		Type entries[Rows][Cols]{};
	};
}

#include "matrix_impl.h"