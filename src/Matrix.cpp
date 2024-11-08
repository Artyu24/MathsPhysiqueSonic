#include "include/Matrix.h"

#include <stdexcept>

Matrix::Matrix() :
	Matrix(3, 3)
{
}
Matrix::Matrix(size_t line, size_t column) :
	m_line(line), m_column(column), m_matrix(std::vector<float>(line * column))
{
}
Matrix::Matrix(size_t line, size_t column, std::vector<float> vec)
{
	if(line * column != vec.size())
		throw std::runtime_error("Vector different than line * column");

	m_line = line;
	m_column = column;
	m_matrix = std::vector(vec);
}
Matrix::Matrix(const Matrix& m)
{
	m_line = m.m_line;
	m_column = m.m_column;
	m_matrix = std::vector(m.m_matrix);
}

float& Matrix::Get(size_t line, size_t column)
{
	return m_matrix[line * m_column + column];
}
float Matrix::Get(size_t line, size_t column) const
{
	return m_matrix[line * m_column + column];
}

size_t Matrix::NbLines() const
{
	return m_line;
}
size_t Matrix::NbColumns() const
{
	return m_column;
}

std::vector<float> Matrix::ToArray2D()
{
	return m_matrix;
}
std::string Matrix::ToString()
{
	std::string matrixString;

	for(int i = 0; i < m_line; i++)
	{
		matrixString += "[";

		for(int j = 0; j < m_column; j++)
		{
			matrixString += std::to_string(Get(i, j));

			if (j != m_column - 1)
				matrixString += ",";
		}

		matrixString += "]\n";
	}

	matrixString += "\n";

	return matrixString;
}

Matrix Matrix::Identity(const size_t& size)
{
	Matrix m(size, size);

	for (size_t i = 0; i < m.NbLines(); i++)
	{
		for (size_t j = 0; j < m.NbColumns(); j++)
		{
			if (i == j)
				m.Get(i, j) = 1;
			else
				m.Get(i, j) = 0;
		}
	}

	return m;
}
bool Matrix::IsIdentity()
{
	if (m_line != m_column)
		return false;

	for (size_t i = 0; i < m_line; i++)
	{
		for (size_t j = 0; j < m_column; j++)
		{
			if (i == j && Get(i, j) != 1.f)
				return false;

			if (i != j && Get(i, j) != 0.f)
				return false;
		}
	}

	return true;
}

//TODO REMAKE THIS FUNCTION WITH VECTOR 3
Matrix Matrix::Rotate(float degreeAngle)
{
	// Subtilité : on inverse la rotation car notre repère n'est pas mathématique: notre Y pointe vers le bas
	// ce qui rend nos rotations en sens horaire plutôt que anti-horaire
	float sinAngle = std::sin(-degreeAngle * DEG_TO_RAD);
	float cosAngle = std::cos(-degreeAngle * DEG_TO_RAD);

	return Matrix(3,3,{
		cosAngle, -sinAngle, 0.0f,
		sinAngle,  cosAngle, 0.0f,
		0.0f,          0.0f, 1.0f
		});
}

Matrix Matrix::Scale(const Vector3f& scale)
{
	return Matrix(3,3,{
		scale.x, 0.0f,    0.0f,
		0.0f,    scale.y, 0.0f,
		0.f,     0.0f,    1.0f
		});
}

Matrix Matrix::Translate(const Vector3f& translation)
{
	return Matrix(3,3,{
		1.0f, 0.0f, translation.x,
		0.0f, 1.0f, translation.y,
		0.0f, 0.0f, 1.0f,
		});
}
//TODO END HERE

void Matrix::Add(const Matrix& m)
{
	if (m_line != m.m_line || m_column != m.m_column)
		throw std::runtime_error("Addition error");

	for (size_t i = 0; i < m_line; i++)
	{
		for (size_t j = 0; j < m_column; j++)
		{
			Get(i, j) += m.Get(i, j);
		}
	}
}
void Matrix::Multiply(const float& v)
{
	for (size_t i = 0; i < m_line; i++)
	{
		for (size_t j = 0; j < m_column; j++)
		{
			Get(i, j) *= v;
		}
	}
}
Matrix Matrix::Multiply(const Matrix& m) const
{
	if (m_column != m.m_line )
		throw std::runtime_error("Multiply error");

	Matrix temp(m_line, m.m_column);
	for (size_t i = 0; i < temp.m_line; i++)
	{
		for (size_t j = 0; j < temp.m_column; j++)
		{
			for (size_t k = 0; k < m_column; k++)
			{
				temp.Get(i, j) += Get(i, k) * m.Get(k, j);
			}
		}
	}

	return temp;
}

Matrix Matrix::Add(const Matrix& m1, const Matrix& m2)
{
	Matrix temp(m1);
	temp.Add(m2);
	return temp;
}
Matrix Matrix::Multiply(const Matrix& m, const float& v)
{
	Matrix temp(m);
	temp.Multiply(v);
	return temp;
}
Matrix Matrix::Multiply(const Matrix& m1, const Matrix& m2)
{
	return m1.Multiply(m2);
}

Matrix Matrix::Transpose() const
{
	Matrix temp(m_column, m_line);

	for (size_t i = 0; i < temp.m_line; i++)
	{
		for (size_t j = 0; j < temp.m_column; j++)
		{
			temp.Get(i, j) = Get(j, i);
		}
	}

	return temp;
}
Matrix Matrix::Transpose(const Matrix& m)
{
	return m.Transpose();
}

std::tuple<Matrix, Matrix> Matrix::Split(const int& l)
{
	Matrix m1Temp(m_line, l + 1);
	Matrix m2Temp(m_line, m_column - (l + 1));

	for (size_t i = 0; i < m_line; i++)
	{
		for (size_t j = 0; j < m_column; j++)
		{
			if (j <= l)
				m1Temp.Get(i, j) = Get(i, j);
			else
				m2Temp.Get(i, j - (l + 1)) = Get(i, j);
		}
	}

	return std::make_tuple(m1Temp, m2Temp);
}

Matrix Matrix::GenerateAugmentedMatrix(const Matrix& m1, const Matrix& m2)
{
	Matrix temp(m1.m_line, m1.m_column + m2.m_column);

	for (size_t i = 0; i < temp.m_line; i++)
	{
		for (size_t j = 0; j < temp.m_column; j++)
		{
			if (j >= m1.m_column)
				temp.Get(i, j) = m2.Get(i, j - m1.m_column);
			else
				temp.Get(i, j) = m1.Get(i, j);
		}
	}

	return temp;
}
void Matrix::SwapLines(Matrix& m, int l1, int l2)
{
	for (size_t i = 0; i < m.NbColumns(); i++)
	{
		float save = m.Get(l1, i);
		m.Get(l1, i) = m.Get(l2, i);
		m.Get(l2, i) = save;
	}
}
void Matrix::SwapColumns(Matrix& m, int c1, int c2)
{
	for (size_t i = 0; i < m.NbLines(); i++)
	{
		float save = m.Get(i, c1);
		m.Get(i, c1) = m.Get(i, c2);
		m.Get(i, c2) = save;
	}
}
void Matrix::MultiplyLine(Matrix& m, int l, float multiplier)
{
	if (multiplier == 0)
		throw std::runtime_error("MatrixScalarZeroException");

	for (size_t i = 0; i < m.NbColumns(); i++)
	{
		m.Get(l, i) *= multiplier;
	}
}
void Matrix::MultiplyColumn(Matrix& m, int c, float multiplier)
{
	if (multiplier == 0)
		throw std::runtime_error("MatrixScalarZeroException");

	for (size_t i = 0; i < m.NbLines(); i++)
	{
		m.Get(i, c) *= multiplier;
	}
}
void Matrix::AddLineToAnother(Matrix& m, int lineMultiplier, int l, float multiplier)
{
	if (multiplier == 0)
		throw std::runtime_error("MatrixScalarZeroException");

	for (size_t i = 0; i < m.NbColumns(); i++)
	{
		m.Get(l, i) += m.Get(lineMultiplier, i) * multiplier;
	}
}
void Matrix::AddColumnToAnother(Matrix& m, int columnMultiplier, int c, float multiplier)
{
	if (multiplier == 0)
		throw std::runtime_error("MatrixScalarZeroException");

	for (size_t i = 0; i < m.NbLines(); i++)
	{
		m.Get(i, c) += m.Get(i, columnMultiplier) * multiplier;
	}
}
int Matrix::GetBestLineValue(const Matrix& m, int l)
{
	int bestL = l;

	for (size_t i = l; i < m.NbLines(); i++)
	{
		if (m.Get(i, l) > m.Get(bestL, l) && m.Get(i, l) != 0)
			bestL = i;
	}

	return bestL;
}

std::tuple<Matrix, Matrix> Matrix::ApplyMatrixRowReduction(const Matrix& m1, const Matrix& m2, bool inverse)
{
	if (m1.NbLines() != m1.NbColumns())
		throw std::runtime_error("MatrixInvertException");

	Matrix mAug = GenerateAugmentedMatrix(m1, m2);

	for (size_t a = 0; a < mAug.NbLines(); a++)
	{
		size_t i = a;
		size_t j = a;

		if (mAug.Get(i, j) == 0 && !inverse)
			continue;

		int k = GetBestLineValue(m1, i);

		if (mAug.Get(k, j) == 0 && inverse)
			throw std::runtime_error("MatrixInvertException");

		if (k != i)
			SwapLines(mAug, i, k);

		MultiplyLine(mAug, i, 1 / mAug.Get(i, j));

		for (size_t r = 0; r < mAug.NbLines(); r++)
		{
			if (r != i && mAug.Get(r, j) != 0)
				AddLineToAnother(mAug, i, r, -mAug.Get(r, j));
		}
	}

	return mAug.Split(m1.NbColumns() - 1);
}
Matrix Matrix::InvertByRowReduction() const
{
	std::tuple<Matrix, Matrix> result = ApplyMatrixRowReduction(*this, Identity(NbLines()), true);
	return std::get<1>(result);
}
Matrix Matrix::InvertByRowReduction(const Matrix& matrix)
{
	return matrix.InvertByRowReduction();
}

Matrix Matrix::SubMatrix(size_t line, size_t column) const
{
	Matrix sub(NbLines() - 1, NbColumns() - 1);

	int k = 0;

	for (size_t i = 0; i < NbLines(); i++)
	{
		if (i == line)
			continue;

		int l = 0;

		for (size_t j = 0; j < NbColumns(); j++)
		{
			if (j == column)
				continue;

			sub.Get(k, l) = Get(i, j);

			l++;
		}

		k++;
	}

	return sub;
}
Matrix Matrix::SubMatrix(const Matrix& m, size_t line, size_t column)
{
	return m.SubMatrix(line, column);
}

float Matrix::Determinant(const Matrix& m)
{
	if (m.NbLines() != m.NbColumns())
		throw std::runtime_error("MatrixInvertException");

	if (m.NbColumns() == 2)
		return m.Get(0, 0) * m.Get(1, 1) - m.Get(0, 1) * m.Get(1, 0);

	float det = 0;

	for (size_t i = 0; i < m.NbColumns(); i++)
	{
		Matrix mCopy(m);
		mCopy = mCopy.SubMatrix(0, i);

		if (i % 2 == 0)
			det += m.Get(0, i) * Determinant(mCopy);
		else
			det -= m.Get(0, i) * Determinant(mCopy);
	}

	return det;
}
Matrix Matrix::Adjugate() const
{
	if (NbLines() != NbColumns())
		throw std::runtime_error("MatrixInvertException");

	if (NbLines() == 2)
	{
		return Matrix(2, 2, std::vector<float>
		{
			Get(1, 1), -Get(0, 1),
			-Get(1, 0), Get(0, 0)
		});
	}

	Matrix m(NbLines(), NbColumns());

	for (size_t i = 0; i < m.NbLines(); i++)
	{
		for (size_t j = 0; j < m.NbColumns(); j++)
		{
			Matrix mSub = SubMatrix(i, j);
			m.Get(i, j) = Determinant(mSub);

			if ((i + j) % 2 != 0)
				m.Get(i, j) *= -1;
		}
	}
	return m.Transpose();
}
Matrix Matrix::Adjugate(const Matrix& m)
{
	return m.Adjugate();
}
Matrix Matrix::InvertByDeterminant() const
{
	const float det = Determinant(*this);
	if (det == 0)
		throw std::runtime_error("MatrixInvertException");

	const Matrix adj = Adjugate(*this);

	return Multiply(adj, 1 / det);
}
Matrix Matrix::InvertByDeterminant(const Matrix& m)
{
	return m.InvertByDeterminant();
}

Matrix Matrix::operator-() const
{
	return Multiply(*this, -1);
}

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
	return Matrix::Add(m1, m2);
}
Matrix operator-(const Matrix& m1, const Matrix& m2)
{
	return Matrix::Add(m1, -m2);
}

Matrix operator*(const Matrix& m, float a)
{
	return  Matrix::Multiply(m, a);
}
Matrix operator*(float a, const Matrix& m)
{
	return Matrix::Multiply(m, a);
}
Matrix operator*(const Matrix& m1, const Matrix& m2)
{
	return Matrix::Multiply(m1, m2);
}

//TODO REMAKE THIS FUNCTION WITH VECTOR 3
Vector3f operator*(const Vector3f& v, const Matrix& m)
{
	Matrix mVec = Matrix::Identity(3);
	mVec.Get(0, 2) = v.x;
	mVec.Get(1, 2) = v.y;

	mVec = mVec * m;
	return {mVec.Get(0, 2), mVec.Get(1, 2), 0};
}
Vector3f operator*(const Matrix& m, const Vector3f& v)
{
	Matrix mVec = Matrix::Identity(3);
	mVec.Get(0, 2) = v.x;
	mVec.Get(1, 2) = v.y;

	mVec = m * mVec;
	return { mVec.Get(0, 2), mVec.Get(1, 2), 0 };
}

