#include <glut.h>
#include <math.h> 

int ww = 800, wh = 800;
int xi, yi, xf, yf;

void putPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void plotCircle(int h, int k, int x, int y)
{
    putPixel((x + h), (y + k));
    putPixel((y + h), (x + k));
    putPixel((-y + h), (x + k));
    putPixel((-x + h), (y + k));
    putPixel((-x + h), (-y + k));
    putPixel((-y + h), (-x + k));
    putPixel((y + h), (-x + k));
    putPixel((x + h), (-y + k));

}

void drawHorizontalLine(int x1, int y1, int x2, int y2)
{
    glPointSize(3.0);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
    glFlush();
}

void horizontalLine(int h, int k, int x, int y)
{
    drawHorizontalLine(-x + h, y + k, x + h, y + k);
    drawHorizontalLine(-y + h, x + k, y + h, x + k);
    drawHorizontalLine(-y + h, -x + k, y + h, -x + k);
    drawHorizontalLine(-x + h, -y + k, x + h, -y + k);
}

void bresenhamCircle(int h, int k, int r)
{
    glColor3f(0.0, 0.0, 1.0);
    int x = 0, y = r, d = 3 - 2 * r;
    while (x <= y)
    {
        plotCircle(h, k, x, y);
        horizontalLine(h, k, x, y);
        if (d < 0)
        {
            d = d + 4 * x + 6;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void midpointCircle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int p = 1 - r;

    plotCircle(xc, yc, x, y);

    while (x < y)
    {
        x++;
        if (p < 0)
            p += 2 * x + 1;
        else
        {
            y--;
            p += 2 * (x - y) + 1;
        }
        plotCircle(xc, yc, x, y);
    }
}

void drawArc(int xc, int yc, int r, float startAngle, float endAngle)
{
    float angleStep = 0.1f;
    for (float angle = startAngle; angle <= endAngle; angle += angleStep)
    {
        float radians = angle * 3.14159265 / 180.0;
        int x = xc + r * cos(radians);
        int y = yc + r * sin(radians);
        putPixel(x, y);
    }
}

void bresenhamAlg(int x0, int y0, int x1, int y1)
{

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int x, y;
    if (dx >= dy)
    {
        int d = 2 * dy - dx;
        int ds = 2 * dy;
        int dt = 2 * (dy - dx);
        if (x0 < x1)
        {
            x = x0;
            y = y0;
        }
        else
        {
            x = x1;
            y = y1;
            x1 = x0;
            y1 = y0;
        }
        putPixel(x, y);
        while (x < x1)
        {
            if (d < 0)
                d += ds;
            else {
                if (y < y1) {
                    y++;
                    d += dt;
                }
                else {
                    y--;
                    d += dt;
                }
            }
            x++;
            putPixel(x, y);
        }
    }
    else {
        int d = 2 * dx - dy;
        int ds = 2 * dx;
        int dt = 2 * (dx - dy);
        if (y0 < y1)
        {
            x = x0;
            y = y0;
        }
        else
        {
            x = x1;
            y = y1;
            y1 = y0;
            x1 = x0;
        }
        putPixel(x, y);
        while (y < y1)
        {
            if (d < 0)
                d += ds;
            else {
                if (x < x1)
                {
                    x++;
                    d += dt;
                }
                else
                {
                    x--;
                    d += dt;
                }
            }
            y++;
            putPixel(x, y);

        }
    }
}



void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.2, 0.3, 0.3);
    glClear(GL_COLOR_BUFFER_BIT);

    //bresenhamCircle(400, 400, 200);

    glColor3f(1.0, 0.0, 0.0);
    drawArc(200, 400, 200, 300, 420);
    drawArc(500, 227, 200, 60, 180);
    drawArc(500, 573, 200, 180, 300);

    glColor3f(0.0, 1.0, 0.0);
    drawArc(300, 573, 200, 240, 360);
    drawArc(300, 227, 200, 0, 120);
    drawArc(600, 400, 200, 120, 240);

    glColor3f(1.0, 1.0, 1.0);
    bresenhamAlg(300, 573, 500, 573);
    bresenhamAlg(500, 573, 600, 400);
    bresenhamAlg(600, 400, 500, 227);
    bresenhamAlg(500, 227, 300, 227);
    bresenhamAlg(300, 227, 200, 400);
    bresenhamAlg(200, 400, 300, 573);

    glColor3f(1.0, 1.0, 1.0);
    bresenhamAlg(300, 573, 400, 400);
    bresenhamAlg(500, 227, 400, 400);
    bresenhamAlg(500, 573, 400, 400);
    bresenhamAlg(300, 227, 400, 400);
    bresenhamAlg(200, 400, 400, 400);
    bresenhamAlg(600, 400, 400, 400);

    glFlush();
}

void myinit()
{
    glViewport(0, 0, ww, wh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww, wh);
    glutCreateWindow("Draw Circle");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}



//bresenham Circle

#include <glut.h>
#include <math.h> 

int ww = 800, wh = 600;
int xi, yi, xf, yf; 

void putPixel (int x, int y)  
{  
   glColor3f (0.3, 0.2, 0.0); // activate the pixel by setting the point color to white  
   glBegin (GL_POINTS);  
	glVertex2i (x, y); // set the point  
   glEnd ();  
   glFlush (); // process all openGL routines as quickly as possible  
} 

void plotCircle(int h, int k, int x, int y)
{
	putPixel((x+h), (y+k)); //x,y
	putPixel((y+h), (x+k));//y, x
	putPixel((-y+h), (x+k));//-y, x
	putPixel((-x+h), (y+k));//-x, y
	putPixel((-x+h), (-y+k));//-x,-y
	putPixel((-y+h), (-x+k));//-y,-x
	putPixel((y+h), (-x+k));//y,-x
	putPixel((x+h), (-y+k));//x,-y

}


void display()  
{  
   glClearColor(0.4, 0.7, 0.5, 1.0);  
   glColor3f(0.2, 0.3, 0.3);  
   glClear(GL_COLOR_BUFFER_BIT);  
   glFlush();  
} 

void bresenhamCircle(int h, int k, int r)
{
	int x=0, y=r, d= 3-2*r;
	while(x <= y)
	{
		plotCircle(h, k, x, y);
		if(d<0)
		{
			d = d + 4*x + 6; 
		}
		else
		{
			d = d + 4*(x-y) + 10;
			y--;
		}
		x++;
	}
}

void mouse(int btn, int state, int x, int y)
{
	
	if (btn == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)
		{
			xi = x;
			yi = (wh - y);
		}
		else if (state == GLUT_UP) {
			xf = x;
			yf = (wh - y);
			glutPostRedisplay();
			int r = (int) sqrt((double)(xi-xf)*(xi-xf)+(yi-yf)*(yi-yf));
			bresenhamCircle (xi, yi, r);
		}
	if (btn == GLUT_RIGHT_BUTTON) {
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}




void myinit()  
{        
     glViewport(0,0,ww,wh);  
     glMatrixMode(GL_PROJECTION);  
     glLoadIdentity();  
     gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);  
     glMatrixMode(GL_MODELVIEW);  
}  
int main(int argc, char** argv)  
{  
     glutInit(&argc,argv);  
     glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  
     glutInitWindowSize(ww,wh);  
     glutCreateWindow("Bresenham Circle Algorithm");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
     glutMainLoop();  
     return 0;  
}




////    Mouse event


#include <glut.h>
#include <stdio.h>

int ww = 600, wh = 400;
int xi, yi, xf, yf;

void drawLine(GLint x1, GLint y1, GLint x2, GLint y2)
{
	glPointSize(2.0);

	glBegin(GL_POINTS);

	glVertex2i(x1, y1);	//plotting the first point

	GLint y;
	float m = (y2 - y1) / (float)(x2 - x1);
	float c = y1 - x1 * m;
	printf("m = %f   ,    c = %f \n", m, c);

	for (GLint x = x1 + 1; x <= x2; x++) {
		y = m * x + c;
		glVertex2i(x, y);	//plotting points
	}

	glEnd();
}

void display()
{
	drawLine(xi, yi, xf, yf);
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)
		{
			xi = x;
			yi = (wh - y);
		}
		else if (state == GLUT_UP) {
			xf = x;
			yf = (wh - y);
			glutPostRedisplay();
		}
	if (btn == GLUT_RIGHT_BUTTON) {
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}

void myinit()
{
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0, 0.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutCreateWindow("Lines");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	myinit();
	glutMainLoop();

	return 0;
}