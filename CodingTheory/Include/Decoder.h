#pragma once

#include "Vector.h"
#include "FiniteField.h"
#include "Utils/Utils.h"

namespace TomasMo
{
	template<typename T> //T èia baigtinis kûnas
	class Decoder final
	{
	private:
		Vector<T> _firstState;
		Vector<T> _secondState;
		Vector<T> _output;
		T _prevMdeResult;

	private:
		void Add(const T& firstFiniteField, const T& secondFiniteField)
		{
			_firstState.AddFront(firstFiniteField);
			auto firstSum = _firstState[0] + _firstState[2] + _firstState[5] + _firstState[6];

			_secondState.AddFront(firstSum + secondFiniteField);

			bool mdeResult = MajorityDecisionElement<T>(_secondState[0], _secondState[1], _secondState[4], _secondState[6]);

			//feddback
			_secondState[0] += _prevMdeResult;
			_secondState[1] += _prevMdeResult;
			_secondState[4] += _prevMdeResult;

			_prevMdeResult = mdeResult;
			//------------------------------

			_output.Add(T(mdeResult) + _firstState[6]);

			_firstState.Pop();
			_secondState.Pop();
		}

	public:
		Decoder(const Vector<T>& state)
			: _firstState(state), _secondState(state), _prevMdeResult(0)
		{}

		Vector<T>& Decode(const Vector<T>& input)
		{
			for (unsigned i = 0; i < input.Size(); i += 2)
			{
				Add(input[i], input[i + 1]);
			}
			return _output;
		}

		Vector<T>& GetOutput() { return _output; }
		Vector<T> GetTrueOutput() const 
		{ 
			auto result = _output;
			result.Drop(6);
			return result;
		}
	};
}