#pragma once

#include <limits>

#define MTLX_STATIC_ASSERT(check, message) static_assert(check, message)

namespace mtlx::details
{
	template<std::uint8_t Dims, typename Type>
	struct operator_add {};

	template<typename Type>
	struct operator_add<1, Type>
	{
		static vector<1, Type> call(const vector<1, Type>& vec, const vector<1, Type>& vec2)
		{
			return vector<1, Type>(vec.x + vec2.x);
		}
	};

	template<typename Type>
	struct operator_add<2, Type>
	{
		static vector<2, Type> call(const vector<2, Type>& vec, const vector<2, Type>& vec2)
		{
			return vector<2, Type>(vec.x + vec2.x, vec.y + vec2.y);
		}
	};

	template<typename Type>
	struct operator_add<3, Type>
	{
		static vector<3, Type> call(const vector<3, Type>& vec, const vector<3, Type>& vec2)
		{
			return vector<3, Type>(vec.x + vec2.x, vec.y + vec2.y, vec.z + vec2.z);
		}
	};

	template<typename Type>
	struct operator_add<4, Type>
	{
		static vector<4, Type> call(const vector<4, Type>& vec, const vector<4, Type>& vec2)
		{
			return vector<4, Type>(vec.x + vec2.x, vec.y + vec2.y,
				vec.z + vec2.z, vec.w + vec2.w);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct operator_sub {};

	template<typename Type>
	struct operator_sub<1, Type>
	{
		static vector<1, Type> call(const vector<1, Type>& vec, const vector<1, Type>& vec2)
		{
			return vector<1, Type>(vec.x - vec2.x);
		}
	};

	template<typename Type>
	struct operator_sub<2, Type>
	{
		static vector<2, Type> call(const vector<2, Type>& vec, const vector<2, Type>& vec2)
		{
			return vector<2, Type>(vec.x - vec2.x, vec.y - vec2.y);
		}
	};

	template<typename Type>
	struct operator_sub<3, Type>
	{
		static vector<3, Type> call(const vector<3, Type>& vec, const vector<3, Type>& vec2)
		{
			return vector<3, Type>(vec.x - vec2.x, vec.y - vec2.y, vec.z - vec2.z);
		}
	};

	template<typename Type>
	struct operator_sub<4, Type>
	{
		static vector<4, Type> call(const vector<4, Type>& vec, const vector<4, Type>& vec2)
		{
			return vector<4, Type>(vec.x - vec2.x, vec.y - vec2.y,
				vec.z - vec2.z, vec.w - vec2.w);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct operator_mult {};

	template<typename Type>
	struct operator_mult<1, Type>
	{
		static vector<1, Type> call(const vector<1, Type>& vec, Type scalar)
		{
			return vector<1, Type>(vec.x * scalar);
		}
	};

	template<typename Type>
	struct operator_mult<2, Type>
	{
		static vector<2, Type> call(const vector<2, Type>& vec, Type scalar)
		{
			return vector<2, Type>(vec.x * scalar, vec.y * scalar);
		}
	};

	template<typename Type>
	struct operator_mult<3, Type>
	{
		static vector<3, Type> call(const vector<3, Type>& vec, Type scalar)
		{
			return vector<3, Type>(vec.x * scalar, vec.y * scalar, vec.z * scalar);
		}
	};

	template<typename Type>
	struct operator_mult<4, Type>
	{
		static vector<4, Type> call(const vector<4, Type>& vec, Type scalar)
		{
			return vector<4, Type>(vec.x * scalar, vec.y * scalar,
				vec.z * scalar, vec.w * scalar);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct operator_div
	{
		static vector<Dims, Type> call(const vector<Dims, Type>& vec, Type scalar)
		{
			return operator_mult<Dims, Type>::call(vec, 1.0f / scalar);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct operator_add_asgmt {};

	template<typename Type>
	struct operator_add_asgmt<1, Type>
	{
		static void call(vector<1, Type>& vec, const vector<1, Type>& vec2)
		{
			vec.x += vec2.x;
		}
	};

	template<typename Type>
	struct operator_add_asgmt<2, Type>
	{
		static void call(vector<2, Type>& vec, const vector<2, Type>& vec2)
		{
			vec.x += vec2.x;
			vec.y += vec2.y;
		}
	};

	template<typename Type>
	struct operator_add_asgmt<3, Type>
	{
		static void call(vector<3, Type>& vec, const vector<3, Type>& vec2)
		{
			vec.x += vec2.x;
			vec.y += vec2.y;
			vec.z += vec2.z;
		}
	};

	template<typename Type>
	struct operator_add_asgmt<4, Type>
	{
		static void call(vector<4, Type>& vec, const vector<4, Type>& vec2)
		{
			vec.x += vec2.x;
			vec.y += vec2.y;
			vec.z += vec2.z;
			vec.w += vec2.w;
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct operator_sub_asgmt {};

	template<typename Type>
	struct operator_sub_asgmt<1, Type>
	{
		static void call(vector<1, Type>& vec, const vector<1, Type>& vec2)
		{
			vec.x -= vec2.x;
		}
	};

	template<typename Type>
	struct operator_sub_asgmt<2, Type>
	{
		static void call(vector<2, Type>& vec, const vector<2, Type>& vec2)
		{
			vec.x -= vec2.x;
			vec.y -= vec2.y;
		}
	};

	template<typename Type>
	struct operator_sub_asgmt<3, Type>
	{
		static void call(vector<3, Type>& vec, const vector<3, Type>& vec2)
		{
			vec.x -= vec2.x;
			vec.y -= vec2.y;
			vec.z -= vec2.z;
		}
	};

	template<typename Type>
	struct operator_sub_asgmt<4, Type>
	{
		static void call(vector<4, Type>& vec, const vector<4, Type>& vec2)
		{
			vec.x -= vec2.x;
			vec.y -= vec2.y;
			vec.z -= vec2.z;
			vec.w -= vec2.w;
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct operator_mult_asgmt {};

	template<typename Type>
	struct operator_mult_asgmt<1, Type>
	{
		static void call(vector<1, Type>& vec, Type scalar)
		{
			vec.x *= scalar;
		}
	};

	template<typename Type>
	struct operator_mult_asgmt<2, Type>
	{
		static void call(vector<2, Type>& vec, Type scalar)
		{
			vec.x *= scalar;
			vec.y *= scalar;
		}
	};

	template<typename Type>
	struct operator_mult_asgmt<3, Type>
	{
		static void call(vector<3, Type>& vec, Type scalar)
		{
			vec.x *= scalar;
			vec.y *= scalar;
			vec.z *= scalar;
		}
	};

	template<typename Type>
	struct operator_mult_asgmt<4, Type>
	{
		static void call(vector<4, Type>& vec, Type scalar)
		{
			vec.x *= scalar;
			vec.y *= scalar;
			vec.z *= scalar;
			vec.w *= scalar;
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct operator_div_asgmt
	{
		static void call(vector<Dims, Type>& vec, Type scalar)
		{
			operator_mult_asgmt<Dims, Type>::call(vec, 1.0f / scalar);
		}
	};

	template<std::uint8_t Dims, typename Type>
	struct operator_negation {};

	template<typename Type>
	struct operator_negation<1, Type>
	{
		static void call(vector<1, Type>& vec)
		{
			vec.x = -vec.x;
		}
	};

	template<typename Type>
	struct operator_negation<2, Type>
	{
		static void call(vector<2, Type>& vec)
		{
			vec.x = -vec.x;
			vec.y = -vec.y;
		}
	};

	template<typename Type>
	struct operator_negation<3, Type>
	{
		static void call(vector<3, Type>& vec)
		{
			vec.x = -vec.x;
			vec.y = -vec.y;
			vec.z = -vec.z;
		}
	};

	template<typename Type>
	struct operator_negation<4, Type>
	{
		static void call(vector<4, Type>& vec)
		{
			vec.x = -vec.x;
			vec.y = -vec.y;
			vec.z = -vec.z;
			vec.w = -vec.w;
		}
	};
}

namespace mtlx
{
	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator+(const vector<Dims, Type>& vec, const vector<Dims, Type>& vec2)
	{
		return details::operator_add<Dims, Type>::call(vec, vec2);
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator-(const vector<Dims, Type>& vec, const vector<Dims, Type>& vec2)
	{
		return details::operator_sub<Dims, Type>::call(vec, vec2);
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator*(const vector<Dims, Type>& vec, Type scalar)
	{
		return details::operator_mult<Dims, Type>::call(vec, scalar);
	}

	template<std::uint8_t Dims, typename Type>
	vector<Dims, Type> operator/(const vector<Dims, Type>& vec, Type scalar)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'operator/' only supports floating-point vectors");
		return details::operator_div<Dims, Type>::call(vec, scalar);
	}
}