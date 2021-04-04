#pragma once

#include <cstdint>
#include <limits>

#define MTLX_STATIC_ASSERT(condition, message) static_assert(condition, message)

namespace mtlx::details
{
	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	struct compute_determinant {};

	template<typename Type>
	struct compute_determinant<2, 2, Type>
	{
		static Type call(const matrix<2, 2, Type>& mat1)
		{
			return(
				mat1(0, 0) * mat1(1, 1) -
				mat1(0, 1) * mat1(1, 0)
				);
		}
	};

	template<typename Type>
	struct compute_determinant<3, 3, Type>
	{
		static Type call(const matrix<3, 3, Type>& mat1)
		{
			return(
				mat1(0, 0) * (mat1(1, 1) * mat1(2, 2) - mat1(1, 2) * mat1(2, 1)) +
				mat1(0, 1) * (mat1(1, 2) * mat1(2, 0) - mat1(1, 0) * mat1(1, 2)) +
				mat1(0, 2) * (mat1(1, 0) * mat1(2, 1) - mat1(1, 1) * mat1(2, 0))
				);
		}
	};

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	struct compute_inverse {};

	template<typename Type>
	struct compute_inverse<3, 3, Type>
	{
		static matrix<3, 3, Type> call(const matrix<3, 3, Type>& mat1)
		{
			const vector<3, Type>& a = mat1[0];
			const vector<3, Type>& b = mat1[1];
			const vector<3, Type>& c = mat1[2];

			vector<3, Type> r0 = compute_cross<3, Type>::call(b, c);
			vector<3, Type> r1 = compute_cross<3, Type>::call(c, a);
			vector<3, Type> r2 = compute_cross<3, Type>::call(a, b);

			Type inv_det = 1.0f / compute_dot<3, Type>::call(r2, c);

			return matrix<3, 3, Type>(
				r0.x * inv_det, r0.y * inv_det, r0.z * inv_det,
				r1.x * inv_det, r1.y * inv_det, r1.z * inv_det,
				r2.x * inv_det, r2.y * inv_det, r2.z * inv_det
				);
		}
	};

	template<typename Type>
	struct compute_inverse<4, 4, Type>
	{
		static matrix<4, 4, Type> call(const matrix<4, 4, Type>& mat1)
		{
			const vector<3, Type>& a = mat1[0];
			const vector<3, Type>& b = mat1[1];
			const vector<3, Type>& c = mat1[2];
			const vector<3, Type>& d = mat1[3];

			const Type& x = mat1(3, 0);
			const Type& y = mat1(3, 1);
			const Type& z = mat1(3, 2);
			const Type& w = mat1(3, 3);

			vector<3, Type> s = compute_cross<3, Type>::call(a, b);
			vector<3, Type> t = compute_cross<3, Type>::call(c, d);
			vector<3, Type> u = a * y - b * x;
			vector<3, Type> v = c * w - d * z;

			Type inv_det = 1.0f / compute_dot<3, Type>::call(s, v) +
				compute_dot<3, Type>::call(t, u);
			s *= inv_det;
			t *= inv_det;
			u *= inv_det;
			v *= inv_det;

			vector<3, Type> r0 = compute_cross<3, Type>::call(b, v) + t * y;
			vector<3, Type> r1 = compute_cross<3, Type>::call(v, a) - t * x;
			vector<3, Type> r2 = compute_cross<3, Type>::call(d, u) + s * w;
			vector<3, Type> r3 = compute_cross<3, Type>::call(u, c) - s * z;

			return matrix<4, 4, Type>(
				r0.x, r0.y, r0.z, -compute_dot<3, Type>::call(b, t),
				r1.x, r1.y, r1.z, +compute_dot<3, Type>::call(a, t),
				r2.x, r2.y, r2.z, -compute_dot<3, Type>::call(d, s),
				r3.x, r3.y, r3.z, +compute_dot<3, Type>::call(c, s)
				);
		}
	};

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	struct compute_rotation_x {};

	template<typename Type>
	struct compute_rotation_x<3, 3, Type>
	{
		static matrix<3, 3, Type> call(Type angle)
		{
			Type cos = std::cos(angle);
			Type sin = std::sin(angle);
			return matrix<3, 3, Type>(
				1.0f, 0.0f, 0.0f,
				0.0f, cos, -sin,
				0.0f, sin, cos
				);
		}
	};

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	struct compute_rotation_y {};

	template<typename Type>
	struct compute_rotation_y<3, 3, Type>
	{
		static matrix<3, 3, Type> call(Type angle)
		{
			Type cos = std::cos(angle);
			Type sin = std::sin(angle);
			return matrix<3, 3, Type>(
				cos, 0.0f, sin,
				0.0f, 1.0f, 0.0f,
				-sin, 0.0f, cos
				);
		}
	};

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	struct compute_rotation_z {};

	template<typename Type>
	struct compute_rotation_z<3, 3, Type>
	{
		static matrix<3, 3, Type> call(Type angle)
		{
			Type cos = std::cos(angle);
			Type sin = std::sin(angle);
			return matrix<3, 3, Type>(
				cos, -sin, 0.0f,
				sin, cos, 0.0f,
				0.0f, 0.0f, 1.0f
				);
		}
	};

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	struct compute_rotation {};

	template<typename Type>
	struct compute_rotation<3, 3, Type>
	{
		static matrix<3, 3, Type> call(Type angle, const vector<3, Type>& axis)
		{
			Type cos = std::cos(angle);
			Type sin = std::sin(angle);
			Type d = 1.0f - cos;
			Type x = axis.x * d;
			Type y = axis.y * d;
			Type z = axis.z * d;
			Type axay = x * axis.y;
			Type axaz = x * axis.z;
			Type ayaz = y * axis.z;

			return matrix<3, 3, Type>(
				cos + x * axis.x, axay - sin * axis.z, axaz + sin * axis.y,
				axay + sin * axis.z, cos + y * axis.y, ayaz - sin * axis.x,
				axaz - sin * axis.y, ayaz + sin * axis.x, cos + z * axis.z
				);
		}
	};

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	struct compute_reflection {};

	template<typename Type>
	struct compute_reflection<3, 3, Type>
	{
		static matrix<3, 3, Type> call(const vector<3, Type>& axis)
		{
			Type x = axis.x * -2.0f;
			Type y = axis.y * -2.0f;
			Type z = axis.z * -2.0f;
			Type axay = x * axis.y;
			Type axaz = x * axis.z;
			Type ayaz = y * axis.z;

			return matrix<3, 3, Type>(
				x * axis.x + 1.0f, axay, axaz,
				axay, y * axis.y + 1.0f, ayaz,
				axaz, ayaz, z * axis.z + 1.0f
				);
		}
	};

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	struct compute_involution {};

	template<typename Type>
	struct compute_involution<3, 3, Type>
	{
		static matrix<3, 3, Type> call(const vector<3, Type>& axis)
		{
			Type x = axis.x * -2.0f;
			Type y = axis.y * -2.0f;
			Type z = axis.z * -2.0f;
			Type axay = x * axis.y;
			Type axaz = x * axis.z;
			Type ayaz = y * axis.z;

			return matrix<3, 3, Type>(
				x * axis.x - 1.0f, axay, axaz,
				axay, y * axis.y - 1.0f, ayaz,
				axaz, ayaz, z * axis.z - 1.0f
				);
		}
	};

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	struct compute_scale {};

	template<typename Type>
	struct compute_scale<3, 3, Type>
	{
		static matrix<3, 3, Type> call(Type sx, Type sy, Type sz)
		{
			return matrix<3, 3, Type>(
				sx, 0.0f, 0.0f,
				0.0f, sy, 0.0f,
				0.0f, 0.0f, sz
				);
		}

		static matrix<3, 3, Type> call(Type s, vector<3, Type> axis)
		{
			s -= 1.0f;
			Type x = axis.x * s;
			Type y = axis.y * s;
			Type z = axis.z * s;
			Type axay = x * axis.y;
			Type axaz = x * axis.z;
			Type ayaz = y * axis.z;

			return matrix<3, 3, Type>(
				x * axis.x + 1.0f, axay, axaz,
				axay, y * axis.y + 1.0f, ayaz,
				axaz, ayaz, z * axis.z + 1.0f
				);
		}
	};

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	struct compute_skew {};

	template<typename Type>
	struct compute_skew<3, 3, Type>
	{
		static matrix<3, 3, Type> call(Type angle, const vector<3, Type>& vec, const vector<3, Type>& vec2)
		{
			angle = std::tan(angle);
			Type x = axis.x * angle;
			Type y = axis.y * angle;
			Type z = axis.z * angle;

			return matrix<3, 3, Type>(
				x * vec2.x + 1.0f, x * vec2.y, x * vec2.z,
				y * vec2.x, y * vec2.y + 1.0f, y * vec2.z,
				z * vec2.x, z * vec2.y, z * vec2.z + 1.0f,
				);
		}
	};
}

namespace mtlx
{
	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	Type determinant(const matrix<Rows, Cols, Type>& mat)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'determinant' only supports floating-point matrices");
		return details::compute_determinant<Rows, Cols, Type>::call(mat);
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	matrix<Rows, Cols, Type> rotate_x(Type angle)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'rotate_x' only supports floating-point values");
		return details::compute_rotation_x<Rows, Cols, Type>::call(angle);
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	matrix<Rows, Cols, Type> rotate_y(Type angle)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'rotate_y' only supports floating-point values");
		return details::compute_rotation_y<Rows, Cols, Type>::call(angle);
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	matrix<Rows, Cols, Type> rotate_z(Type angle)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'rotate_z' only supports floating-point values");
		return details::compute_rotation_z<Rows, Cols, Type>::call(angle);
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	matrix<Rows, Cols, Type> rotate(Type angle, const vector<3, Type>& axis)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'rotate' only supports floating-point values");
		return details::compute_rotation<Rows, Cols, Type>::call(angle, axis);
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	matrix<Rows, Cols, Type> reflect(Type angle, const vector<3, Type>& axis)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'reflect' only supports floating-point values");
		return details::compute_reflection<Rows, Cols, Type>::call(axis);
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	matrix<Rows, Cols, Type> involute(Type angle, const vector<3, Type>& axis)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'involute' only supports floating-point values");
		return details::compute_involution<Rows, Cols, Type>::call(axis);
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	matrix<Rows, Cols, Type> scale(Type sx, Type sy, Type sz)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'scale' only supports floating-point values");
		return details::compute_scale<Rows, Cols, Type>::call(sx, sy, sz);
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	matrix<Rows, Cols, Type> scale(Type s, vector<3, Type> axis)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'scale' only supports floating-point values");
		return details::compute_scale<Rows, Cols, Type>::call(s, axis);
	}

	template<std::uint8_t Rows, std::uint8_t Cols, typename Type>
	matrix<Rows, Cols, Type> skew(Type angle, const vector<3, Type>& vec, const vector<3, Type>& vec2)
	{
		MTLX_STATIC_ASSERT(std::numeric_limits<Type>::is_iec559,
			"'skew' only supports floating-point values");
		return details::compute_skew<Rows, Cols, Type>::call(angle, vec, vec2);
	}
}