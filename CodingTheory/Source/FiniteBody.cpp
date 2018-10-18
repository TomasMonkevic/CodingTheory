#include "../Include/FiniteBody.h"

namespace TomasMo 
{
	FiniteBody::FiniteBody() noexcept
		: FiniteBody(false)
	{

	}

	FiniteBody::FiniteBody(bool el) noexcept
		: Value(el)
	{
	}

	FiniteBody FiniteBody::operator+(const FiniteBody& right) const
	{
		return FiniteBody(Value != right.Value ? true : false);
	}

	FiniteBody& FiniteBody::operator+=(const FiniteBody& right)
	{
		Value = Value != right.Value ? true : false;
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
		stream << obj.Value;
		return stream;
	}
}