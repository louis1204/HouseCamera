#include "Vector4.h"
#include <iostream>

using namespace std;

Vector4::Vector4(double i, double j, double k)
{
	v4[0] = i;
	v4[1] = j;
	v4[2] = k;
	v4[3] = 1;
}

Vector4::Vector4(double i, double j, double k, double l)
{
	v4[0] = i;
	v4[1] = j;
	v4[2] = k;
	v4[3] = l;
}

Vector4::~Vector4(void)
{
}


void Vector4::setCoords(double i, double j, double k, double l)
{
	v4[0] = i;
	v4[1] = j;
	v4[2] = k;
	v4[3] = l;
}

double Vector4::getCoordAt(int index)
{
	return(v4[index]);
}

double& Vector4::operator[](const int index)
{
	return v4[index];
}

void Vector4::add(Vector4& vector1)
{
	v4[0] = vector1[0] + v4[0];
	v4[1] = vector1[1] + v4[1];
	v4[2] = vector1[2] + v4[2];
	v4[3] = vector1[3] + v4[3];
}

Vector4 operator+(Vector4& vector1, Vector4& vector2)
{
	return Vector4(vector1.getCoordAt(0) + vector2.getCoordAt(0), vector1.getCoordAt(1) + vector2.getCoordAt(1), vector1.getCoordAt(2) + vector2.getCoordAt(2), vector1.getCoordAt(3) + vector2.getCoordAt(3));
}

void Vector4::subtract(Vector4& vector1)
{
	v4[0] = v4[0] - vector1[0];
	v4[1] = v4[1] - vector1[1];
	v4[2] = v4[2] - vector1[2];
	v4[3] = v4[3] - vector1[3];
}

Vector4 operator-(Vector4& vector1, Vector4& vector2)
{
	return Vector4(vector1.getCoordAt(0) - vector2.getCoordAt(0), vector1.getCoordAt(1) - vector2.getCoordAt(1), vector1.getCoordAt(2) - vector2.getCoordAt(2), vector1.getCoordAt(3) - vector2.getCoordAt(3));
}

void Vector4::dehomogenize()
{
	v4[0] = v4[0]/v4[3];
	v4[1] = v4[1]/v4[3];
	v4[2] = v4[2]/v4[3];
	v4[3] = v4[3]/v4[3];
}

void Vector4::print()
{
	cout << "v4[0] = " << v4[0] << endl;
	cout << "v4[1] = " << v4[1] << endl;
	cout << "v4[2] = " << v4[2] << endl;
	cout << "v4[3] = " << v4[3] << endl;
}