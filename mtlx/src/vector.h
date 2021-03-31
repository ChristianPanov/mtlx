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

	using vec1 = vector<1, float>;
	using vec2 = vector<2, float>;
	using vec3 = vector<3, float>;
	using vec4 = vector<4, float>;

	using vec1i = vector<1, int>;
	using vec2i = vector<2, int>;
	using vec3i = vector<3, int>;
	using vec4i = vector<4, int>;

	using vec1u = vector<1, unsigned int>;
	using vec2u = vector<2, unsigned int>;
	using vec3u = vector<3, unsigned int>;
	using vec4u = vector<4, unsigned int>;

	using vec1b = vector<1, bool>;
	using vec2b = vector<2, bool>;
	using vec3b = vector<3, bool>;
	using vec4b = vector<4, bool>;
}

#include "vector_impl.h"