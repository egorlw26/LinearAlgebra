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

		TEST_METHOD(Matrix2x2DeterminantTest)
		{
			Matrix<int> a(2, 2);
			a[0][0] = 3;
			a[0][1] = 2;
			a[1][0] = 5;
			a[1][1] = 10;

			double expected = 20;
			auto determinant = a.determinant();

			Assert::AreEqual(expected, determinant);
		}

		TEST_METHOD(Matrix3x3DeterminantTest)
		{
			Matrix<int> a(3, 3);
			a[0][0] = 3;
			a[0][1] = 2;
			a[0][2] = 6;
			a[1][0] = 5;
			a[1][1] = 10;
			a[1][2] = 8;
			a[2][0] = 2;
			a[2][1] = 3;
			a[2][2] = 5;

			double expected = 30;
			double result = a.determinant();

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(Matrix3x3DeterminantTest2)
		{
			Matrix<int> a(3, 3);
			a[0][0] = 2;
			a[0][1] = -5;
			a[0][2] = 18;

			a[1][0] = 2;
			a[1][1] = -13;
			a[1][2] = 9;

			a[2][0] = 0;
			a[2][1] = 10;
			a[2][2] = 12;

			double expected = -12;
			double result = a.determinant();

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(Matrix3x3DeterminantTest3)
		{
			Matrix<int> a(3, 3);
			a[0][0] = 3;
			a[0][1] = -5;
			a[0][2] = 18;

			a[1][0] = 6;
			a[1][1] = -13;
			a[1][2] = 9;

			a[2][0] = 3;
			a[2][1] = 10;
			a[2][2] = 12;

			double expected = 1269;
			double result = a.determinant();

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(Matrix3x3DeterminantTest4)
		{
			Matrix<int> a(3, 3);
			a[0][0] = 2;
			a[0][1] = 3;
			a[0][2] = 18;

			a[1][0] = 2;
			a[1][1] = 6;
			a[1][2] = 9;

			a[2][0] = 0;
			a[2][1] = 3;
			a[2][2] = 12;

			double expected = 126;
			double result = a.determinant();

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(Matrix3x3DeterminantTest5)
		{
			Matrix<int> a(3, 3);
			a[0][0] = 2;
			a[0][1] = 3;
			a[0][2] = -5;

			a[1][0] = 2;
			a[1][1] = 6;
			a[1][2] = -13;

			a[2][0] = 0;
			a[2][1] = 3;
			a[2][2] = 10;

			double expected = 108;
			double result = a.determinant();

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(MatrixRemoveRowAndColumnTest)
		{
			Matrix<int> a(3, 3);
			a[0][0] = 3;
			a[0][1] = 2;
			a[0][2] = 6;
			a[1][0] = 5;
			a[1][1] = 10;
			a[1][2] = 8;
			a[2][0] = 2;
			a[2][1] = 3;
			a[2][2] = 5;

			Matrix<int> test = a.removeRowAndColumn(0, 1);

			Matrix<int> expected(2, 2);
			expected[0][0] = a[1][0];
			expected[0][1] = a[1][2];
			expected[1][0] = a[2][0];
			expected[1][1] = a[2][2];

			bool res = (test == expected);

			Assert::IsTrue(res);
		}

		TEST_METHOD(MatrixRemoveRowAndColumnTest2)
		{
			Matrix<int> a(4, 4);
			a[0][0] = 2;
			a[0][1] = 3;
			a[0][2] = 4;
			a[0][3] = 18;

			a[1][0] = 2;
			a[1][1] = 3;
			a[1][2] = -5;
			a[1][3] = 18;

			a[2][0] = 2;
			a[2][1] = 6;
			a[2][2] = -13;
			a[2][3] = 9;

			a[3][0] = 0;
			a[3][1] = 3;
			a[3][2] = 10;
			a[3][3] = 12;

			Matrix<int> exp(3, 3);
			exp[0][0] = 2;
			exp[0][1] = -5;
			exp[0][2] = 18;

			exp[1][0] = 2;
			exp[1][1] = -13;
			exp[1][2] = 9;

			exp[2][0] = 0;
			exp[2][1] = 10;
			exp[2][2] = 12;

			auto test = a.removeRowAndColumn(0, 1);

			Logger::WriteMessage(test.toString().c_str());

			bool res = (exp == test);

			Assert::IsTrue(res);
		}

		TEST_METHOD(MatrixRemoveRowAndColumnTest3)
		{
			Matrix<int> a(4, 4);
			a[0][0] = 2;
			a[0][1] = 3;
			a[0][2] = 4;
			a[0][3] = 18;

			a[1][0] = 2;
			a[1][1] = 3;
			a[1][2] = -5;
			a[1][3] = 18;

			a[2][0] = 2;
			a[2][1] = 6;
			a[2][2] = -13;
			a[2][3] = 9;

			a[3][0] = 0;
			a[3][1] = 3;
			a[3][2] = 10;
			a[3][3] = 12;

			Matrix<int> exp(3, 3);
			exp[0][0] = 2;
			exp[0][1] = 3;
			exp[0][2] = 18;

			exp[1][0] = 2;
			exp[1][1] = 6;
			exp[1][2] = 9;

			exp[2][0] = 0;
			exp[2][1] = 3;
			exp[2][2] = 12;

			auto test = a.removeRowAndColumn(0, 2);
			bool res = (exp == test);

			Assert::IsTrue(res);
		}

		TEST_METHOD(MatrixRemoveRowAndColumnTest4)
		{
			Matrix<int> a(4, 4);
			a[0][0] = 2;
			a[0][1] = 3;
			a[0][2] = 4;
			a[0][3] = 18;

			a[1][0] = 2;
			a[1][1] = 3;
			a[1][2] = -5;
			a[1][3] = 18;

			a[2][0] = 2;
			a[2][1] = 6;
			a[2][2] = -13;
			a[2][3] = 9;

			a[3][0] = 0;
			a[3][1] = 3;
			a[3][2] = 10;
			a[3][3] = 12;

			Matrix<int> exp(3, 3);
			exp[0][0] = 2;
			exp[0][1] = 3;
			exp[0][2] = -5;

			exp[1][0] = 2;
			exp[1][1] = 6;
			exp[1][2] = -13;

			exp[2][0] = 0;
			exp[2][1] = 3;
			exp[2][2] = 10;

			auto test = a.removeRowAndColumn(0, 3);
			bool res = (exp == test);

			Assert::IsTrue(res);
		}

		TEST_METHOD(Matrix4x4DeterminantTest1)
		{
			Matrix<int> a(4, 4);
			a[0][0] = 2;
			a[1][1] = 2;
			a[2][2] = 2;
			a[3][3] = 2;

			double expected = 16;

			Assert::AreEqual(expected, a.determinant());
		}

		TEST_METHOD(Matrix4x4DeterminantTest2)
		{
			Matrix<int> a(4, 4);
			a[0][0] = 2;
			a[0][1] = 3;
			a[0][2] = 4;
			a[0][3] = 18;

			a[1][0] = 2;
			a[1][1] = 3;
			a[1][2] = -5;
			a[1][3] = 18;

			a[2][0] = 2;
			a[2][1] = 6;
			a[2][2] = -13;
			a[2][3] = 9;

			a[3][0] = 0;
			a[3][1] = 3;
			a[3][2] = 10;
			a[3][3] = 12;

			double expected = 1134;

			Assert::AreEqual(expected, a.determinant());
		}
	};
}
