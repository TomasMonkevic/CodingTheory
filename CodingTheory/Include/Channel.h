#pragma once

#include "Vector.h"

namespace TomasMo {

	template<typename T>
	class Channel
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
			//TODO
		}

		Vector<T>& GetInput() { return _input; }
		Vector<T>& GetOutput() { return _output; }
	};
}