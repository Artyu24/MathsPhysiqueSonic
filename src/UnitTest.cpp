#include "include/UnitTest.h"

#include "include/Vector3.h"
#include "iostream"
#include "cassert"

void UnitTest::LaunchTest() const
{
	Vector3Test();
}

//Because our Vector3 class is a template, we will test it with float Vector
void UnitTest::Vector3Test() const
{
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
