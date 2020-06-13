#include "Matrix.h"
#include <iostream>

int main()
{
	//Just testing how it's working
	Matrix<int> a(3, 3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			a[i][j] = i + j;

	Matrix<int> b(a);

	Matrix<int> c = a * b;

	std::cout << c;

}