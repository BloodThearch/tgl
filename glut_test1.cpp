#include <iostream>
#include <GL/glut.h>
using namespace std;
GLdouble x1, Y1, x2, y2;
void myinit()
{
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-250, 250, -250, 250);
	glMatrixMode(GL_PROJECTION);
	//glViewport(0, 0, 500, 500);
}

void setPixel(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void ellipseMidPoint(int rx, int ry, int xCenter, int yCenter)
{
	//plotting first region	
	float x = 0;
	float y = ry;
	float p1 = ry * ry - (rx * rx) * ry + (rx * rx) * (0.25);
	//slope
	float dx = 2 * (ry * ry) * x;
	float dy = 2 * (rx * rx) * y;
	while (dx < dy)
	{
		setPixel(xCenter + x, yCenter + y);
		setPixel(xCenter - x, yCenter + y);
		setPixel(xCenter + x, yCenter - y);
		setPixel(xCenter - x, yCenter - y);
		if (p1 < 0)
		{
			x = x + 1;
			dx = 2 * (ry * ry) * x;
			p1 = p1 + dx + (ry * ry);
		}
		else {
			x = x + 1;
			y = y - 1;
			dx = 2 * (ry * ry) * x;
			dy = 2 * (rx * rx) * y;
			p1 = p1 + dx - dy + (ry * ry);
		}
	}
	//plotting region 2
	float p2 = (ry * ry) * (x + 0.5) * (x + 0.5) + (rx * rx) * (y - 1) * (y - 1) - (rx * rx) * (ry * ry);
	while (y > 0)
	{
		setPixel(xCenter + x, yCenter + y);
		setPixel(xCenter - x, yCenter + y);
		setPixel(xCenter + x, yCenter - y);
		setPixel(xCenter - x, yCenter - y);
		if (p2 > 0)
		{
			x = x;
			y = y - 1;
			dy = 2 * (rx * rx) * y;
			p2 = p2 - dy + (rx * rx);
		}
		else {
			x = x + 1;
			y = y - 1;
			dy = dy - 2 * (rx * rx);
			dx = dx + 2 * (ry * ry);
			p2 = p2 + dx - dy + (rx * rx);
		}
	}
}

void bcircle(int xin, int yin, int rin)
{
//	glColor3f(1, 0, 0);
//	glPointSize(2.0);
	float r = rin;
	float x = 0, y = rin;
	float p = 3 - 2 * r;
	glBegin(GL_POINTS);
	while(x!=y)
	{
		x++;
		if (p < 0) {
			p += 4 * x + 6;
		}
		else {
			y--;
			p += 4 * x - 4 * y + 10;
		}
		glVertex2i(x + xin, y + yin);
		glVertex2i(-x + xin, y + yin);
		glVertex2i(x + xin, -y + yin);
		glVertex2i(-x + xin, -y + yin);
		glVertex2i(y + xin, x + yin);
		glVertex2i(-y + xin, x + yin);
		glVertex2i(y + xin, -x + yin);
		glVertex2i(-y + xin, -x + yin);

	}
	glEnd();
//	glFlush();
}

void mcircle(int xoff, int yoff, int rin)
{
//	glColor3f(1, 0, 0);
//	glPointSize(2.0);
	float r = rin;
	float x = 0, y = r;
	float p = 1 - r;
	glBegin(GL_POINTS);
	while(x!=y)
	{
		x++;
		if (p < 0) {
			p += 2 * (x + 1) + 1;
		}
		else {
			y--;
			p += 2 * (x + 1) + 1 - 2 * (y - 1);
		}
		glVertex2i(x + xoff, y + yoff);
		glVertex2i(-x + xoff, y + yoff);
		glVertex2i(x + xoff, -y + yoff);
		glVertex2i(-x + xoff, -y + yoff);
		glVertex2i(y + xoff, x + yoff);
		glVertex2i(-y + xoff, x + yoff);
		glVertex2i(y + xoff, -x + yoff);
		glVertex2i(-y + xoff, -x + yoff);

	}
	glEnd();
//	glFlush();
}



void bline(GLdouble x1, GLdouble Y1, GLdouble x2, GLdouble y2)
{
	GLdouble dx, dy, steps;
	float xinc, yinc, x, y,p;
	x = x1;
	y = Y1;
	dx = x2 - x1;
	dy = y2 - Y1;
	p = 2 * dy - dx;
//	glClear(GL_COLOR_BUFFER_BIT);
//	glPointSize(4.0);
	glBegin(GL_POINTS);
	while (x != x2)
	{
		if (p < 0)
		{
			p = p + 2 * dy;
			x = x + 1;
			glVertex2d(x, y);
		}
		else
		{
			p = p + 2 * dy - 2 * dx;
			x = x + 1;
			y = y + 1;
			glVertex2d(x, y);
		}
			
	}
	

	glEnd();
//	glFlush();
}


void ddaLine(GLdouble x1, GLdouble Y1, GLdouble x2, GLdouble y2)
{
	GLdouble dx, dy, steps;
	float xinc, yinc, x, y;
	x = x1;
	y = Y1;
	dx = x2 - x1;
	dy = y2 - Y1;
	steps = (abs(dx) > abs(dy) ? dx : dy);
	xinc = dx / (float)steps;
	yinc = dy / (float)steps;
//	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	for (int i = 0; i < steps; i++)
	{
		x = x + xinc;
		y = y + yinc;
		glVertex2d(x, y);
	}
	glEnd();
//	glFlush();
}



void bsmile(int xin, int yin, int rin)
{
//	glColor3f(1, 0, 0);
//	glPointSize(2.0);
	float r = rin;
	float x = 0, y = rin;
	float p = 3 - 2 * r;
	glBegin(GL_POINTS);
	while(x!=y)
	{
		x++;
		if (p < 0) {
			p += 4 * x + 6;
		}
		else {
			y--;
			p += 4 * x - 4 * y + 10;
		}
//		glVertex2i(x + xin, y + yin);
//		glVertex2i(-x + xin, y + yin);
		glVertex2i(x + xin, -y + yin);
		glVertex2i(-x + xin, -y + yin);
//		glVertex2i(y + xin, x + yin);
//		glVertex2i(-y + xin, x + yin);
//		glVertex2i(y + xin, -x + yin);
//		glVertex2i(-y + xin, -x + yin);

	}
	glEnd();
//	glFlush();
}

void display()
{
	glColor3f(1, 0, 0);
	glPointSize(2.0);
	
	// smile 
	
//	bcircle(0, 0, 100);
//	bcircle(40, 35, 15);
//	bcircle(-40, 35, 15);
//	bsmile(0, 0, 55);	
	
//	mcircle(0, 0, 100);
//	mcircle(40, 35, 15);
//	mcircle(-40, 35, 15);
//	bsmile(0, 0, 55);
	
	// smile finished	
	
//	ddaLine(0, -200, 100, 0);
//	bline(0, -200, 100, 0);
	
	ellipseMidPoint(65, 35, 0, 0);
	
	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Window");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}
