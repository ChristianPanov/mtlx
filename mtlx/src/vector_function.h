#pragma once

#include <limits>

#define MTLX_STATIC_ASSERT(check, message) static_assert(check, message)

namespace mtlx::details
{
	template<std::uint8_t Dims, typename Type>
	struct compute_addition {};

	template<typename Type>
	struct compute_addition<1, Type>
	{
		static vec<1, Type> call(const vec<1, Type>& vec1, const vec<1, Type>& vec2)
		{
			return vec<1, Type>(vec1.x + vec2.x);
		}
	};

	template<typename Type>
	struct compute_addition<2, Type>
	{
		static vec<2, Type> call(const vec<2, Type>& vec1, const vec<2, Type>& vec2)
		{
			return vec<2, Type>(vec1.x + vec2.x, vec1.y + vec2.y);
		}
	};

	template<typename Type>
	struct compute_addition<3, Type>
	{
		static vec<3, Type> call(const vec<3, Type>& vec1, const vec<3, Type>& vec2)
		{
			return vec<3, Type>(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
		}
	};

	template<typename Type>
	struct compute_addition<4, Type>
	{
		static vec<4, Type> call(const vec<4, Type>& vec1, const vec<4, Type>& vec2)
		{
			return vec<4, Type>(vec1.x + vec2.x, vec1.y + vec2.y,
				vec1.z + vec2.z, vec1.w + vec2.w);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_subtraction {};

	template<typename Type>
	struct compute_subtraction<1, Type>
	{
		static vec<1, Type> call(const vec<1, Type>& vec1, const vec<1, Type>& vec2)
		{
			return vec<1, Type>(vec1.x - vec2.x);
		}
	};

	template<typename Type>
	struct compute_subtraction<2, Type>
	{
		static vec<2, Type> call(const vec<2, Type>& vec1, const vec<2, Type>& vec2)
		{
			return vec<2, Type>(vec1.x - vec2.x, vec1.y - vec2.y);
		}
	};

	template<typename Type>
	struct compute_subtraction<3, Type>
	{
		static vec<3, Type> call(const vec<3, Type>& vec1, const vec<3, Type>& vec2)
		{
			return vec<3, Type>(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
		}
	};

	template<typename Type>
	struct compute_subtraction<4, Type>
	{
		static vec<4, Type> call(const vec<4, Type>& vec1, const vec<4, Type>& vec2)
		{
			return vec<4, Type>(vec1.x - vec2.x, vec1.y - vec2.y,
				vec1.z - vec2.z, vec1.w - vec2.w);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_multiplication {};

	template<typename Type>
	struct compute_multiplication<1, Type>
	{
		static vec<1, Type> call(const vec<1, Type>& vec1, Type scalar)
		{
			return vec<1, Type>(vec1.x * scalar);
		}
	};

	template<typename Type>
	struct compute_multiplication<2, Type>
	{
		static vec<2, Type> call(const vec<2, Type>& vec1, Type scalar)
		{
			return vec<2, Type>(vec1.x * scalar, vec1.y * scalar);
		}
	};

	template<typename Type>
	struct compute_multiplication<3, Type>
	{
		static vec<3, Type> call(const vec<3, Type>& vec1, Type scalar)
		{
			return vec<3, Type>(vec1.x * scalar, vec1.y * scalar, vec1.z * scalar);
		}
	};

	template<typename Type>
	struct compute_multiplication<4, Type>
	{
		static vec<4, Type> call(const vec<4, Type>& vec1, Type scalar)
		{
			return vec<4, Type>(vec1.x * scalar, vec1.y * scalar,
				vec1.z * scalar, vec1.w * scalar);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_division
	{
		static vec<Dims, Type> call(const vec<Dims, Type>& vec1, Type scalar)
		{
			return compute_multiplication<Dims, Type>::call(vec1, 1.0f / scalar);
		}
	};

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
	vec<Dims, Type> operator+(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2)
	{
		return details::compute_addition<Dims, Type>::call(vec1, vec2);
	}

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> operator-(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2)
	{
		return details::compute_subtraction<Dims, Type>::call(vec1, vec2);
	}

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> operator*(const vec<Dims, Type>& vec1, Type scalar)
	{
		return details::compute_multiplication<Dims, Type>::call(vec1, scalar);
	}

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> operator/(const vec<Dims, Type>& vec1, Type scalar)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'operator/' only supports floating-point vectors");
		return details::compute_division<Dims, Type>::call(vec1, scalar);
	}

	template<std::uint8_t Dims, typename Type>
	Type dot(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2)
	{
		return details::compute_dot<Dims, Type>::call(vec1, vec2);
	}

	template<std::uint8_t Dims, typename Type>
	Type magnitude(const vec<Dims, Type>& vec1)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'magnitude' only supports floating-point vectors");
		return details::compute_magnitude<Dims, Type>::call(vec1);
	}

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> normalize(const vec<Dims, Type>& vec1)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'normalize' only supports floating-point vectors");
		return details::compute_normalize<Dims, Type>::call(vec1);
	}

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> project(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'project' only supports floating-point vectors");
		return details::compute_project<Dims, Type>::call(vec1, vec2);
	}

	template<std::uint8_t Dims, typename Type>
	vec<Dims, Type> reject(const vec<Dims, Type>& vec1, const vec<Dims, Type>& vec2)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'reject' only supports floating-point vectors");
		return details::compute_reject<Dims, Type>::call(vec1, vec2);
	}

	template<typename Type>
	vec<3, Type> cross(const vec<3, Type>& vec1, const vec<3, Type>& vec2)
	{
		return details::compute_cross<3, Type>::call(vec1, vec2);
	}
}