#pragma once

#include <ostream>
#include <istream>
#include <vector>
#include <algorithm>

namespace TomasMo {

	template<typename T>
	struct Vector final
	{
		using Containter = std::vector<T>;

		Containter Values;

		Vector()
			: Values()
		{}

		Vector(const Containter& values)
			: Values(values)
		{}

		inline void Add(const T& element) { Values.push_back(element); }
		inline void AddFront(const T& element) { Values.insert(Values.begin(), element); }
		inline void Pop() { Values.pop_back(); }
		inline size_t Size() const { return Values.size(); }

		Vector operator+(const Vector& right) const
		{
			Vector result;
			for (unsigned i = 0; i<std::max(Size(), right.Size()); i++)
			{
				if (i >= Size())
				{
					result.Add(right[i]);
				}
				else if (i >= right.Size())
				{
					result.Add(Values[i]);
				}
				else
				{
					result.Add(Values[i] + right[i]);
				}
			}
			return result;
		}

		Vector& operator+=(const Vector& right)
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

		bool operator!=(const Vector& right) const
		{
			return !(*this == right);
		}

		bool operator==(const Vector& right) const
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

		T& operator[](uint32_t index)
		{
			return Values[index];
		}

		T operator[](uint32_t index) const
		{
			return Values[index];
		}

		friend std::ostream& operator<<(std::ostream& stream, const Vector& obj)
		{
			for (const T& fb : obj.Values)
			{
				stream << fb;
			}
			return stream;
		}

		friend std::istream& operator>>(std::istream& stream, Vector& obj)
		{
			//TODO can be improved but I think not necessery for avaluation
			//separatos would be nice, but for finary doesn't matter
			obj.Values.clear();

			char buffer[256];
			stream.getline(buffer, 256, '\n');
			unsigned i = 0;
			while (buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\0')
			{
				obj.Values.emplace_back(uint32_t(buffer[i] - 0x30));
				i++;
			}
			return stream;
		}
	};
}