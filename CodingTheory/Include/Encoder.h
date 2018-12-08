#pragma once

#include "Vector.h"
#include "FiniteField.h"

namespace TomasMo
{
	template<typename T>
	class Encoder final
	{
	private:
		Vector<T> _state;
		Vector<T> _output;

	private:
		void Add(T finiteField)
		{
			_output.Add(finiteField);
			_state.AddFront(finiteField);
			_output.Add(_state[0] + _state[2] + _state[5] + _state[6]);
			_state.Pop();
		}

	public:
		Encoder(const Vector<T>& state)
			: _state(state)
		{
		}

		Vector<T>& Encode(const Vector<T>& input)
		{
			for (unsigned i = 0; i < input.Size(); i++)
			{
				Add(input[i]);
			}
			for (unsigned i = 0; i < 6; i++)
			{
				Add(T::Zero());
			}
			return _output;
		}

		Vector<T>& GetOutput() { return _output; }
	};
}