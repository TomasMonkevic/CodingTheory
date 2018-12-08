#pragma once

#include "stb_image.h"
#include "stb_image_write.h"
#include <vector>

namespace TomasMo
{
	template <typename T, typename... Args>
	bool MajorityDecisionElement(Args const&... args)
	{
		std::vector<T> buffer{ { args... } };

		uint32_t count = 0;
		for (auto& el : buffer)
		{
			if (el == T::One())
			{
				count++;
			}
		}
		return count > (buffer.size() / 2);
	}
}