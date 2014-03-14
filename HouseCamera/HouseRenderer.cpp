#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "HouseRenderer.h"
#include "Matrix4.h"
#include "cube.h"
#include<vector>

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
static Camera camera;
static Cube cube;
int mode = 1;
double objAngle = 0;

//shapes
int verts;
float* sphereVertices;
float* normals;
float* texcoords;
int sphereNumIndices;
int* sphereIndices;

float* teddyVertices;
int teddyNumIndices;
int* teddyIndices;

float* teapotVertices;
int teapotNumIndices;
int* teapotIndices;

float* bunnyVertices;
int bunnyNumIndices;
int* bunnyIndices;

float* cowVertices;
int cowNumIndices;
int* cowIndices;

Matrix4 objMatrix;

//cube
static Matrix4 rotZ = Matrix4(1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1);
static Matrix4 rotY = Matrix4(1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1);
static Matrix4 transZ = Matrix4(1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1);
static Matrix4 transX = Matrix4(1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1);
static Matrix4 transY = Matrix4(1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1);
static Matrix4 scaleM = Matrix4(1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1);
static double spinVal = 0.001;
static double r = 0;
static double g = 255;
static double b = 0;

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
	if(mode == 1)
		cube.spin(spinVal);
	else if(mode != 8 && mode != 9)
		spin(spinVal);     // rotate cube; if it spins too fast try 0.001

	displayCallback();		// call display routine to re-draw cube
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);

	if(mode == 1)
		RenderCube();
	if(mode == 2)
		RenderSphere();
	else if(mode == 3)
		RenderTeddy();
	else if(mode == 4)
		RenderTeapot();
	else if(mode == 5)
		RenderCow();
	else if(mode == 6)
		RenderBunny();
	else if(mode == 8 || mode == 9)
		RenderHouse();
	
	
	glEnd();
  
	glFlush();  
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:             // ESCAPE key
			exit (0);
			break;
		case 'c':
			spinVal = spinVal * -1;
			if(mode == 1)
				cube.getMatrix().print();
			else if(mode != 8 && mode != 9)
				objMatrix.print();
			break;
		case 'Y':
			{
				transY.translate("y",1);
				if(mode == 1)
					cube.getMatrix().print();
				else if(mode != 8 && mode != 9)
					objMatrix.print();
				break;
			}
		case 'y':
			{
				transY.translate("y",-1);
				if(mode == 1)
					cube.getMatrix().print();
				else if(mode != 8 && mode != 9)
					objMatrix.print();
				break;
			}
		case 'X':
			{
				transX.translate("x",1);
				if(mode == 1)
					cube.getMatrix().print();
				else if(mode != 8 && mode != 9)
					objMatrix.print();
				break;
			}
		case 'x':
			{
				transX.translate("x",-1);
				if(mode == 1)
					cube.getMatrix().print();
				else if(mode != 8 && mode != 9)
					objMatrix.print();
				break;
			}
		case 'Z':
			{
				transZ.translate("z",1);
				if(mode == 1)
					cube.getMatrix().print();
				else if(mode != 8 && mode != 9)
					objMatrix.print();
				break;
			}
		case 'z':
			{
				transZ.translate("z",-1);
				if(mode == 1)
					cube.getMatrix().print();
				else if(mode != 8 && mode != 9)
					objMatrix.print();
				break;
			}
		case 'r':
			cube.identity();
			rotZ.identity();
			transX.identity();
			transY.identity();
			transZ.identity();
			scaleM.identity();
			r=0;
			g=255;
			b=0;
			if(mode == 1)
					cube.getMatrix().print();
			else if(mode != 8 && mode != 9)
					objMatrix.print();
			break;
		case 'a':
			{
				cube.rotateZ(3.14/(180));
				if(mode == 1)
					cube.getMatrix().print();
				else if(mode != 8 && mode != 9)
					objMatrix.print();
				break;
			}
		case 's':
			{
				scaleM.scale(0.9);
				//cout << "scale" << endl;
				//scaleM.print();
				if(mode == 1)
					cube.getMatrix().print();
				else if(mode != 8 && mode != 9)
					objMatrix.print();
				break;
			}
		case 'S':
			{
				scaleM.scale(1.1);
				//cout << "scale" << endl;
				//scaleM.print();
				if(mode == 1)
					cube.getMatrix().print();
				else if(mode != 8 && mode != 9)
					objMatrix.print();
				break;
			}
		case '1':
			r = 255;
			g = 0;
			b = 0;
			break;
		case '2':
			r = 0;
			g = 255;
			b = 0;
			break;
		case '3':
			r = 0;
			g = 0;
			b = 255;
			break;
		case '4':
			r = 255;
			g = 255;
			b = 0;
			break;
		case 'f':
			if(mode == 2)
				FindMaxMins(sphereVertices, sphereNumIndices);
			else if(mode == 3)
				FindMaxMins(teddyVertices, teddyNumIndices);
			else if(mode == 4)
				FindMaxMins(teapotVertices, teapotNumIndices);
			else if(mode == 5)
				FindMaxMins(cowVertices, cowNumIndices);
			else if(mode == 6)
				FindMaxMins(bunnyVertices, bunnyNumIndices);
			break;
	}	
}

void ProcessFunctionKeys(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_F1:
			mode = 1;
			cube.identity();
			objMatrix.identity();
			rotZ.identity();
			transX.identity();
			transY.identity();
			transZ.identity();
			scaleM.identity();
			r=0;
			g=255;
			b=0;
			break;
		case GLUT_KEY_F2:
			mode = 2;
			cube.identity();
			objMatrix.identity();
			rotZ.identity();
			transX.identity();
			transY.identity();
			transZ.identity();
			scaleM.identity();
			r=0;
			g=255;
			b=0;
			break;
		case GLUT_KEY_F3:
			mode = 3;
			cube.identity();
			objMatrix.identity();
			rotZ.identity();
			transX.identity();
			transY.identity();
			transZ.identity();
			scaleM.identity();
			r=0;
			g=255;
			b=0;
			break;
		case GLUT_KEY_F4:
			mode = 4;
			cube.identity();
			objMatrix.identity();
			rotZ.identity();
			transX.identity();
			transY.identity();
			transZ.identity();
			scaleM.identity();
			r=0;
			g=255;
			b=0;
			break;
		case GLUT_KEY_F5:
			mode = 5;
			cube.identity();
			objMatrix.identity();
			rotZ.identity();
			transX.identity();
			transY.identity();
			transZ.identity();
			scaleM.identity();
			r=0;
			g=255;
			b=0;
			break;
		case GLUT_KEY_F6:
			mode = 6;
			cube.identity();
			objMatrix.identity();
			rotZ.identity();
			transX.identity();
			transY.identity();
			transZ.identity();
			scaleM.identity();
			r=0;
			g=255;
			b=0;
			break;
		case GLUT_KEY_F8:
			mode = 8;
			cube.identity();
			objMatrix.identity();
			rotZ.identity();
			transX.identity();
			transY.identity();
			transZ.identity();
			scaleM.identity();
			r=0;
			g=255;
			b=0;
			break;
		case GLUT_KEY_F9:
			mode = 9;
			cube.identity();
			objMatrix.identity();
			rotZ.identity();
			transX.identity();
			transY.identity();
			transZ.identity();
			scaleM.identity();
			r=0;
			g=255;
			b=0;
			break;
	}
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Cube for CSE167");    	      // open window and set window title

  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 
  

  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  //glEnable(GL_LIGHTING);
  glDisable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);
  glutKeyboardFunc (Keyboard);
  glutSpecialFunc(ProcessFunctionKeys);
  // Initialize camera matrix:
  //camera.c.identity();
  ObjReader::readObj("sphere.obj", verts, &sphereVertices, &normals, &texcoords, sphereNumIndices, &sphereIndices);
  ObjReader::readObj("teddy.obj", verts, &teddyVertices, &normals, &texcoords, teddyNumIndices, &teddyIndices);
  ObjReader::readObj("teapot.obj", verts, &teapotVertices, &normals, &texcoords, teapotNumIndices, &teapotIndices);
  ObjReader::readObj("cow.obj", verts, &cowVertices, &normals, &texcoords, cowNumIndices, &cowIndices);
  ObjReader::readObj("bunny.obj", verts, &bunnyVertices, &normals, &texcoords, bunnyNumIndices, &bunnyIndices);
  objMatrix.identity();
  glutMainLoop();
  return 0;
}

void RenderHouse()
{
	if(mode == 8)
	{
		camera = Camera(Vector3(0,10,10),Vector3(0,0,0),Vector3(0,1,0));
		camera.c.inverse(); 
	}
	else if(mode == 9)
	{
		camera = Camera(Vector3(-15,5,10),Vector3(-5,0,0),Vector3(0,1,0.5));
		camera.c.inverse(); 
	}

	camera.getGLMatrix().transpose();
	glLoadMatrixd(camera.getGLMatrix().getPointer());	//updates the matrix
	camera.getGLMatrix().transpose();
	// Draw sides of cube in object coordinate system:
	glBegin(GL_TRIANGLES);

	int x;
	for(int i = 0; i < 60; i++)
	{
		x=indices[i]*3;
		glColor3f(colors[x],colors[x+1],colors[x+2]);
		glVertex3f(vertices[x],vertices[x+1],vertices[x+2]);
	}
}

void RenderSphere()
{
	objMatrix.transpose();
	glLoadMatrixd(objMatrix.getPointer());	//updates the matrix
	objMatrix.transpose();
	// Draw sides of cube in object coordinate system:
	glBegin(GL_TRIANGLES);

	int x;
	int color = 1 % 3;
	for(int i = 0; i < sphereNumIndices; i++)
	{
		x = sphereIndices[i] * 3;
		if(color == 0)
			glColor3f(255,0,0);
		else if(color == 1)
			glColor3f(0,255,0);
		else if(color == 2)
			glColor3f(0,0,255);
		
		color++;
		color = color %3;
		glVertex3f(sphereVertices[x], sphereVertices[x+1], sphereVertices[x+2]);
	}
}

void RenderTeddy()
{
	objMatrix.transpose();
	glLoadMatrixd(objMatrix.getPointer());	//updates the matrix
	objMatrix.transpose();
	// Draw sides of cube in object coordinate system:
	glBegin(GL_TRIANGLES);

	int x;
	int color = 1 % 3;
	for(int i = 0; i < teddyNumIndices; i++)
	{
		x = teddyIndices[i] * 3;
		if(color == 0)
			glColor3f(255,0,0);
		else if(color == 1)
			glColor3f(0,255,0);
		else if(color == 2)
			glColor3f(0,0,255);
		
		color++;
		color = color %3;
		glVertex3f(teddyVertices[x], teddyVertices[x+1], teddyVertices[x+2]);
	}
}

void RenderTeapot()
{
	objMatrix.transpose();
	glLoadMatrixd(objMatrix.getPointer());	//updates the matrix
	objMatrix.transpose();

	// Draw sides of cube in object coordinate system:
	glBegin(GL_TRIANGLES);

	int x;
	int color = 1 % 3;
	for(int i = 0; i < teapotNumIndices; i++)
	{
		x = teapotIndices[i] * 3;
		if(color == 0)
			glColor3f(255,0,0);
		else if(color == 1)
			glColor3f(0,255,0);
		else if(color == 2)
			glColor3f(0,0,255);
		
		color++;
		color = color %3;
		glVertex3f(teapotVertices[x], teapotVertices[x+1], teapotVertices[x+2]);
	}
}

void RenderCow()
{
	objMatrix.transpose();
	glLoadMatrixd(objMatrix.getPointer());	//updates the matrix
	objMatrix.transpose();
	// Draw sides of cube in object coordinate system:
	glBegin(GL_TRIANGLES);

	int x;
	int color = 1 % 3;
	for(int i = 0; i < cowNumIndices; i++)
	{
		x = cowIndices[i] * 3;
		if(color == 0)
			glColor3f(255,0,0);
		else if(color == 1)
			glColor3f(0,255,0);
		else if(color == 2)
			glColor3f(0,0,255);
		
		color++;
		color = color %3;
		glVertex3f(cowVertices[x], cowVertices[x+1], cowVertices[x+2]);
	}
}

void RenderBunny()
{
	objMatrix.transpose();
	glLoadMatrixd(objMatrix.getPointer());	//updates the matrix
	objMatrix.transpose();
	// Draw sides of cube in object coordinate system:
	glBegin(GL_TRIANGLES);

	int x;
	int color = 1 % 3;
	for(int i = 0; i < bunnyNumIndices; i++)
	{
		x = bunnyIndices[i] * 3;
		if(color == 0)
			glColor3f(255,0,0);
		else if(color == 1)
			glColor3f(0,255,0);
		else if(color == 2)
			glColor3f(0,0,255);
		
		color++;
		color = color %3;
		glVertex3f(bunnyVertices[x], bunnyVertices[x+1], bunnyVertices[x+2]);
	}
}

void RenderCube()
{
	cube.getMatrix().transpose();
	glLoadMatrixd(cube.getMatrix().getPointer());	//updates the matrix
	cube.getMatrix().transpose();

	// Draw sides of cube in object coordinate system:
	glBegin(GL_QUADS);
    glColor3f(r, g, b);

    // Draw front face:
	glNormal3f(0.0, 0.0, 1.0);   
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0, -5.0,  5.0);
    glVertex3f(-5.0, -5.0,  5.0);
    
    // Draw left side:
	glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f(-5.0,  5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0,  5.0);
    
    // Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0,  5.0);
  
    // Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-5.0,  5.0, -5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
  
    // Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f(-5.0,  5.0, -5.0);
  
    // Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0,  5.0);
    glVertex3f(-5.0, -5.0,  5.0);
}

Cube::Cube()
{
  angle = 0.0;
  angleZ = 0.0;
}

Matrix4& Cube::getMatrix()
{
  return matrix;
}

void Cube::spin(double deg)
{
  angle += deg;
  if (angle > 360.0 || angle < -360.0) 
	  angle = 0.0;

  Matrix4 transformationM = Matrix4(1,0,0,0,
						 0,1,0,0,
						 0,0,1,0,
						 0,0,0,1);
  transformationM.multiply(transX);
  transformationM.multiply(transY);
  transformationM.multiply(transZ);
  rotY.rotateY(angle);
  transformationM.multiply(rotY);
  //matrix.setRotateY(angle, cube.getMatrix());
  //matrix.add(rotY);

  transformationM.multiply(rotZ);

  transformationM.multiply(scaleM);
  matrix = transformationM;
}

void Cube::rotateZ(double deg)
{
	angleZ += deg;
	if (angleZ > 360.0 || angleZ < -360.0) 
	  angleZ = 0.0;

	rotZ.rotateZ(angleZ);
}

double Cube::getAngle()
{
	return cube.angle;
}

void Cube::setAngle(double angle)
{
	cube.angle = angle;
}

void Cube::offsetX(double offset)
{
	cube.matrix.translate("x", offset);
}

void Cube::identity()
{
	cube.matrix.identity();
}

void spin(double deg)
{
	objAngle += deg;
	if (objAngle > 360.0 || objAngle < -360.0) 
	  objAngle = 0.0;

  Matrix4 transformationM = Matrix4(1,0,0,0,
						 0,1,0,0,
						 0,0,1,0,
						 0,0,0,1);
  if(mode != 2)
	transformationM.multiply(scaleM);
    transformationM.multiply(transX);
  transformationM.multiply(transY);
  transformationM.multiply(transZ);
  rotY.rotateY(objAngle);
  transformationM.multiply(rotY);

  transformationM.multiply(rotZ);

  if(mode == 2)
	  transformationM.multiply(scaleM);
  

  objMatrix = transformationM;
}

void FindMaxMins(float* vertices, int numIndices)
{
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;
	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float maxZ = FLT_MIN;

	for(int i = 0; i < numIndices; i++)
	{
		if(i%3 == 0)
		{
			if(vertices[i] < minX)
				minX = vertices[i];

			if(vertices[i] > maxX)
				maxX = vertices[i];
		}

		else if(i%3 == 1)
		{
			if(vertices[i] < minY)
				minY = vertices[i];

			if(vertices[i] > maxY)
				maxY = vertices[i];
		}

		else if(i%3 == 2)
		{
			if(vertices[i] < minZ)
				minZ = vertices[i];
			
			if(vertices[i] > maxZ)
				maxZ = vertices[i];
		}
	}
		cout << "Max X: " << maxX << endl;
		cout << "Min X: " << minX << endl;
		cout << "Max Y: " << maxY << endl;
		cout << "Min Y: " << minY << endl;
		cout << "Max Z: " << maxZ << endl;
		cout << "Min Z: " << minZ << endl;

		float translateX = (maxX + minX)/2;
		
		float translateY = (maxY + minY)/2;
		
		float translateZ = (maxZ + minZ)/2;

		transX.identity();
		transY.identity();
		transZ.identity();
		transX.translate("x", -1*translateX);
		transY.translate("y", -1*translateY);
		transZ.translate("z", -1*translateZ);

		cout << "Translate X by " << translateX << endl;
		transX.print();
		cout << "Translate Y by " << translateY << endl;
		transY.print();
		cout << "Translate Z by " << translateZ << endl;
		transZ.print();

		scaleM.identity();

		//sphere
		if(mode == 2)
		{
			scaleM.scale(19);
			cout << "Scale by 19:" << endl;
			scaleM.print();
		}
		//teddy
		else if(mode == 3)
		{
			scaleM.scale(0.60264);
			cout << "Scale by: 0.60264" << endl;
			scaleM.print();
		}

		//teapot
		else if(mode == 4)
		{
			scaleM.scale(3.0);
			cout << "Scale by: 3.2669" << endl;
			scaleM.print();
		}

		//cow
		else if(mode == 5)
		{
			scaleM.scale(1.35);
			cout << "Scale by: 1.53158" << endl;
			scaleM.print();
		}

		//bunny
		else if(mode == 6)
		{
			scaleM.scale(5.9);
			cout << "Scale by: 8.9979" << endl;
			scaleM.print();
		}
}