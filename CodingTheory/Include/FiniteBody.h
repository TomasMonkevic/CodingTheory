#pragma once

#include <stdint.h>
#include <ostream>

namespace TomasMo {

	enum class Elements : uint8_t
	{
		Zero = 0,
		One = 1
	};

	struct FiniteBody final
	{
		Elements Value;

		static const FiniteBody Zero() { static FiniteBody rez;  return rez; }
		static const FiniteBody One() { static FiniteBody rez(Elements::One);  return rez; }

		FiniteBody();
		explicit FiniteBody(Elements el);

		FiniteBody operator+(const FiniteBody& right) const;

		FiniteBody& operator+=(const FiniteBody& right);

		bool operator!=(const FiniteBody& right) const;
		bool operator==(const FiniteBody& right) const;

		friend std::ostream& operator<<(std::ostream& stream, const FiniteBody& obj);
	};
}