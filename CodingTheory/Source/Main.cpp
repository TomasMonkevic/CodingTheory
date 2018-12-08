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

void Scenario1(double errorRate);
void Scenario2(double errorRate);
void Scenario3(double errorRate);

void ChangeErrorRate(double& errorRate);

void Differance(const std::string& left, const std::string& right);
void Differance(const Vector<FiniteField<2>>& left, const Vector<FiniteField<2>>& right);

int main()
{
	srand(time(nullptr));

	char selection = '0';
	double errorRate = 0.05;
	do
	{
		std::cout << "----------Menu-----------" << std::endl;
		std::cout << "Current error rate: " << errorRate << std::endl;
		std::cout << "-------------------------" << std::endl;
		std::cout << "1. Scenario 1 (Vectors)" << std::endl;
		std::cout << "2. Scenario 2 (Text)" << std::endl;
		std::cout << "3. Scenario 3 (Images)" << std::endl;
		std::cout << "4. Change error rate" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "-------------------------" << std::endl;
		selection = '0';
		std::cin.get(selection);
		switch (selection)
		{
			case '1':
				Scenario1(errorRate);
				break;
			case '2':
				Scenario2(errorRate);
				break;
			case '3':
				Scenario3(errorRate);
				break;
			case '4':
				ChangeErrorRate(errorRate);
				break;
			case '0':
				break;
			default:
				std::cout << "Incorrect input!" << std::endl;
				selection = -1;
				break;
		}
	} 
	while (selection != '0');
	return 0;
}

void Scenario1(double errorRate)
{
	std::cout << "Please enter vector: ";
	Vector<FiniteField<2>> vector;
	std::cin.ignore(256, '\n');
	std::cin >> vector;

	Encoder encoder(Vector<FiniteField<2>>({ ZERO, ZERO, ZERO, ZERO, ZERO, ZERO }));
	encoder.Encode(vector);
	std::cout << "Encoded vector: " << encoder.GetOutput() << std::endl;

	Channel<FiniteField<2>> channel(errorRate, encoder.GetOutput());
	channel.Simulate();
	std::cout << "Channel output: ";
	Differance(channel.GetInput(), channel.GetOutput());
	std::cout << std::endl;
	//std::cout << channel.GetErrorCount() << " errors made in channel." << std::endl;

	char edditAnwser;
	std::cout << "Do you want to eddit channel ouput? y/n: ";
	std::cin >> edditAnwser;
	if(edditAnwser == 'y' || edditAnwser == 'Y')
	{
		std::cout << "Enter positions to flip ('-1' - to finish): " << std::endl;
		std::vector<int> positionsToFlip;
		int position;
		do
		{
			std::cout << "> ";
			std::cin >> position;
			if(position >= 0)
			{
				positionsToFlip.push_back(position);
			}
		}
		while(position >= 0);
		channel.ChangeOutputBits(positionsToFlip);
		std::cout << "Channel output after edit: ";
		Differance(channel.GetInput(), channel.GetOutput());
		std::cout << std::endl;
		//std::cout << channel.GetErrorCount() << " errors made in channel." << std::endl; 
	}

	Decoder decoder(Vector<FiniteField<2>>({ ZERO, ZERO, ZERO, ZERO, ZERO, ZERO }));
	decoder.Decode(channel.GetOutput());

	std::cout << "Decoder output: " << std::endl;
	Differance(vector, decoder.GetTrueOutput());
	std::cin.get();
}

void Scenario2(double errorRate)
{
	std::cin.ignore(256, '\n');
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
	if (text.empty())
	{
		std::cout << "No input found!" << std::endl;
		return;
	}
	text.pop_back();
	Vector<FiniteField<2>> vector(text);

	Encoder encoder(Vector<FiniteField<2>>({ ZERO, ZERO, ZERO, ZERO, ZERO, ZERO }));
	encoder.Encode(vector);

	std::cout << "--- with encoding ---" << std::endl;
	Channel<FiniteField<2>> channel(errorRate, encoder.GetOutput());
	channel.Simulate();
	std::cout << channel.GetErrorCount() << " of " << channel.GetInput().Size() << " errors made in channel." << std::endl;

	Decoder decoder(Vector<FiniteField<2>>({ ZERO, ZERO, ZERO, ZERO, ZERO, ZERO }));
	decoder.Decode(channel.GetOutput());
	Differance(vector.ToText(), decoder.GetTrueOutput().ToText());

	std::cout << std::endl;

	std::cout << "--- without encoding ---" << std::endl;
	Channel<FiniteField<2>> channel2(errorRate, vector);
	channel2.Simulate();
	std::cout << channel2.GetErrorCount() << " of " << channel2.GetInput().Size() << " errors made in channel." << std::endl;
	Differance(vector.ToText(), channel2.GetOutput().ToText());
}

void Scenario3(double errorRate)
{
	std::cin.ignore(256, '\n');
	std::cout << "Enter BMP image absoulte path: ";
	std::string path;
	std::cin >> path;
	int width, height, n;
	uint8_t* image = stbi_load(path.c_str(), &width, &height, &n, 0);
	if (image)
	{
		Vector<FiniteField<2>> vector(image, width * height * n);

		std::cout << "--- with encoding ---" << std::endl;

		Encoder encoder(Vector<FiniteField<2>>({ ZERO, ZERO, ZERO, ZERO, ZERO, ZERO }));
		encoder.Encode(vector);

		Channel<FiniteField<2>> channel(errorRate, encoder.GetOutput());
		channel.Simulate();
		std::cout << channel.GetErrorCount() << " of " << channel.GetInput().Size() << " errors made in channel." << std::endl;

		Decoder decoder(Vector<FiniteField<2>>({ ZERO, ZERO, ZERO, ZERO, ZERO, ZERO }));
		decoder.Decode(channel.GetOutput());

		stbi_write_bmp("WithEncoding.bmp", width, height, n, decoder.GetTrueOutput().ToBytes().data());

		std::cout << std::endl;

		std::cout << "--- without encoding ---" << std::endl;
		Channel<FiniteField<2>> channel2(errorRate, vector);
		channel2.Simulate();
		std::cout << channel2.GetErrorCount() << " of " << channel2.GetInput().Size() << " errors made in channel." << std::endl;

		stbi_write_bmp("WithoutEncoding.bmp", width, height, n, channel2.GetOutput().ToBytes().data());
		std::cout << "Done!" << std::endl;
	}
	else
	{
		std::cout << "Image (" << path << ") not found!" << std::endl;
	}
	stbi_image_free(image);
	std::cin.get();
}

void ChangeErrorRate(double& errorRate)
{
	std::cin.ignore(256, '\n');
	std::cout << "Enter new error rate: ";
	std::cin >> errorRate;
}

void Differance(const std::string& left, const std::string& right)
{
	uint32_t errorCount = 0;
	std::cout << "------------Output-------------" << std::endl;
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
	std::cout << "------------------------------" << std::endl;
	std::cout << "Errors made: " << errorCount << std::endl;
}

void Differance(const Vector<FiniteField<2>>& left, const Vector<FiniteField<2>>& right)
{
	uint32_t errorCount = 0;
	for (unsigned i = 0; i < left.Size(); i++)
	{
		if (i % 4 == 0 && i != 0)
		{
			ColorPrinter::Print(ColorPrinter::White, "%s", " ");
		}
		if (left[i] != right[i])
		{
			ColorPrinter::Print(ColorPrinter::Red, "%d", right[i].GetValue());
			errorCount++;
		}
		else
		{
			ColorPrinter::Print(ColorPrinter::White, "%d", right[i].GetValue());
		}
	}
	std::cout << std::endl;
	std::cout << "Errors made: " << errorCount << std::endl;
}