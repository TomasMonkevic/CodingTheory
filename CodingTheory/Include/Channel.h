#pragma once

#include "Vector.h"

namespace TomasMo {

	class Channel
	{
	private:
		Vector _input;
		Vector _output;
		double _flipChance;

	public:
		Channel(double flipChance, const Vector& input);

		void Simulate();

		Vector& GetInput() { return _input; }
		Vector& GetOutput() { return _output; }
	};
}