#include "Camera.h"


Camera::Camera()
{
	e = Vector3();
}

Camera::Camera(Vector3 e1, Vector3 d1, Vector3 up1)
{
	e = e1;
	d = d1;
	up = up1;

	Vector3 zc = e - d;
	zc.normalize();

	Vector3 xc = up;
	xc.crossProduct(zc);
	xc.normalize();

	Vector3 yc = zc;
	yc.crossProduct(xc);

	c = Matrix4(xc[0],yc[0],zc[0],e[0],
				xc[1],yc[1],zc[1],e[1],
				xc[2],yc[2],zc[2],e[2],
				0,0,0,1);
}

Camera::~Camera(void)
{
}

Matrix4& Camera::getGLMatrix()
{
	/*
	GLdouble matrix[16];

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			matrix[i+j*4] = c.getElementAt(i, j);
		}
	}*/

	return (c);
}