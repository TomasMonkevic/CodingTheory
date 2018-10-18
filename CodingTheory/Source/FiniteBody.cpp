#include "../Include/FiniteBody.h"

namespace TomasMo 
{
	FiniteBody::FiniteBody()
		: FiniteBody(Elements::Zero)
	{

	}

	FiniteBody::FiniteBody(Elements el)
		: Value(el)
	{
	}

	FiniteBody FiniteBody::operator+(const FiniteBody& right) const
	{
		return FiniteBody(Value != right.Value ? Elements::One : Elements::Zero);
	}

	FiniteBody& FiniteBody::operator+=(const FiniteBody& right)
	{
		Value = Value != right.Value ? Elements::One : Elements::Zero;
		return *this;
	}

	bool FiniteBody::operator!=(const FiniteBody& right) const
	{
		return !(*this == right);
	}

	bool FiniteBody::operator==(const FiniteBody& right) const
	{
		return right.Value == Value;
	}

	std::ostream& operator<<(std::ostream& stream, const FiniteBody& obj)
	{
		stream << (obj.Value == Elements::Zero ? "0" : "1");
		return stream;
	}
}