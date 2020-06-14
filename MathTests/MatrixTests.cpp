#include "pch.h"
#include "CppUnitTest.h"
#include "../Math/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTests
{
	TEST_CLASS(MatrixTests)
	{
	public:
		
		TEST_METHOD(SimpleTest)
		{
			Matrix<int> a(3, 2);
			Assert::AreEqual(a[0][0], 0);
		}
	};
}
