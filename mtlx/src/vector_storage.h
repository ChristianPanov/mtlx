#pragma once

namespace mtlx::details
{
	template<std::uint8_t Dims, typename Type>
	struct vector_storage {};

	template<typename Type>
	struct vector_storage<1, Type>
	{
		union
		{
			struct { Type x; };
			Type values[1];
		};
	};

	template<typename Type>
	struct vector_storage<2, Type>
	{
		union
		{
			struct { Type x, y; };
			struct { Type r, g; };
			Type values[2];
		};
	};

	template<typename Type>
	struct vector_storage<3, Type>
	{
		union
		{
			struct { Type x, y, z; };
			struct { Type r, g, b; };
			Type values[3];
		};
	};

	template<typename Type>
	struct vector_storage<4, Type>
	{
		union
		{
			struct { Type x, y, z, w; };
			struct { Type r, g, b, a; };
			Type values[4];
		};
	};
}