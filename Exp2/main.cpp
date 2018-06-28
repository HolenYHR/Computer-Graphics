#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <iostream>
/* Global variables */
char title[] = "3D Shapes with animation";
GLfloat anglePyramid = 0.0f;  // Rotational angle for pyramid [NEW]
GLfloat angleCube = 0.0f;     // Rotational angle for cube [NEW]
int refreshMills = 15;        // refresh interval in milliseconds [NEW]

GLfloat x = 0;
GLfloat y = 0.3;
GLfloat z = 0;
GLfloat x1 = -1.5;
GLfloat y3 = -1.5;
GLfloat x2 = -1;
GLfloat y2 = 0.5;

GLfloat temp1;
GLfloat temp2;
int step1;
int step2;

int ccc = 0;
int ddd = 0;
GLfloat aaa;
GLfloat bbb;
GLfloat movex1 = 0;
GLfloat movey1 = 0;
GLfloat movex2 = 0;
GLfloat movey2 = 0;
							  /* Initialize OpenGL Graphics */
void initGL() {
	temp1 = double((y3 - y)) / (x1 - x);
	temp2 = double((x2 - x1))/(y2-y3);
	step1 = abs((x1 - x)) / 0.1;
	step2 = abs((y2 - y3)) / 0.1;

	ccc = 0;
	ddd = 0;
	aaa = x1 > x ? 0.1 : -0.1;
	bbb = y2 > y3 ? 0.1 : -0.1;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}



/* Handler for window-repaint event. Called back when the window first appears and
whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

			
			  // Render a pyramid consists of 4 triangles
	glLoadIdentity();                  // Reset the model-view matrix
	//glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen
	glRotatef(anglePyramid, 1.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis [NEW]
	//glScalef(1.0f, 1.0f, 1.0f);
	glTranslatef(movex1, movey1, 0);
	glTranslatef(movex2, movey2, 0);
	glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
									 // Front
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 0.3f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(-0.3f, -0.3f, 0.3f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(0.3f, -0.3f, 0.3f);

	// Right
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 0.3f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(0.3f, -0.3f, 0.3f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(0.3f, -0.3f, -0.3f);

	// Back
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 0.3f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(0.3f, -0.3f, -0.3f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-0.3f, -0.3f, -0.3f);

	// Left
	glColor3f(1.0f, 0.0f, 0.0f);       // Red
	glVertex3f(0.0f, 0.3f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);       // Blue
	glVertex3f(-0.3f, -0.3f, -0.3f);
	glColor3f(0.0f, 1.0f, 0.0f);       // Green
	glVertex3f(-0.3f, -0.3f, 0.3f);
	glEnd();   // Done drawing the pyramid
	
	glLoadIdentity();
	glBegin(GL_POINTS);

	glColor3f(1, 0, 0);
	glVertex2f(-1.5f, -1.5f); //中间位置
	
	glColor3f(1, 0, 0); 
	glVertex2f(-1, 0.5);	//最后位置	
    glEnd();

	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

						// Update the rotational angle after each refresh [NEW]
	anglePyramid += 0.2f;
	

	
	
	if (ccc<step1) {
		movex1 += aaa;
		movey1 += aaa*temp1;
		ccc += 1;
		
	}

	else {
		if (ddd < step2) {
			movey2 += bbb;
			movex2 += bbb*temp2;
			ddd += 1;
		}
	}
	Sleep(100);
}

/* Called back when timer expired [NEW] */
void timer(int value) {
	glutPostRedisplay();      // Post re-paint request to activate display()
	glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
											   // Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
								  // Enable perspective projection with fovy, aspect, zNear and zFar
	//gluPerspective(1.0f, aspect, 0.01f, 200.0f);
	glOrtho(-2, 2, -2, 2, -10, 10);
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(640, 480);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	initGL();                       // Our own OpenGL initialization
	glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}