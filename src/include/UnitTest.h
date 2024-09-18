#pragma once

class UnitTest
{
public:
	UnitTest() = default;
	~UnitTest() = default;

	void LaunchTest() const;

private:
	void Vector3Test() const;
};

