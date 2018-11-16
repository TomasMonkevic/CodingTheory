#include "../Include/Decoder.h"

#include <vector>
#include <iostream>

namespace TomasMo
{
	template <typename T, typename... Args>
	bool MajorityDecisionElement (Args const&... args) 
	{    
		std::vector<T> buffer { { args... } };

		uint32_t count = 0;
		for(auto& el : buffer)
		{
			if(el == T::One())
			{
				count++;
			}
		}
		return count >= (buffer.size() / 2);
	}

	Decoder::Decoder(const Vector<FiniteField<2>>& state)
		: _firstState(state), _secondState(state)
	{

	}

	void Decoder::Add(FiniteField<2> firstFiniteField, FiniteField<2> secondFiniteField)
	{
		_firstState.AddFront(firstFiniteField);
		auto firstSum = _firstState[0] + _firstState[2] + _firstState[5] + _firstState[6];

		_secondState.AddFront(firstSum + secondFiniteField);
		bool mdeResult = MajorityDecisionElement<FiniteField<2>>(_secondState[0], _secondState[1],_secondState[4],_secondState[6]);
		std::cout<<mdeResult<<std::endl;

		_output.Add(FiniteField<2>(mdeResult) + _firstState[6]);

		_firstState.Pop();
		_secondState.Pop();
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