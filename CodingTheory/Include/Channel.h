#pragma once

#include "Vector.h"
#include "ColorPrinter.h"
#include <stdlib.h>

#include <iostream>

namespace TomasMo {

	template<typename T> //T èia baigtinis kûnas
	class Channel final
	{
	private:
		Vector<T> _input;
		Vector<T> _output;
		double _flipChance;

	public:
		Channel(double flipChance, const Vector<T>& input)
			: _flipChance(flipChance), _input(input)
		{}

		void Simulate()
		{
			for (unsigned i = 0; i < _input.Size(); i++)
			{
				double flipChance = double(rand()) / double(RAND_MAX);
				//std::cout << flipChance << std::endl;
				if(flipChance <= _flipChance)
				{
					_output.Add(_input[i].Corrupt());
				}
				else
				{
					_output.Add(_input[i]);
				}
			}
		}

		void ChangeOutputBits(const std::vector<int>& positions)
		{
			for(auto position : positions)
			{
				_output[position] = _output[position].Corrupt();
			}
		}

		Vector<T>& GetInput() { return _input; }
		Vector<T>& GetOutput() { return _output; }

		uint32_t GetErrorCount() const 
		{ 
			uint32_t result = 0;
			for (unsigned i = 0; i < _input.Size(); i++)
			{
				if(_input[i] != _output[i])
				{
					result++;
				}
			}
			return result;
		}
	};
}