#include <iostream>
#include "../Include/FiniteBody.h"
#include "../Include/Vector.h"

using namespace TomasMo;

int main()
{
	const FiniteBody one = FiniteBody::One();
	const FiniteBody zero = FiniteBody::Zero();
	FiniteBody rez = FiniteBody::Zero();
	rez += one;
	rez += one;
	rez += zero;
	rez += one;
	std::cout << rez << std::endl;
	std::cout << zero + one + F1 + one + zero + one << std::endl;
	Vector vector ({ F1, F0, F1, F1, F1, F0 });
	Vector vector2({ F0, F1 });
	std::cout << vector << std::endl;
	//vector[1] += F1;
	vector += vector2;
	std::cout << vector << std::endl;
	std::cin.get();
	return 0;
}