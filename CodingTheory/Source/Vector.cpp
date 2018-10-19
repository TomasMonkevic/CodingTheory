#include "../Include/Vector.h"
#include <algorithm>

namespace TomasMo {

	Vector::Vector()
		: Values()
	{

	}

	Vector::Vector(const Containter& values)
		: Values(values)
	{

	}

	Vector Vector::operator+(const Vector& right) const
	{
		Vector result;
		for(unsigned i=0; i<std::max(Size(), right.Size()); i++)
		{
			if (i >= Size())
			{
				result.Add(F0 + right[i]);
			}
			else if (i >= right.Size())
			{
				result.Add(Values[i] + F0);
			}
			else
			{
				result.Add(Values[i] + right[i]);
			}
		}
		return result;
	}

	Vector& Vector::operator+=(const Vector& right)
	{
		for (unsigned i = 0; i<std::max(Size(), right.Size()); i++)
		{
			if (i >= Size())
			{
				Add(right[i]);
			}
			else if (i >= right.Size())
			{
				continue;
			}
			else
			{
				Values[i] += right[i];
			}
		}
		return *this;
	}

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

	FiniteBody& Vector::operator[](uint32_t index)
	{
		return Values[index];
	}

	FiniteBody Vector::operator[](uint32_t index) const
	{
		return Values[index];
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