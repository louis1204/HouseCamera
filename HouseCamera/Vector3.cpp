#include "Vector3.h"
#include <math.h>
#include <iostream>

using namespace std;

Vector3::Vector3(double i, double j, double k)
{
	setCoords(i,j,k);
}

Vector3::Vector3()
{
	v3[0] = 0;
	v3[1] = 0;
	v3[2] = 0;
}

Vector3::~Vector3(void)
{
}

void Vector3::setCoords(double i, double j, double k)
{
	v3[0] = i;
	v3[1] = j;
	v3[2] = k;
}

double Vector3::getCoordAt(int index)
{
	return(v3[index]);
}

double& Vector3::operator[](const int index)
{
	return v3[index];
}

void Vector3::add(Vector3& vector1)
{
	v3[0] = vector1[0] + v3[0];
	v3[1] = vector1[1] + v3[1];
	v3[2] = vector1[2] + v3[2];
}

Vector3 operator+(Vector3& vector1, Vector3& vector2)
{
	return Vector3(vector1.getCoordAt(0) + vector2.getCoordAt(0), vector1.getCoordAt(1) + vector2.getCoordAt(1), vector1.getCoordAt(2) + vector2.getCoordAt(2));
}

void Vector3::subtract(Vector3& vector1)
{
	v3[0] = v3[0] - vector1[0];
	v3[1] = v3[1] - vector1[1];
	v3[2] = v3[2] - vector1[2];
}

Vector3 operator-(Vector3& vector1, Vector3& vector2)
{
	return Vector3(vector1.getCoordAt(0) - vector2.getCoordAt(0), vector1.getCoordAt(1) - vector2.getCoordAt(1), vector1.getCoordAt(2) - vector2.getCoordAt(2));
}

void Vector3::negation()
{
	v3[0] = v3[0] * -1;
	v3[1] = v3[1] * -1;
	v3[2] = v3[2] * -1;
}

void Vector3::scale(double scaler)
{
	v3[0] = v3[0] * scaler;
	v3[1] = v3[1] * scaler;
	v3[2] = v3[2] * scaler;
}

double Vector3::dot(Vector3& vector)
{
	return (v3[0] * vector[0]) + (v3[1] * vector[1]) + (v3[2] * vector[2]);
}

void Vector3::crossProduct(Vector3& vector)
{
	double i = (v3[1] * vector[2]) - (v3[2] * vector[1]);
	double j = -1 * ((v3[0] * vector[2]) - (v3[2] * vector[0]));
	double k = (v3[0] * vector[1]) - (v3[1] * vector[0]);
	v3[0] = i;
	v3[1] = j;
	v3[2] = k;
}

double Vector3::magnitude()
{
	return sqrt(pow(v3[0], 2) + pow(v3[1], 2) + pow(v3[2], 2));
}

void Vector3::normalize()
{
	double length = magnitude();
	v3[0] = v3[0]/length;
	v3[1] = v3[1]/length;
	v3[2] = v3[2]/length;
}

void Vector3::print()
{
	cout << "v3[0] = " << v3[0] << endl;
	cout << "v3[1] = " << v3[1] << endl;
	cout << "v3[2] = " << v3[2] << endl;
}