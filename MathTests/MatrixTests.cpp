#include "pch.h"
#include "CppUnitTest.h"
#include "../Math/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTests
{
	TEST_CLASS(MatrixTests)
	{
	public:
		const double tolerance = 1e-3;
		TEST_METHOD(SimpleTest)
		{
			Matrix<int> a(3, 2);
			Assert::AreEqual(a[0][0], 0);
		}

		TEST_METHOD(MatrixIntXDoubleTest)
		{
			Matrix<int> a(2, 2);
			a[0][0] = 1;
			a[0][1] = 2;
			a[1][0] = 3;
			a[1][1] = 4;

			double value = 10;

			auto res = a * value;

			Assert::AreEqual(20.0, res[0][1]);
		}

		TEST_METHOD(DoubleXMatrixIntTest)
		{
			Matrix<int> a(2, 2);
			a[0][0] = 1;
			a[0][1] = 2;
			a[1][0] = 3;
			a[1][1] = 4;

			double value = 10;

			auto res = value * a;

			Assert::AreEqual(30.0, res[1][0]);
		}

		TEST_METHOD(MatrixSumTest)
		{
			Matrix<int> a(2, 2);
			a[0][0] = 1;
			a[0][1] = 2;
			a[1][0] = 3;
			a[1][1] = 4;

			Matrix<double> b(2, 2);
			b[0][0] = 2.5;
			b[0][1] = 3.0;
			b[1][0] = 4.7;
			b[1][1] = 5;

			auto res = a + b;

			Assert::AreEqual(3.5, res[0][0]);
		}

		TEST_METHOD(MatrixSubtractTest)
		{
			Matrix<int> a(2, 2);
			a[0][0] = 1;
			a[0][1] = 2;
			a[1][0] = 3;
			a[1][1] = 4;

			Matrix<double> b(2, 2);
			b[0][0] = 2.5;
			b[0][1] = 3.0;
			b[1][0] = 4.7;
			b[1][1] = 5;

			auto res = b - a;

			Assert::IsTrue(std::fabs(1.5 - res[0][0]) < tolerance);
			Assert::IsTrue(std::fabs(1.0 - res[0][1]) < tolerance);
			Assert::IsTrue(std::fabs(1.7 - res[1][0]) < tolerance);
			Assert::AreEqual(1, (int)res[1][1]);
		}

		TEST_METHOD(MatrixMultiplyMethod)
		{
			Matrix<int> a(2, 2);
			a[0][0] = 1;
			a[0][1] = 2;
			a[1][0] = 3;
			a[1][1] = 4;

			Matrix<double> b(2, 2);
			b[0][0] = 2.5;
			b[0][1] = 3.0;
			b[1][0] = 4.7;
			b[1][1] = 5;

			auto res = a * b;


			Assert::IsTrue(fabs(11.9 - res[0][0]) < tolerance);
		}

		TEST_METHOD(AreMatrixEqual)
		{
			Matrix<int> a(2, 2);
			a[0][0] = 1;
			a[0][1] = 2;
			a[1][0] = 3;
			a[1][1] = 4;

			Matrix<int> b(2, 2);
			b[0][0] = 1;
			b[0][1] = 2;
			b[1][0] = 3;
			b[1][1] = 4;

			bool res = (a == b);
			Assert::IsTrue(res);
		}

		TEST_METHOD(IdentityMatrixTest)
		{
			Matrix<int> test = Matrix<int>::createIdentity(2);

			Matrix<int> expected(2, 2);
			expected[0][0] = 1;
			expected[1][1] = 1;

			bool res = (test == expected);

			Assert::IsTrue(res);
		}
	};
}
