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
		static vector<1, Type> call(const vector<1, Type>& vec1, const vector<1, Type>& vec2)
		{
			return vector<1, Type>(vec1.x + vec2.x);
		}
	};

	template<typename Type>
	struct compute_addition<2, Type>
	{
		static vector<2, Type> call(const vector<2, Type>& vec1, const vector<2, Type>& vec2)
		{
			return vector<2, Type>(vec1.x + vec2.x, vec1.y + vec2.y);
		}
	};

	template<typename Type>
	struct compute_addition<3, Type>
	{
		static vector<3, Type> call(const vector<3, Type>& vec1, const vector<3, Type>& vec2)
		{
			return vector<3, Type>(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
		}
	};

	template<typename Type>
	struct compute_addition<4, Type>
	{
		static vector<4, Type> call(const vector<4, Type>& vec1, const vector<4, Type>& vec2)
		{
			return vector<4, Type>(vec1.x + vec2.x, vec1.y + vec2.y,
				vec1.z + vec2.z, vec1.w + vec2.w);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_subtraction {};

	template<typename Type>
	struct compute_subtraction<1, Type>
	{
		static vector<1, Type> call(const vector<1, Type>& vec1, const vector<1, Type>& vec2)
		{
			return vector<1, Type>(vec1.x - vec2.x);
		}
	};

	template<typename Type>
	struct compute_subtraction<2, Type>
	{
		static vector<2, Type> call(const vector<2, Type>& vec1, const vector<2, Type>& vec2)
		{
			return vector<2, Type>(vec1.x - vec2.x, vec1.y - vec2.y);
		}
	};

	template<typename Type>
	struct compute_subtraction<3, Type>
	{
		static vector<3, Type> call(const vector<3, Type>& vec1, const vector<3, Type>& vec2)
		{
			return vector<3, Type>(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
		}
	};

	template<typename Type>
	struct compute_subtraction<4, Type>
	{
		static vector<4, Type> call(const vector<4, Type>& vec1, const vector<4, Type>& vec2)
		{
			return vector<4, Type>(vec1.x - vec2.x, vec1.y - vec2.y,
				vec1.z - vec2.z, vec1.w - vec2.w);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_multiplication {};

	template<typename Type>
	struct compute_multiplication<1, Type>
	{
		static vector<1, Type> call(const vector<1, Type>& vec1, Type scalar)
		{
			return vector<1, Type>(vec1.x * scalar);
		}
	};

	template<typename Type>
	struct compute_multiplication<2, Type>
	{
		static vector<2, Type> call(const vector<2, Type>& vec1, Type scalar)
		{
			return vector<2, Type>(vec1.x * scalar, vec1.y * scalar);
		}
	};

	template<typename Type>
	struct compute_multiplication<3, Type>
	{
		static vector<3, Type> call(const vector<3, Type>& vec1, Type scalar)
		{
			return vector<3, Type>(vec1.x * scalar, vec1.y * scalar, vec1.z * scalar);
		}
	};

	template<typename Type>
	struct compute_multiplication<4, Type>
	{
		static vector<4, Type> call(const vector<4, Type>& vec1, Type scalar)
		{
			return vector<4, Type>(vec1.x * scalar, vec1.y * scalar,
				vec1.z * scalar, vec1.w * scalar);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_division
	{
		static vector<Dims, Type> call(const vector<Dims, Type>& vec1, Type scalar)
		{
			return compute_multiplication<Dims, Type>::call(vec1, 1.0f / scalar);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_dot {};

	template<typename Type>
	struct compute_dot<1, Type>
	{
		static Type call(const vector<1, Type>& vec1, const vector<1, Type>& vec2)
		{
			return vec1.x * vec2.x;
		}
	};

	template<typename Type>
	struct compute_dot<2, Type>
	{
		static Type call(const vector<2, Type>& vec1, const vector<2, Type>& vec2)
		{
			return vec1.x * vec2.x + vec1.y * vec2.y;
		}
	};

	template<typename Type>
	struct compute_dot<3, Type>
	{
		static Type call(const vector<3, Type>& vec1, const vector<3, Type>& vec2)
		{
			return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
		}
	};

	template<typename Type>
	struct compute_dot<4, Type>
	{
		static Type call(const vector<4, Type>& vec1, const vector<4, Type>& vec2)
		{
			return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w;
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_magnitude
	{
		static Type call(const vector<Dims, Type>& vec1)
		{
			return std::sqrt(compute_dot<Dims, Type>::call(vec1, vec1));
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_normalize
	{
		static vector<Dims, Type> call(const vector<Dims, Type>& vec1)
		{
			return vec1 / compute_magnitude<Dims, Type>::call(vec1);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_project
	{
		static vector<Dims, Type> call(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
		{
			return vec2 * (compute_dot<Dims, Type>::call(vec1, vec2) /
				compute_dot<Dims, Type>::call(vec2, vec2));
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_reject
	{
		static vector<Dims, Type> call(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
		{
			return vec1 - compute_project<Dims, Type>::call(vec1, vec2);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct compute_cross
	{
		static vector<Dims, Type> call(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
		{
			return vector<3, Type>(
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
	vector<Dims, Type> operator+(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
	{
		return details::compute_addition<Dims, Type>::call(vec1, vec2);
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator-(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
	{
		return details::compute_subtraction<Dims, Type>::call(vec1, vec2);
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator*(const vector<Dims, Type>& vec1, Type scalar)
	{
		return details::compute_multiplication<Dims, Type>::call(vec1, scalar);
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator/(const vector<Dims, Type>& vec1, Type scalar)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'operator/' only supports floating-point vectors");
		return details::compute_division<Dims, Type>::call(vec1, scalar);
	}

	template<std::uint8_t Dims, typename Type>
	Type dot(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
	{
		return details::compute_dot<Dims, Type>::call(vec1, vec2);
	}

	template<std::uint8_t Dims, typename Type>
	Type magnitude(const vector<Dims, Type>& vec1)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'magnitude' only supports floating-point vectors");
		return details::compute_magnitude<Dims, Type>::call(vec1);
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> normalize(const vector<Dims, Type>& vec1)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'normalize' only supports floating-point vectors");
		return details::compute_normalize<Dims, Type>::call(vec1);
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> project(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'project' only supports floating-point vectors");
		return details::compute_project<Dims, Type>::call(vec1, vec2);
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> reject(const vector<Dims, Type>& vec1, const vector<Dims, Type>& vec2)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'reject' only supports floating-point vectors");
		return details::compute_reject<Dims, Type>::call(vec1, vec2);
	}

	template<typename Type>
	vector<3, Type> cross(const vector<3, Type>& vec1, const vector<3, Type>& vec2)
	{
		return details::compute_cross<3, Type>::call(vec1, vec2);
	}
}