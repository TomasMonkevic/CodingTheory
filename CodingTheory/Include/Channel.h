#pragma once

#include "Vector.h"
#include <stdlib.h>

#include <iostream>

namespace TomasMo {

	template<typename T>
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
				_output.Add(flipChance <= _flipChance ? _input[i].Corrupt() : _input[i]);
			}
		}

		Vector<T>& GetInput() { return _input; }
		Vector<T>& GetOutput() { return _output; }
	};
}