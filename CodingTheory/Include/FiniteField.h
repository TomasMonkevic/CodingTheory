#pragma once

#include <stdint.h>
#include <ostream>

namespace TomasMo {

	template<uint32_t N>
	class FiniteField final
	{
	private:
		uint32_t _value;

	public:
		static const FiniteField Zero() { static FiniteField rez(0);  return rez; }
		static const FiniteField One() { static FiniteField rez(1);  return rez; }

		FiniteField() noexcept
			: FiniteField(0)
		{}

		FiniteField(uint32_t value) noexcept
			: _value(value % N)
		{}

		FiniteField operator+(const FiniteField& right) const
		{
			return FiniteField(_value + right._value);
		}

		FiniteField& operator+=(const FiniteField& right)
		{
			_value = (_value + right._value) % N;
			return *this;
		}

		bool operator!=(const FiniteField& right) const
		{
			return !(*this == right);
		}

		bool operator==(const FiniteField& right) const
		{
			return right._value == _value;
		}

		friend std::ostream& operator<<(std::ostream& stream, const FiniteField& obj)
		{
			stream << obj._value;
			return stream;
		}
	};
}