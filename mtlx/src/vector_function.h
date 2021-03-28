#pragma once

#include <limits>

namespace mtlx::details
{
	template<std::uint8_t Dims, typename Type>
	struct compute_dot {};

	template<typename Type>
	struct compute_dot<1, Type>
	{
		static Type call(const vec<1, Type>& vec1, const vec<1, Type>& vec2)
		{
			return vec1.x * vec2.x;
		}
	};

	template<typename Type>
	struct compute_dot<2, Type>
	{
		static Type call(const vec<2, Type>& vec1, const vec<2, Type>& vec2)
		{
			return vec1.x * vec2.x + vec1.y * vec2.y;
		}
	};

	template<typename Type>
	struct compute_dot<3, Type>
	{
		static Type call(const vec<3, Type>& vec1, const vec<3, Type>& vec2)
		{
			return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
		}
	};

	template<typename Type>
	struct compute_dot<4, Type>
	{
		static Type call(const vec<4, Type>& vec1, const vec<4, Type>& vec2)
		{
			return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w;
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_magnitude
	{
		static Type call(const vec<Dims, Type>& vec1)
		{
			return std::sqrt(compute_dot<Dims, Type>::call(vec1, vec1));
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_normalize
	{
		static vec<Dims, Type> call(const vec<Dims, Type>& vec1)
		{
			return vec1 / compute_magnitude<Dims, Type>::call(vec1);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_project
	{
		static vec<Dims, Type> call(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2)
		{
			return vec2 * (compute_dot<Dims, Type>::call(vec1, vec2) /
				compute_dot<Dims, Type>::call(vec2, vec2));
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_reject
	{
		static vec<Dims, Type> call(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2)
		{
			return vec1 - compute_project<Dims, Type>::call(vec1, vec2);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_cross
	{
		static vec<Dims, Type> call(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2)
		{
			return vec<3, Type>(
				vec1.y * vec2.z - vec1.z * vec2.y,
				vec1.z * vec2.x - vec1.x * vec2.z,
				vec1.y * vec2.y - vec1.y * vec2.x
				);
		}
	};
}

namespace mtlx
{
	template<std::uint8_t Dims, typename Type>
	Type magnitude(const vec<Dims, Type>& vec1)
	{
		return details::compute_magnitude<Dims, Type>::call(vec1);
	}

	template<std::uint8_t Dims, typename Type>
	Type dot(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2)
	{
		return details::compute_dot<Dims, Type>::call(vec1, vec2);
	}

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> normalize(const vec<Dims, Type>& vec1)
	{
		return details::compute_normalize<Dims, Type>::call(vec1);
	}

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> project(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2)
	{
		return details::compute_project<Dims, Type>::call(vec1, vec2);
	}

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> reject(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2)
	{
		return details::compute_reject<Dims, Type>::call(vec1, vec2);
	}

	template<typename Type>
	vec<3, Type> cross(const vec<3, Type>& vec1, const vec<3, Type>& vec2)
	{
		return details::compute_cross<3, Type>::call(vec1, vec2);
	}
}