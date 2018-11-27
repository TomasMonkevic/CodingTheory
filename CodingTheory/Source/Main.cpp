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

	Channel<FiniteField<2>> channel(0.05, encoder.GetOutput());
	channel.Simulate();
	std::cout << "Channel output: ";
	channel.DisplayOutputDiff(); 
	std::cout << std::endl;
	std::cout << channel.GetErrorCount() << " errors made in channel." << std::endl;

	char edditAnwser;
	std::cout << "Do you want to eddit channel ouput? y/n: ";
	std::cin >> edditAnwser;
	if(edditAnwser == 'y' || edditAnwser == 'Y')
	{
		std::cout << "Enter positions to flip: ";
		std::vector<int> positionsToFlip;
		int position;
		do
		{
			std::cin >> position;
			if(position >= 0)
			{
				positionsToFlip.push_back(position);
			}
		}
		while(position >= 0);
		channel.ChangeOutputBits(positionsToFlip);
		std::cout << "Channel output after edit: ";
		channel.DisplayOutputDiff();
		std::cout << std::endl;
		std::cout << channel.GetErrorCount() << " errors made in channel." << std::endl; 
	}

	Decoder decoder(Vector<FiniteField<2>>({ zero, zero, zero, zero, zero, zero }));
	decoder.Decode(channel.GetOutput());
	//TODO also display wrong decoded output in red
	std::cout << "Decoder output: " << decoder.GetTrueOutput() << std::endl;
	std::cin.get();
	return 0;
}