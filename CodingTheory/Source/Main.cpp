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
	std::cout << zero + one + one + one + zero + one << std::endl;
	Vector vector({ one, zero, one, one, one, zero });
	std::cout << vector << std::endl;
	std::cin.get();
	return 0;
}