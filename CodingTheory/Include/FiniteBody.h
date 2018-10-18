#pragma once

#include <stdint.h>
#include <ostream>

namespace TomasMo {

	struct FiniteBody final
	{
		bool Value;

		static const FiniteBody Zero() { static FiniteBody rez;  return rez; }
		static const FiniteBody One() { static FiniteBody rez(true);  return rez; }

		FiniteBody() noexcept;
		explicit FiniteBody(bool el) noexcept;

		FiniteBody operator+(const FiniteBody& right) const;

		FiniteBody& operator+=(const FiniteBody& right);

		bool operator!=(const FiniteBody& right) const;
		bool operator==(const FiniteBody& right) const;

		friend std::ostream& operator<<(std::ostream& stream, const FiniteBody& obj);
	};

	#define F0 FiniteBody::Zero()
	#define F1 FiniteBody::One()
}