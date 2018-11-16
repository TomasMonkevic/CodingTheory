#include "../Include/Decoder.h"

namespace TomasMo
{

	Decoder::Decoder(const Vector<FiniteField<2>>& state)
		: _firstState(state), _secondState(state)
	{

	}

	void Decoder::Add(FiniteField<2> firstFiniteField, FiniteField<2> secondFiniteField)
	{
		//TODO
	}

	Vector<FiniteField<2>>& Decoder::Decode(const Vector<FiniteField<2>>& input)
	{
		for (unsigned i = 0; i < input.Size(); i+=2)
		{
			Add(input[i], input[i+1]);
		}
		return _output;
	}
}