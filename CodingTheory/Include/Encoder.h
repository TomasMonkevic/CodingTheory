#pragma once

#include "Vector.h"
#include "FiniteField.h"

namespace TomasMo
{
	class Encoder final
	{
	private:
		Vector<FiniteField<2>> _state;
		Vector<FiniteField<2>> _output;

	private:
		void Add(FiniteField<2> finiteField);

	public:
		Encoder(const Vector<FiniteField<2>>& state);

		Vector<FiniteField<2>>& GetOutput() { return _output; }

		Vector<FiniteField<2>>& Encode(const Vector<FiniteField<2>>& input);
	};
}