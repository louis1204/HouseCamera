#include <math.h>
#include "Matrix4.h"
#include <iostream>

using namespace std;

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0.0;
    }
  }
} 

Matrix4::Matrix4(
  double m00, double m01, double m02, double m03,
  double m10, double m11, double m12, double m13,
  double m20, double m21, double m22, double m23,
  double m30, double m31, double m32, double m33 )
{
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;
  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;
  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;
  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

double* Matrix4::getPointer()
{
  return &m[0][0];
}

void Matrix4::identity()
{
  double ident[4][4]={{1.0,0.0,0.0,0.0},{0.0,1.0,0.0,0.0},{0.0,0.0,1.0,0.0},{0.0,0.0,0.0,1.0}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = ident[i][j];
    }
  }
}

// angle in radians
void Matrix4::rotateY(double angle)
{
	m[0][0] = cos(angle);
	m[0][1] = 0.0;
	m[0][2] = sin(angle);
	m[0][3] = 0.0;
	m[1][0] = 0.0;
	m[1][1] = 1.0;
	m[1][2] = 0.0;
	m[1][3] = 0.0;
	m[2][0] = -sin(angle);
	m[2][1] = 0.0;
	m[2][2] = cos(angle);
	m[2][3] = 0.0;
	m[3][0] = 0.0;
	m[3][1] = 0.0;
	m[3][2] = 0.0;
	m[3][3] = 1.0;
}

void Matrix4::setRotateY(double angle, Matrix4 matrix)
{
	m[0][0] = cos(angle);
	m[0][1] = 0.0;
	m[0][2] = sin(angle);
	m[0][3] = matrix.getElementAt(0,3);
	m[1][0] = 0.0;
	m[1][1] = 1.0;
	m[1][2] = 0.0;
	m[1][3] = matrix.getElementAt(1,3);
	m[2][0] = -sin(angle);
	m[2][1] = 0.0;
	m[2][2] = cos(angle);
	m[2][3] = matrix.getElementAt(2,3);
	m[3][0] = 0.0;
	m[3][1] = 0.0;
	m[3][2] = 0.0;
	m[3][3] = matrix.getElementAt(3,3);
}

void Matrix4::rotateX(double angle)
{
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = cos(angle);
	m[1][2] = -sin(angle);
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = sin(angle);
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::rotateZ(double angle)
{
	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = sin(angle);
	m[1][1] = cos(angle);
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::rotate(double x, double y, double z, double angle)
{
	m[0][0] = 1 + (1-cos(angle))*(pow(x,2)-1);
	m[0][1] = -z*sin(angle) + (1-cos(angle))*x*y;
	m[0][2] = y * sin(angle) + (1 - cos(angle))*x*z;
	m[0][3] = 0;
	m[1][0] = z*sin(angle) + (1-cos(angle))*y*x;
	m[1][1] = 1+(1-cos(angle)) * (pow(y,2)-1);
	m[1][2] = -x*sin(angle) + (1-cos(angle))*y*z;
	m[1][3] = 0;
	m[2][0] = -y*sin(angle) + (1 - cos(angle))*z*x;
	m[2][1] = x*sin(angle) + (1 - cos(angle)) * z * y;
	m[2][2] = 1+(1-cos(angle))*(pow(z,2)-1);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
                    
}

double Matrix4::getElementAt(int x, int y)
{
	return m[x][y];
}

void Matrix4::multiply(Matrix4 matrix)
{
	double temp[4][4];

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			temp[i][j] = (m[i][0] * matrix.getElementAt(0,j)) + (m[i][1] * matrix.getElementAt(1,j)) + (m[i][2] * matrix.getElementAt(2, j)) + (m[i][3] * matrix.getElementAt(3, j));
		}
	}

	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			m[i][j] = temp[i][j];
		}
	}
}

void Matrix4::multiply(double matrix[4][4])
{
	double temp[4][4];

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			temp[i][j] = (m[i][0] * matrix[0][j]) + (m[i][1] * matrix[1][j]) + (m[i][2] * matrix[2][j]) + (m[i][3] * matrix[3][j]);
		}
	}

	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			m[i][j] = temp[i][j];
		}
	}
}

double* Matrix4::multiply(double vector[4])
{
    double *temp = new double[4];
	for(int i = 0; i < 4; i++)
	{
		temp[i] = (m[i][0] * vector[0]) + (m[i][1] * vector[1]) + (m[i][2] * vector[2]) + (m[i][3] * vector[3]);
	}

	return temp;
}

void Matrix4::scale(double scalar)
{
  double scaleMatrix[4][4]={{m[0][0] * scalar,0,0,0},{0,m[1][1] * scalar,0,0},{0,0,m[2][2] * scalar,0},{0,0,0,1}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
		m[i][j] = scaleMatrix[i][j];
    }
  }
}

void Matrix4::translate(char* axis, double offset)
{
	Matrix4 translationMatrix;
	if(axis == "x" || axis == "X")
		translationMatrix = Matrix4(1.0,0.0,0.0,m[0][3] + offset,
									0.0,1.0,0.0,0.0,
									0.0,0.0,1.0,0.0,
									0.0,0.0,0.0,1.0);
	else if(axis == "y" || axis == "Y")
		translationMatrix = Matrix4(1,0,0,0,
									0,1,0,m[1][3] + offset,
									0,0,1,0,
									0,0,0,1);
	else if(axis == "z" || axis == "Z")
		translationMatrix = Matrix4(1,0,0,0,
									0,1,0,0,
									0,0,1,m[2][3] + offset,
									0,0,0,1);
	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			m[i][j] = translationMatrix.getElementAt(i,j);
		}
	}
}

void Matrix4::print()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			cout << m[i][j] << "\t";
		}
		cout << endl;
	}

	cout << endl;
}

void Matrix4::transpose()
{
	double transposedMatrix[4][4];

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			transposedMatrix[i][j] = m[j][i];
		}
	}

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			m[i][j] = transposedMatrix[i][j];
		}
	}
}

void Matrix4::add(Matrix4 matrix)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			m[i][j] += matrix.getElementAt(i,j);
		}
	}
}

bool Matrix4::inverse()
{
	 double temp[4][4], det;

	temp[0][0] = m[1][1]  * m[2][2] * m[3][3] - 
             m[1][1]  * m[3][2] * m[2][3] - 
             m[1][2]  * m[2][1]  * m[3][3] + 
             m[1][2]  * m[3][1]  * m[2][3] +
             m[1][3] * m[2][1]  * m[3][2] - 
             m[1][3] * m[3][1]  * m[2][2];

	temp[0][1] = -m[0][1]  * m[2][2] * m[3][3] + 
              m[0][1]  * m[3][2] * m[2][3] + 
              m[0][2]  * m[2][1]  * m[3][3] - 
              m[0][2]  * m[3][1]  * m[2][3] - 
              m[0][3] * m[2][1]  * m[3][2] + 
              m[0][3] * m[3][1]  * m[2][2];

	temp[0][2] = m[0][1]  * m[1][2] * m[3][3] - 
             m[0][1]  * m[3][2] * m[1][3] - 
             m[0][2]  * m[1][1] * m[3][3] + 
             m[0][2]  * m[3][1] * m[1][3] + 
             m[0][3] * m[1][1] * m[3][2] - 
             m[0][3] * m[3][1] * m[1][2];

	temp[0][3] = -m[0][1]  * m[1][2] * m[2][3] + 
               m[0][1]  * m[2][2] * m[1][3] +
               m[0][2]  * m[1][1] * m[2][3] - 
               m[0][2]  * m[2][1] * m[1][3] - 
               m[0][3] * m[1][1] * m[2][2] + 
               m[0][3] * m[2][1] * m[1][2];

	temp[1][0] = -m[1][0]  * m[2][2] * m[3][3] + 
              m[1][0]  * m[3][2] * m[2][3] + 
              m[1][2]  * m[2][0] * m[3][3] - 
              m[1][2]  * m[3][0] * m[2][3] - 
              m[1][3] * m[2][0] * m[3][2] + 
              m[1][3] * m[3][0] * m[2][2];

	temp[1][1] =m[0][0] * m[2][2] * m[3][3] - 
            m[0][0] * m[3][2] * m[2][3] - 
             m[0][2]  *m[2][0]* m[3][3] + 
             m[0][2]  *m[3][0]* m[2][3] + 
             m[0][3] *m[2][0]* m[3][2] - 
             m[0][3] *m[3][0]* m[2][2];

	temp[1][2] = -m[0][0]  * m[1][2] * m[3][3] + 
             m[0][0] * m[3][2] * m[1][3] + 
              m[0][2]  *m[1][0]* m[3][3] - 
              m[0][2]  *m[3][0]* m[1][3] - 
              m[0][3] *m[1][0]* m[3][2] + 
              m[0][3] *m[3][0]* m[1][2];

	temp[1][3] =m[0][0] * m[1][2] * m[2][3] - 
             m[0][0] * m[2][2] * m[1][3] - 
              m[0][2]  *m[1][0]* m[2][3] + 
              m[0][2]  *m[2][0]* m[1][3] + 
              m[0][3] *m[1][0]* m[2][2] - 
              m[0][3] *m[2][0]* m[1][2];

	temp[2][0] =m[1][0] * m[2][1] * m[3][3] - 
            m[1][0] * m[3][1] * m[2][3] - 
             m[1][1]  *m[2][0]* m[3][3] + 
             m[1][1]  *m[3][0]* m[2][3] + 
             m[1][3] *m[2][0]* m[3][1] - 
             m[1][3] *m[3][0]* m[2][1];

	temp[2][1] = -m[0][0]  * m[2][1] * m[3][3] + 
             m[0][0] * m[3][1] * m[2][3] + 
              m[0][1]  *m[2][0]* m[3][3] - 
              m[0][1]  *m[3][0]* m[2][3] - 
              m[0][3] *m[2][0]* m[3][1] + 
              m[0][3] *m[3][0]* m[2][1];

	temp[2][2] =m[0][0] * m[1][1] * m[3][3] - 
             m[0][0] * m[3][1] * m[1][3] - 
              m[0][1]  *m[1][0]* m[3][3] + 
              m[0][1]  *m[3][0]* m[1][3] + 
              m[0][3] *m[1][0]* m[3][1] - 
              m[0][3] *m[3][0]* m[1][1];

	temp[2][3] = -m[0][0]  * m[1][1] * m[2][3] + 
              m[0][0] * m[2][1] * m[1][3] + 
               m[0][1]  *m[1][0]* m[2][3] - 
               m[0][1]  *m[2][0]* m[1][3] - 
               m[0][3] *m[1][0]* m[2][1] + 
               m[0][3] *m[2][0]* m[1][1];

	temp[3][0] = -m[1][0] * m[2][1] * m[3][2] + 
             m[1][0]* m[3][1] * m[2][2] + 
              m[1][1] *m[2][0]* m[3][2] - 
              m[1][1] *m[3][0]* m[2][2] - 
              m[1][2] *m[2][0]* m[3][1] + 
              m[1][2] *m[3][0]* m[2][1];

	temp[3][1] =m[0][0]* m[2][1] * m[3][2] - 
            m[0][0]* m[3][1] * m[2][2] - 
             m[0][1] *m[2][0]* m[3][2] + 
             m[0][1] *m[3][0]* m[2][2] + 
             m[0][2] *m[2][0]* m[3][1] - 
             m[0][2] *m[3][0]* m[2][1];

	temp[3][2] = -m[0][0] * m[1][1] * m[3][2] + 
              m[0][0]* m[3][1] * m[1][2] + 
               m[0][1] *m[1][0]* m[3][2] - 
               m[0][1] *m[3][0]* m[1][2] - 
               m[0][2] *m[1][0]* m[3][1] + 
               m[0][2] *m[3][0]* m[1][1];

	temp[3][3] =m[0][0]* m[1][1] * m[2][2] - 
             m[0][0]* m[2][1] * m[1][2] - 
              m[0][1] *m[1][0]* m[2][2] + 
              m[0][1] *m[2][0]* m[1][2] + 
              m[0][2] *m[1][0]* m[2][1] - 
              m[0][2] *m[2][0]* m[1][1];

    det =m[0][0]* temp[0][0] +m[1][0]* temp[0][1] +m[2][0]* temp[0][2] +m[3][0]* temp[0][3];

    if (det == 0)
        return false;

    det = 1.0 / det;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			m[i][j] = temp[i][j] * det;
		}
	}

    return true;
}