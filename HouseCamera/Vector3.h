#pragma once
class Vector3
{
protected: 
	double v3[3]; //vector elements
public:
	Vector3();
	Vector3(double, double, double);
	~Vector3(void);
	void setCoords(double,double,double);
	double getCoordAt(int);
	double& operator[](const int index);
	void add(Vector3&);
	friend Vector3 operator+(Vector3& vector1, Vector3& vector2);
	void subtract(Vector3&);
	friend Vector3 operator-(Vector3& vector1, Vector3& vector2);
	void negation();
	void scale(double scaler);
	double dot(Vector3& vector);
	void crossProduct(Vector3& vector);
	double magnitude();
	void normalize();
	void print();
};

