#pragma once

#include "Vector.h"
#include "ColorPrinter.h"
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
		uint32_t _errorCount = 0;

	public:
		Channel(double flipChance, const Vector<T>& input)
			: _flipChance(flipChance), _input(input)
		{}

		void Simulate()
		{
			_errorCount = 0;
			for (unsigned i = 0; i < _input.Size(); i++)
			{
				double flipChance = double(rand()) / double(RAND_MAX);
				//std::cout << flipChance << std::endl;
				if(flipChance <= _flipChance)
				{
					_output.Add(_input[i].Corrupt());
					_errorCount++;
				}
				else
				{
					_output.Add(_input[i]);
				}
			}
		}

		void DisplayOutputDiff()
		{
			for (unsigned i = 0; i < _input.Size(); i++)
			{
				if(_input[i] != _output[i])
				{
					ColorPrinter::Print(ColorPrinter::Red, "%d", _output[i].GetValue());
				}
				else
				{
					ColorPrinter::Print(ColorPrinter::White, "%d", _output[i].GetValue());
				}
			}
		}

		Vector<T>& GetInput() { return _input; }
		Vector<T>& GetOutput() { return _output; }
		uint32_t GetErrorCount() const { return _errorCount; }
	};
}