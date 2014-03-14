#ifndef _MATRIX4_H_
#define _MATRIX4_H_

class Matrix4
{
  protected:
    double m[4][4];   // matrix elements
    
  public:
    Matrix4();        // constructor
    Matrix4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
    double* getPointer();  // return pointer to matrix elements
    void identity();  // create identity matrix
    void rotateY(double); // rotation about y axis
	double getElementAt(int x, int y);
	void multiply(Matrix4);
	void multiply(double[4][4]);
	double* multiply(double*);
	void rotateX(double);
	void rotateZ(double);
	void rotate(double, double, double, double);
	void scale(double);
	void translate(char*, double);
	void print();
	void transpose();
	void add(Matrix4 matrix);
	void setRotateY(double angle, Matrix4 matrix);
	bool inverse();
};

#endif