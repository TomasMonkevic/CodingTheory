#pragma once

#include "Vector.h"
#include "FiniteField.h"

namespace TomasMo
{
	class Decoder final
	{
	private:
		Vector<FiniteField<2>> _firstState;
		Vector<FiniteField<2>> _secondState;
		Vector<FiniteField<2>> _output;
		FiniteField<2> _prevMdeResult;

	private:
		void Add(FiniteField<2> firstFiniteField, FiniteField<2> secondFiniteField);

	public:
		Decoder(const Vector<FiniteField<2>>& state);

		Vector<FiniteField<2>>& GetOutput() { return _output; }

		Vector<FiniteField<2>>& Decode(const Vector<FiniteField<2>>& input);
	};
}