#pragma once

#include <stdint.h>
#include <ostream>
#include <istream>
#include <stdlib.h>

namespace TomasMo {

	//Baigtinio k�no klas�.
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

		uint32_t GetValue() const { return _value; }

		//Kei�ia baigtinio k�no reik�m�. Pvz. i� 0 � 1 arba i� 1 � 0
		FiniteField Corrupt()
		{
			FiniteField other = FiniteField(rand() % N);
			return  other == *this ? other + One() : other;
		}

		//Baigtinio k�no sumos operacij�. Suma moduliu N, kur N tai baigtinio k�no element� skai�ius
		FiniteField operator+(const FiniteField& right) const
		{
			return FiniteField(_value + right._value);
		}

		FiniteField& operator+=(const FiniteField& right)
		{
			_value = (_value + right._value) % N;
			return *this;
		}

		//Baigtinio k�no palyginimo operacijos
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

		friend std::istream& operator>>(std::istream& stream, FiniteField& obj)
		{
			stream >> obj._value;
			obj._value %= N;
			return stream;
		}
	};
}