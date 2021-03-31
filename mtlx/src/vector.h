#pragma once

#include <cstdint>
#include <type_traits>

#include "vector_storage.h"

namespace mtlx
{
	template<std::uint8_t Dims, typename Type>
	struct vector : public details::vector_storage<Dims, Type>
	{
	public:
		vector() = default;
		template<typename... Args, 
			typename = std::enable_if_t<sizeof...(Args) == Dims>>
		vector(Args&&... args);
		vector(Type (&arr)[Dims]);
		vector(const vector& other);
		vector& operator=(const vector& other);

	public:
		Type& operator[](std::uint8_t index);
		const Type& operator[](std::uint8_t index) const;

	public:
		vector& operator+=(const vector& other);
		vector& operator-=(const vector& other);
		vector& operator*=(Type scalar);
		vector& operator/=(Type scalar);
		vector& operator-();
	};
}

#include "vector_impl.h"