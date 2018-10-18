#include "../Include/Vector.h"

namespace TomasMo {

	Vector::Vector(const Containter& values)
		: Values(values)
	{

	}

	//Vector Vector::operator+(const Vector& right) const
	//{

	//}

	//Vector& Vector::operator+=(const Vector& right)
	//{

	//}

	bool Vector::operator!=(const Vector& right) const
	{
		return !(*this == right);
	}

	bool Vector::operator==(const Vector& right) const
	{
		if (Values.size() != right.Values.size()) return false;
		for (unsigned i = 0; i < Values.size(); i++)
		{
			if (Values[i] != right.Values[i])
			{
				return false;
			}
		}
		return true;
	}

	std::ostream& operator<<(std::ostream& stream, const Vector& obj)
	{
		for (const FiniteBody& fb : obj.Values)
		{
			stream << fb;
		}
		return stream;
	}
}