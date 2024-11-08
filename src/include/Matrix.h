#pragma once

#include <string>
#include <tuple>
#include <vector>

#include "Vector3.h"

class Matrix
{
public:
	Matrix();
	Matrix(size_t line, size_t column);
	Matrix(size_t line, size_t column, std::vector<float> vec);
	Matrix(const Matrix& m);

	float& Get(size_t line, size_t column);
	float Get(size_t line, size_t column) const;

	size_t NbLines() const;
	size_t NbColumns() const;

	std::vector<float> ToArray2D();
	std::string ToString();

	static Matrix Identity(const size_t& size);
	bool IsIdentity();

	static Matrix Rotate(float degreeAngle);
	static Matrix Scale(const Vector3f& scale);
	static Matrix Translate(const Vector3f& translation);
	
	void Add(const Matrix& m);
	void Multiply(const float& v);
	Matrix Multiply(const Matrix& m) const;

	static Matrix Add(const Matrix& m1, const Matrix& m2);
	static Matrix Multiply(const Matrix& m, const float& v);
	static Matrix Multiply(const Matrix& m1, const Matrix& m2);

	Matrix Transpose() const;
	static Matrix Transpose(const Matrix& m);

	std::tuple<Matrix, Matrix> Split(const int& l);

	static Matrix GenerateAugmentedMatrix(const Matrix& m1, const Matrix& m2);
	static void SwapLines(Matrix& m, int l1, int l2);
	static void SwapColumns(Matrix& m, int c1, int c2);
	static void MultiplyLine(Matrix& m, int l, float multiplier);
	static void MultiplyColumn(Matrix& m, int c, float multiplier);
	static void AddLineToAnother(Matrix& m, int lineMultiplier, int l, float multiplier);
	static void AddColumnToAnother(Matrix& m, int columnMultiplier, int c, float multiplier);
	static int GetBestLineValue(const Matrix& m, int l);

	static std::tuple<Matrix, Matrix> ApplyMatrixRowReduction(const Matrix& m1, const Matrix& m2, bool inverse = false);
	Matrix InvertByRowReduction() const;
	static Matrix InvertByRowReduction(const Matrix& matrix);

	Matrix SubMatrix(size_t line, size_t column) const;
	static Matrix SubMatrix(const Matrix& m, size_t line, size_t column);

	static float Determinant(const Matrix& m);
	Matrix Adjugate() const;
	static Matrix Adjugate(const Matrix& m);
	Matrix InvertByDeterminant() const;
	static Matrix InvertByDeterminant(const Matrix& m);

	Matrix operator-() const;

private:
	size_t m_line;
	size_t m_column;
	std::vector<float> m_matrix;
};

Matrix operator+(const Matrix& m1, const Matrix& m2);
Matrix operator-(const Matrix& m1, const Matrix& m2);

Matrix operator*(const Matrix& m, float a);
Matrix operator*(float a, const Matrix& m);
Matrix operator*(const Matrix& m1, const Matrix& m2);

Vector3f operator*(const Vector3f& v, const Matrix& m);
Vector3f operator*(const Matrix& m, const Vector3f& v);
