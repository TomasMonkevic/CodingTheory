#include <iostream>
#include "../Include/FiniteField.h"
#include "../Include/Vector.h"

using namespace TomasMo;

int main()
{
	const FiniteField<2> one = FiniteField<2>::One();
	const FiniteField<2> zero = FiniteField<2>::Zero();;
	FiniteField<2> rez = zero;
	std::cout << rez << std::endl;
	rez += one;
	std::cout << rez << std::endl;
	rez += one;
	std::cout << rez << std::endl;
	rez += zero;
	std::cout << rez << std::endl;
	rez += one;
	std::cout << rez << std::endl;
	std::cout << std::endl;
	std::cout << zero + one + one + one + zero << std::endl;
	Vector<FiniteField<2>> vector ({ one, zero, one, one, one, zero });
	Vector<FiniteField<2>> vector2({ zero, one });
	std::cout << vector << std::endl;
	vector[5] += one;
	vector += vector2;
	std::cout << vector << std::endl;
	FiniteField<5> tris(3);
	FiniteField<5> keturi(4);
	std::cout << tris << " + " << keturi << " = "<<tris+keturi;
	std::cin.get();
	return 0;
}