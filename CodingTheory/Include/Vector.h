#pragma once

#include <ostream>
#include <vector>
#include "FiniteBody.h"

namespace TomasMo {

	struct Vector final
	{
		using Containter = std::vector<FiniteBody>;

		Containter Values;

		Vector();
		Vector(const Containter& values);

		inline void Add(const FiniteBody& element) { Values.push_back(element); }
		inline size_t Size() const { return Values.size(); }

		Vector operator+(const Vector& right) const;

		Vector& operator+=(const Vector& right);

		bool operator!=(const Vector& right) const;
		bool operator==(const Vector& right) const;

		FiniteBody& operator[](uint32_t index);
		FiniteBody operator[](uint32_t index) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector& obj);
	};
}