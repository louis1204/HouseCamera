#pragma once
#include "Vector3.h"

class Vector4
{
protected: 
	double v4[4]; //vector elements
public:
	Vector4(double, double, double);
	Vector4(double, double, double, double);
	~Vector4(void);
	void setCoords(double,double,double, double);
	double getCoordAt(int);
	double& operator[](const int index);
	void add(Vector4&);
	friend Vector4 operator+(Vector4& vector1, Vector4& vector2);
	void subtract(Vector4&);
	friend Vector4 operator-(Vector4& vector1, Vector4& vector2);
	void dehomogenize();
	void print();
};

