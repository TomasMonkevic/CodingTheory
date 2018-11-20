#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "../Include/FiniteField.h"
#include "../Include/Vector.h"
#include "../Include/Channel.h"
#include "../Include/Encoder.h"
#include "../Include/Decoder.h"

using namespace TomasMo;

int main()
{
	srand(time(nullptr));

	const FiniteField<2> one = FiniteField<2>::One();
	const FiniteField<2> zero = FiniteField<2>::Zero();

	std::cout << "Please enter vector: ";
	Vector<FiniteField<2>> vector;
	std::cin >> vector;

	Encoder encoder(Vector<FiniteField<2>>({ zero, zero, zero, zero, zero, zero }));
	encoder.Encode(vector);
	std::cout << "Encoded vector: " << encoder.GetOutput() << std::endl;

	Channel<FiniteField<2>> channel(0.1, encoder.GetOutput());
	channel.Simulate();
	std::cout << "Channel output: ";
	channel.DisplayOutputDiff(); 
	std::cout << std::endl;
	std::cout << channel.GetErrorCount() << " errors made in channel." << std::endl;

	//TODO show error count end positions
	//TODO let the user change vector

	Decoder decoder(Vector<FiniteField<2>>({ zero, zero, zero, zero, zero, zero }));
	decoder.Decode(channel.GetOutput());
	std::cout << "Decoder output: " << decoder.GetOutput() << std::endl;
	std::cin.get();
	return 0;
}