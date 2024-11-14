#pragma once
#include <vector>

class UnitTest
{
public:
	UnitTest() = default;
	~UnitTest() = default;

	void LaunchTest() const;

private:
	bool FloatingPointTolerance(float testValue, float refValue, float tolerance) const;
	bool FloatingPointTolerance(std::vector<float> testValue, std::vector<float> refValue, float tolerance) const;

	void Vector3Test() const;
	void MatrixTest() const;
	void QuaternionTest() const;
};

