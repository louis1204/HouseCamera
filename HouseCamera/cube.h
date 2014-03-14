#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"

class Cube
{
  protected:
    Matrix4 matrix;                 // model matrix
    double angle;                   // rotation angle [degrees]
	double angleZ;

  public:
    Cube();   // Constructor
    Matrix4& getMatrix();
    void spin(double);      // spin cube [degrees]
	void Keyboard(unsigned char key, int x, int y);
	double getAngle();
	void setAngle(double);
	void offsetX(double);
	void identity();
	void rotateZ(double deg);
};

#endif

