#include "../Include/Encoder.h"

namespace TomasMo
{
	Encoder::Encoder(const Vector<FiniteField<2>>& state)
		: _state(state)
	{
	}

	void Encoder::Add(FiniteField<2> finiteField)
	{
		_output.Add(finiteField);
		_state.AddFront(finiteField);
		_output.Add(_state[0] + _state[2] + _state[5] + _state[6]);
		_state.Pop();
	}

	Vector<FiniteField<2>>& Encoder::Encode(const Vector<FiniteField<2>>& input)
	{
		for (unsigned i = 0; i < input.Size(); i++)
		{
			Add(input[i]);
		}
		return _output;
	}
}