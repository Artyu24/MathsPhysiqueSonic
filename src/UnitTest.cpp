#include "include/UnitTest.h"

#include "include/Vector3.h"
#include "include/Matrix.h"
#include "iostream"
#include "cassert"

void UnitTest::LaunchTest() const
{
	Vector3Test();
	MatrixTest();
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
	Matrix m(3, 3);
	assert(m.NbLines() == 3);
	assert(m.NbColumns() == 3);

	m = Matrix(2, 2, std::vector<float>
	{
		1, 2,
		3, 4
	});
	assert(m.Get(0, 0) == 1);
	assert(m.Get(0, 1) == 2);
	assert(m.Get(1, 0) == 3);
	assert(m.Get(1, 1) == 4);

	//Modification Test
	m = Matrix(2, 2);
	m.Get(0, 0) = 1;
	m.Get(0, 1) = 2;
	m.Get(1, 0) = 3;
	m.Get(1, 1) = 4;
	assert(m.Get(0, 0) == 1);
	assert(m.Get(0, 1) == 2);
	assert(m.Get(1, 0) == 3);
	assert(m.Get(1, 1) == 4);

	//Copy Test
	m = Matrix(2, 2, std::vector<float>
	{
		1, 2,
		3, 4
	});
	Matrix m2(m);
	m2.Get(0, 0) = 23;
	assert(m.Get(0, 0) == 1);
	assert(m2.Get(0, 0) == 23);
	assert(m.Get(0, 1) == 2);
	assert(m2.Get(0, 1) == 2);

	//Identity
	m = Matrix::Identity(2);
	//assert(m.ToArray2D() == std::vector<float>{1.f, 0.f, 1.f, 0.f})

	std::cout << "Unit Test Matrix : Confirm" << std::endl;
}
