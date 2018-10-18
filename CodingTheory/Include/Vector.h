#pragma once

#include <ostream>
#include <vector>
#include "FiniteBody.h"

namespace TomasMo {

	struct Vector final
	{
		using Containter = std::vector<FiniteBody>;

		Containter Values;

		Vector(const Containter& values);

		Vector operator+(const Vector& right) const;

		Vector& operator+=(const Vector& right);

		bool operator!=(const Vector& right) const;
		bool operator==(const Vector& right) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector& obj);
	};
}