#pragma once

#include <cstdint>
#include <type_traits>

namespace mtlx
{
	template<std::uint8_t Cols, std::uint8_t Rows, typename Type>
	class matrix
	{
	public:
		matrix() = default;
		template<typename... Args,
			typename = std::enable_if_t<sizeof...(Args) == Cols * Rows>>
		matrix(Args&&... args);
		matrix(Type (&arr)[Cols][Rows]);

	public:
		Type& operator()(std::uint8_t col, std::uint8_t row);
		const Type& operator()(std::uint8_t col, std::uint8_t row) const;
		vector<Rows, Type>& operator[](std::uint8_t index);
		const vector<Rows, Type>& operator[](std::uint8_t index) const;

	public:
		Type entries[Cols][Rows]{};
	};
}

#include "matrix_impl.h"