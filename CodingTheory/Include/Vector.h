#pragma once

#include <ostream>
#include <istream>
#include <vector>
#include <algorithm>

namespace TomasMo {

	template<typename T> //T �ia baigtinis k�nas
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

		//Vektoriaus konstravimas i� teksto
		Vector(const std::string& text)
			: Values()
		{
			Values.reserve(text.size());
			for (char c : text)
			{
				uint8_t mask = 0x80;
				for (int8_t i = 7; i >= 0; i--)
				{
					Values.emplace_back(((uint8_t)c & mask) >> i);
					mask = mask >> 1;
				}
			}
		}

		//Vektoriaus konstravimas i� bait�
		Vector(const uint8_t* bytes, uint64_t size)
			: Values()
		{
			Values.reserve(size);
			for (uint64_t j=0; j<size; j++)
			{
				uint8_t mask = 0x80;
				for (int8_t i = 7; i >= 0; i--)
				{
					Values.emplace_back(((uint8_t)bytes[j] & mask) >> i);
					mask = mask >> 1;
				}
			}
		}

		//Vektoriaus konvertavimas � tekst�
		std::string ToText() const
		{
			std::string result = "";

			for (int i=0; i < Values.size() / 8; i++)
			{
				uint8_t c = 0;
				for (int j = 0; j < 8; j++)
				{
					c += Values[i * 8 + j].GetValue();
					if (j != 7)
					{
						c = c << 1;
					}
				}
				result += (char)c;
			}

			return result;
		}

		//Vektoriaus konvertavimas � baitus
		std::vector<uint8_t> ToBytes() const
		{
			std::vector<uint8_t> result;

			for (int i = 0; i < Values.size() / 8; i++)
			{
				uint8_t c = 0;
				for (int j = 0; j < 8; j++)
				{
					c += Values[i * 8 + j].GetValue();
					if (j != 7)
					{
						c = c << 1;
					}
				}
				result.push_back(c);
			}

			return result;
		}

		//Pridedamas baigtinis k�nas � vektoriaus gal�
		inline void Add(const T& element) { Values.push_back(element); }
		//I�trinamas pirmas vektoriaus baigtinis k�nas
		inline void Drop(unsigned count) { Values.erase(Values.begin(), Values.begin() + count); }
		//Pridedamas baigtinis k�nas � vektoriaus prad�i�
		inline void AddFront(const T& element) { Values.insert(Values.begin(), element); }
		//I�trinamas paskutinis vektoriaus baigtinis k�nas
		inline void Pop() { Values.pop_back(); }
		//Gaunamas vektoriaus dydis
		inline size_t Size() const { return Values.size(); }

		//Dviej� vektori� sudeties operacija
		//Baigtiniai k�nai sudedami panariui
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

		//Vektoriu palyginimo funkcija
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
			for (unsigned i = 0; i < obj.Values.size(); i++)
			{
				if(i % 4 == 0 && i != 0)
				{
					stream << ' ';
				}
				stream << obj.Values[i];
			}
			return stream;
		}

		friend std::istream& operator>>(std::istream& stream, Vector& obj)
		{
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