#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "../Include/FiniteField.h"
#include "../Include/Vector.h"
#include "../Include/Channel.h"
#include "../Include/Encoder.h"
#include "../Include/Decoder.h"
#include "../Include/Utils/Utils.h"

using namespace TomasMo;

static const FiniteField<2> ONE = FiniteField<2>::One();
static const FiniteField<2> ZERO = FiniteField<2>::Zero();

void Scenario1();
void Scenario2();
void Scenario3();

void Differance(std::string left, std::string right)
{
	uint32_t errorCount = 0;
	for (unsigned i = 0; i < left.size(); i++)
	{
		if (left[i] != right[i])
		{
			ColorPrinter::Print(ColorPrinter::Red, "%c", right[i]);
			errorCount++;
		}
		else
		{
			ColorPrinter::Print(ColorPrinter::White, "%c", right[i]);
		}
	}
	std::cout << std::endl;
	std::cout << "Errors made: " << errorCount << std::endl;
}

int main()
{
	srand(time(nullptr));

	//Scenario1();
	//Scenario2();
	Scenario3();

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
	std::cout << "Enter text (\\q - to finish): " << std::endl;
	std::string text;
	char line[257];
	do
	{
		std::cout << "> ";
		std::cin.getline(line, 256, '\n');
		if(strcmp("\\q", line))
		{
			text += line;
			text += '\n';
		}
	}
	while(strcmp("\\q", line));
	text.pop_back();
	Vector<FiniteField<2>> vector(text);

	Encoder encoder(Vector<FiniteField<2>>({ ZERO, ZERO, ZERO, ZERO, ZERO, ZERO }));
	encoder.Encode(vector);

	const double ERROR_CHANCE = 0.02;

	std::cout << "--- with encoding ---" << std::endl;
	Channel<FiniteField<2>> channel(ERROR_CHANCE, encoder.GetOutput());
	channel.Simulate();
	std::cout << channel.GetErrorCount() << " of " << channel.GetInput().Size() << " errors made in channel." << std::endl;

	Decoder decoder(Vector<FiniteField<2>>({ ZERO, ZERO, ZERO, ZERO, ZERO, ZERO }));
	decoder.Decode(channel.GetOutput());
	Differance(vector.ToText(), decoder.GetTrueOutput().ToText());

	std::cout << std::endl;

	std::cout << "--- without encoding ---" << std::endl;
	Channel<FiniteField<2>> channel2(ERROR_CHANCE, vector);
	channel2.Simulate();
	std::cout << channel2.GetErrorCount() << " of " << channel2.GetInput().Size() << " errors made in channel." << std::endl;
	Differance(vector.ToText(), channel2.GetOutput().ToText());
	std::cin.get();
}

void Scenario3()
{
	std::cout << "Enter BMP image absoulte path: ";
	std::string path;
	std::cin >> path;
	int width, height, n;
	uint8_t* image = stbi_load(path.c_str(), &width, &height, &n, 0);
	if (image)
	{
		Vector<FiniteField<2>> vector(image, width * height * n);
		Channel<FiniteField<2>> channel(0.01, vector);
		channel.Simulate();
		std::cout << channel.GetErrorCount() << " of " << channel.GetInput().Size() << " errors made in channel." << std::endl;

		stbi_write_bmp("WithoutEncoding.bmp", width, height, n, channel.GetOutput().ToBytes().data());
	}
	stbi_image_free(image);
	std::cin.get();
}