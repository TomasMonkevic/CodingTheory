#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include "../Include/FiniteField.h"
#include "../Include/Vector.h"
#include "../Include/Channel.h"
#include "../Include/Encoder.h"
#include "../Include/Decoder.h"

using namespace TomasMo;

static const FiniteField<2> ONE = FiniteField<2>::One();
static const FiniteField<2> ZERO = FiniteField<2>::Zero();

void Scenario1();
void Scenario2();
void Scenario3();

int main()
{
	srand(time(nullptr));

	//Scenario1();
	Scenario2();
	//Scenario3();

	return 0;
}

void Scenario1()
{
	std::cout << "Please enter vector: ";
	Vector<FiniteField<2>> vector;
	std::cin >> vector;

	Encoder encoder(Vector<FiniteField<2>>({ ZERO, ZERO, ZERO, ZERO, ZERO, ZERO }));
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

	Decoder decoder(Vector<FiniteField<2>>({ ZERO, ZERO, ZERO, ZERO, ZERO, ZERO }));
	decoder.Decode(channel.GetOutput());
	//TODO also display wrong decoded output in red
	std::cout << "Decoder output: " << decoder.GetTrueOutput() << std::endl;
	std::cin.get();
}

void Scenario2()
{
	std::cout << "Enter text to encode and send." << std::endl;
	std::string text;
	char line[257];
	do
	{
		std::cin.getline(line, 256, '\n');
		if(strcmp("\\q", line))
		{
			text += line;
			text += '\n';
		}
	}
	while(strcmp("\\q", line));
	std::cout << "Entered text:" << std::endl;
	std::cout << text << std::endl;
	Vector<FiniteField<2>> vector(text);

	Encoder encoder(Vector<FiniteField<2>>({ ZERO, ZERO, ZERO, ZERO, ZERO, ZERO }));
	encoder.Encode(vector);
	//std::cout << "Encoded vector: " << encoder.GetOutput() << std::endl;
	Decoder decoder(Vector<FiniteField<2>>({ ZERO, ZERO, ZERO, ZERO, ZERO, ZERO }));
	decoder.Decode(encoder.GetOutput());
	std::cout << "Decoder output: " << decoder.GetTrueOutput().ToText() << std::endl;
	std::cin.get();
}

void Scenario3()
{

}