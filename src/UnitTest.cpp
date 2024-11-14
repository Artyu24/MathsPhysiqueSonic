#include "include/UnitTest.h"

#include "include/Vector3.h"
#include "include/Matrix.h"
#include "iostream"
#include "cassert"
#include "include/Quaternion.h"

void UnitTest::LaunchTest() const
{
	Vector3Test();
	MatrixTest();
	QuaternionTest();
}

bool UnitTest::FloatingPointTolerance(float testValue, float refValue, float tolerance) const
{
	return testValue <= refValue + tolerance && testValue >= refValue - tolerance;
}

bool UnitTest::FloatingPointTolerance(std::vector<float> testValue, std::vector<float> refValue, float tolerance) const
{
	for (size_t i = 0; i < testValue.size(); i++)
	{
		if (!(testValue[i] <= refValue[i] + tolerance && testValue[i] >= refValue[i] - tolerance))
			return false;
	}

	return true;
}

//Because our Vector3 class is a template, we will test it with float Vector
void UnitTest::Vector3Test() const
{
	std::cout << "Unit Test Vector3 : Start" << std::endl;

	//Vector Calculation
	assert(Vector3f(3.f, 2.f, 5.f) + Vector3f(6.f, 1.f, 3.f) == Vector3f(9.f, 3.f, 8.f));
	assert(Vector3f(3.f, 2.f, 5.f) - Vector3f(6.f, 1.f, 3.f) == Vector3f(-3.f, 1.f, 2.f));
	assert(Vector3f(3.f, 2.f, 5.f) * Vector3f(6.f, 1.f, 3.f) == Vector3f(18.f, 2.f, 15.f));
	assert(Vector3f(3.f, 2.f, 6.f) / Vector3f(6.f, 1.f, 3.f) == Vector3f(0.5f, 2.f, 2.f));

	Vector3f vec;

	//Vector Calculation by reference
	vec = { 3.f, 2.f, 5.f };
	vec += Vector3f(6.f, 1.f, 3.f);
	assert(vec == Vector3f(9.f, 3.f, 8.f));
	vec = { 3.f, 2.f, 5.f };
	vec -= Vector3f(6.f, 1.f, 3.f);
	assert(vec == Vector3f(-3.f, 1.f, 2.f));
	vec = { 3.f, 2.f, 5.f };
	vec *= Vector3f(6.f, 1.f, 3.f);
	assert(vec == Vector3f(18.f, 2.f, 15.f));
	vec = { 3.f, 2.f, 6.f };
	vec /= Vector3f(6.f, 1.f, 3.f);
	assert(vec == Vector3f(0.5f, 2.f, 2.f));

	//Conditions
	assert(Vector3f(3.f, 2.f, 6.f) == Vector3f(5.f, 4.f, 8.f) == false);
	assert(Vector3f(3.f, 2.f, 6.f) == Vector3f(3.f, 2.f, 6.f) == true);
	assert(Vector3f(3.f, 2.f, 6.f) != Vector3f(5.f, 4.f, 8.f) == true);
	assert(Vector3f(3.f, 2.f, 6.f) != Vector3f(3.f, 2.f, 6.f) == false);

	//Scalar Calculation
	assert(Vector3f(3.f, 2.f, 6.f) + 2 == Vector3f(5.f, 4.f, 8.f));
	assert(Vector3f(3.f, 2.f, 6.f) - 2 == Vector3f(1.f, 0.f, 4.f));
	assert(Vector3f(3.f, 2.f, 6.f) * 2 == Vector3f(6.f, 4.f, 12.f));
	assert(Vector3f(3.f, 2.f, 6.f) / 2 == Vector3f(1.5f, 1.f, 3.f));

	//Scalar Calculation by reference
	vec = { 3.f, 2.f, 6.f };
	vec += 2;
	assert(vec == Vector3f(5.f, 4.f, 8.f));
	vec = { 3.f, 2.f, 6.f };
	vec -= 2;
	assert(vec == Vector3f(1.f, 0.f, 4.f));
	vec = { 3.f, 2.f, 6.f };
	vec *= 2;
	assert(vec == Vector3f(6.f, 4.f, 12.f));
	vec = { 3.f, 2.f, 6.f };
	vec /= 2;
	assert(vec == Vector3f(1.5f, 1.f, 3.f));

	//Negatif Vector
	assert(-Vector3f(3.f, 2.f, 6.f) == Vector3f(-3.f, -2.f, -6.f));

	//Lenght
	assert(Vector3f(3.f, 2.f, 6.f).Length() == 7);
	assert(Vector3f(3.f, 2.f, 6.f).SquaredLength() == 49);

	//Normalize
	//assert(Vector3f(3.f, 2.f, 6.f).Normalize());

	//Product
	assert(Vector3f(3.f, 2.f, 6.f).DotProduct(Vector3f(6.f, 1.f, 3.f)) == 38);
	assert(Vector3f(3.f, 2.f, 6.f).CrossProduct(Vector3f(6.f, 1.f, 3.f)) == Vector3f(0.f, 27.f, -9.f));

	std::cout << "Unit Test Vector3 : Confirm" << std::endl;
}

void UnitTest::MatrixTest() const
{
	std::cout << "Unit Test Matrix : Start" << std::endl;

	//Constructor Test
	Matrix m1(3, 3);
	assert(m1.NbLines() == 3);
	assert(m1.NbColumns() == 3);

	m1 = Matrix(2, 2, std::vector<float>
	{
		1, 2,
		3, 4
	});
	assert(m1.Get(0, 0) == 1);
	assert(m1.Get(0, 1) == 2);
	assert(m1.Get(1, 0) == 3);
	assert(m1.Get(1, 1) == 4);

	//Modification Test
	m1 = Matrix(2, 2);
	m1.Get(0, 0) = 1;
	m1.Get(0, 1) = 2;
	m1.Get(1, 0) = 3;
	m1.Get(1, 1) = 4;
	assert(m1.Get(0, 0) == 1);
	assert(m1.Get(0, 1) == 2);
	assert(m1.Get(1, 0) == 3);
	assert(m1.Get(1, 1) == 4);

	//Copy Test
	m1 = Matrix(2, 2, std::vector<float>
	{
		1, 2,
		3, 4
	});
	Matrix m2(m1);
	m2.Get(0, 0) = 23;
	assert(m1.Get(0, 0) == 1);
	assert(m2.Get(0, 0) == 23);
	assert(m1.Get(0, 1) == 2);
	assert(m2.Get(0, 1) == 2);

	//Identity
	m1 = Matrix::Identity(2);
	std::vector<float> vTest{ 1.f, 0.f, 0.f, 1.f };
	assert(m1.ToArray2D() == vTest);

	m2 = Matrix(3, 2);
	assert(m1.IsIdentity() == true);
	assert(m2.IsIdentity() == false);

	//Scalar Multiplication
	m1 = Matrix(2, 2, std::vector<float>
	{
		1, 2,
		3, 4
	});
	m2 = m1 * 2;
	vTest = { 2.f, 4.f, 6.f, 8.f };
	assert(m2.ToArray2D() == vTest);

	m1.Multiply(2);
	assert(m1.ToArray2D() == vTest);

	//Addition
	m1 = Matrix(2, 2, std::vector<float>
	{
		1, 2,
		3, 4
	});

	m2 = Matrix(2, 2, std::vector<float>
	{
		5, 6,
		7, 8
	});

	Matrix m3 = m1 + m2;

	vTest = { 6.f, 8.f, 10.f, 12.f };
	assert(m3.ToArray2D() == vTest);

	//Substract
	m1 = Matrix(2, 2, std::vector<float>
	{
		5, 6,
		7, 8
	});

	m2 = Matrix(2, 2, std::vector<float>
	{
		1, 2,
		3, 4
	});

	m3 = m1 - m2;

	vTest = { 4.f, 4.f, 4.f, 4.f };
	assert(m3.ToArray2D() == vTest);

	//Matrice Multiplication
	m1 = Matrix(4, 2, std::vector<float>
	{
		1,4,
		2,2,
		7,6,
		23,1
	});

	m2 = Matrix(2, 3, std::vector<float>
	{
		8,5,2,
		3,1,2
	});

	m3 = m1 * m2;
	vTest = { 20,9,10,22,12,8,74,41,26,187,116,48 };
	assert(m3.ToArray2D() == vTest);

	//Transpose
	m1 = Matrix(2, 3, std::vector<float>
	{
		1, 2, 3,
		4, 5, 6
	});
	m1 = Matrix::Transpose(m1);

	vTest = { 1, 4, 2, 5, 3, 6};
	assert(m1.ToArray2D() == vTest);

	//Swap Line / Column
	m1 = Matrix(3, 3, std::vector<float>
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	});
	Matrix::SwapLines(m1, 0, 2);
	vTest = { 7, 8, 9, 4, 5, 6, 1, 2, 3 };

	assert(m1.ToArray2D() == vTest);

	m1 = Matrix(3, 3, std::vector<float>
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	});
	Matrix::SwapColumns(m1, 0, 1);
	vTest = { 2, 1, 3, 5, 4, 6, 8, 7, 9 };

	assert(m1.ToArray2D() == vTest);

	//Multiply Line / Column
	m1 = Matrix(3, 3, std::vector<float>
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	});
	Matrix::MultiplyLine(m1, 1, 2);
	vTest = { 1, 2, 3, 8, 10, 12, 7, 8, 9 };

	assert(m1.ToArray2D() == vTest);

	m1 = Matrix(3, 3, std::vector<float>
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	});
	Matrix::MultiplyColumn(m1, 0, 2);
	vTest = { 2, 2, 3, 8, 5, 6, 14, 8, 9 };

	assert(m1.ToArray2D() == vTest);

	//Add Line / Column to another
	m1 = Matrix(3, 3, std::vector<float>
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	});
	Matrix::AddLineToAnother(m1, 1, 0, 2);
	vTest = { 9, 12, 15, 4, 5, 6, 7, 8, 9 };

	assert(m1.ToArray2D() == vTest);

	m1 = Matrix(3, 3, std::vector<float>
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	});
	Matrix::AddColumnToAnother(m1, 1, 0, 2);
	vTest = { 5, 2, 3, 14, 5, 6, 23, 8, 9 };

	assert(m1.ToArray2D() == vTest);

	//Generate Augmented Matrix
	m1 = Matrix(3, 3, std::vector<float>
	{
		3, 2, -3,
		4, -3, 6,
		1, 0, -1
	});

	m2 = Matrix(3, 1, std::vector<float>
	{
		-13,
		7,
		-5
	});

	m3 = Matrix::GenerateAugmentedMatrix(m1, m2);
	vTest = { 3,2,-3,-13,4,-3,6,7,1,0,-1,-5 };

	assert(m3.ToArray2D() == vTest);

	//Split Matrix
	m1 = Matrix(3, 4, std::vector<float>
	{
		3, 2, -3, 0,
		4, -3, 6, 0,
		1, 0, -1, 0
	});
	std::tuple<Matrix, Matrix> mtuple = m1.Split(2);

	vTest = { 3,2,-3, 4,-3,6,1,0,-1};
	assert(std::get<0>(mtuple).ToArray2D() == vTest);

	vTest = { 0,0,0};
	assert(std::get<1>(mtuple).ToArray2D() == vTest);

	//Apply Row Reduction
	m1 = Matrix(3, 3, std::vector<float>
	{
		3, 2, -3,
		4, -3, 6,
		1, 0, -1
	});
	m2 = Matrix(3, 1, std::vector<float>
	{
		-13,
		7,
		-5
	});
	mtuple = Matrix::ApplyMatrixRowReduction(m1, m2);

	vTest = { 1.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,1.f };
	assert(FloatingPointTolerance(std::get<0>(mtuple).ToArray2D(), vTest, 0.001f));

	vTest = { -2,1,3 };
	assert(FloatingPointTolerance(std::get<1>(mtuple).ToArray2D(), vTest, 0.001f));

	//Invert Matrix
	m1 = Matrix(2, 2, std::vector<float>
	{
		1, 2,
		3, 4
	});

	m1 = Matrix::InvertByRowReduction(m1);
	vTest = { -2.f, 1.f, 1.5f, -0.5f };

	assert(FloatingPointTolerance(m1.ToArray2D(), vTest, 0.001f));

	//Sub Matrix
	m1 = Matrix(3, 3, std::vector<float>
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	});
	m2 = m1.SubMatrix(0, 0);
	vTest = { 5, 6, 8, 9 };

	assert(m2.ToArray2D() == vTest);

	m2 = m1.SubMatrix(1, 2);
	vTest = { 1, 2, 7, 8 };

	assert(m2.ToArray2D() == vTest);

	//Determinant
	m1 = Matrix(2, 2, std::vector<float>
	{
		1, 2,
		3, 4
	});
	float det = Matrix::Determinant(m1);
	assert(FloatingPointTolerance(det, -2.f, 0.001f));

	m1 = Matrix::Identity(3);
	det = Matrix::Determinant(m1);
	assert(FloatingPointTolerance(det, 1.f, 0.001f));

	//Adjugate
	m1 = Matrix(2, 2, std::vector<float>
	{
		1, 2,
		3, 4
	});
	m2 = m1.Adjugate();
	vTest = { 4.f, -2.f, -3.f, 1.f };
	assert(FloatingPointTolerance(m2.ToArray2D(), vTest, 0.001f));

	m1 = Matrix(3, 3, std::vector<float>
	{
		1, 0, 5,
		2, 1, 6,
		3, 4, 0
	});
	m2 = m1.Adjugate();
	vTest = { -24.f, 20.f, -5.f, 18.f, -15.f, 4.f, 5.f, -4.f, 1.f };
	assert(FloatingPointTolerance(m2.ToArray2D(), vTest, 0.001f));

	//Invert Matrix by Determinant
	m1 = Matrix(2, 2, std::vector<float>
	{
		1, 2,
		3, 4
	});

	m1 = Matrix::InvertByDeterminant(m1);
	vTest = { -2.f, 1.f, 1.5f, -0.5f };

	assert(FloatingPointTolerance(m1.ToArray2D(), vTest, 0.001f));

	std::cout << "Unit Test Matrix : Confirm" << std::endl;
}

void UnitTest::QuaternionTest() const
{
	std::cout << "Unit Test Quaternion : Start" << std::endl;

	//Constructor Test
	Quaternion q(1.f, 2.f, 3.f, 4.f);
	assert(q.W() == 1.f);
	assert(q.X() == 2.f);
	assert(q.Y() == 3.f);
	assert(q.Z() == 4.f);

	q = Quaternion(Vector3f(1.f, 2.f, 3.f));
	assert(q.W() == 0.f);
	assert(q.X() == 1.f);
	assert(q.Y() == 2.f);
	assert(q.Z() == 3.f);

	//Identity
	q = Quaternion::Identity();
	assert(q.W() == 1.f);
	assert(q.X() == 0.f);
	assert(q.Y() == 0.f);
	assert(q.Z() == 0.f);

	//Rotation Quaternion
	//X Axis
	q = Quaternion::GetRotationQuaternion(90.f, Vector3f(1.f, 0.f, 0.f));
	assert(FloatingPointTolerance(q.W(), 0.71f, 0.01f));
	assert(FloatingPointTolerance(q.X(), 0.71f, 0.01f));
	assert(FloatingPointTolerance(q.Y(), 0.f, 0.01f));
	assert(FloatingPointTolerance(q.Z(), 0.f, 0.01f));
	//Y Axis
	q = Quaternion::GetRotationQuaternion(90.f, Vector3f(0.f, 1.f, 0.f));
	assert(FloatingPointTolerance(q.W(), 0.71f, 0.01f));
	assert(FloatingPointTolerance(q.X(), 0.f, 0.01f));
	assert(FloatingPointTolerance(q.Y(), 0.71f, 0.01f));
	assert(FloatingPointTolerance(q.Z(), 0.f, 0.01f));
	//Z Axis
	q = Quaternion::GetRotationQuaternion(90.f, Vector3f(0.f, 0.f, 1.f));
	assert(FloatingPointTolerance(q.W(), 0.71f, 0.01f));
	assert(FloatingPointTolerance(q.X(), 0.f, 0.01f));
	assert(FloatingPointTolerance(q.Y(), 0.f, 0.01f));
	assert(FloatingPointTolerance(q.Z(), 0.71f, 0.01f));

	//Multiplication
	Quaternion rotationXAxis = Quaternion::GetRotationQuaternion(90.f, Vector3f(1.f, 0.f, 0.f));
	Quaternion rotationYAxis = Quaternion::GetRotationQuaternion(90.f, Vector3f(0.f, 1.f, 0.f));
	q = rotationXAxis * rotationYAxis;
	assert(FloatingPointTolerance(q.W(), 0.5f, 0.01f));
	assert(FloatingPointTolerance(q.X(), 0.5f, 0.01f));
	assert(FloatingPointTolerance(q.Y(), 0.5f, 0.01f));
	assert(FloatingPointTolerance(q.Z(), 0.5f, 0.01f));
	q = rotationYAxis * rotationXAxis;
	assert(FloatingPointTolerance(q.W(), 0.5f, 0.01f));
	assert(FloatingPointTolerance(q.X(), 0.5f, 0.01f));
	assert(FloatingPointTolerance(q.Y(), 0.5f, 0.01f));
	assert(FloatingPointTolerance(q.Z(), -0.5f, 0.01f));

	std::cout << "Unit Test Quaternion : Confirm" << std::endl;
}