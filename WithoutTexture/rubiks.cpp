#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat squareSize = 2, lineWidth = 3;
GLfloat color[][3]={{1.0,1.0,1.0},  // White
                    {1.0,0.5,0.0},  // Orange
                    {0.0,0.0,1.0},  // Blue
                    {0.0,1.0,0.0},  // Green
                    {1.0,1.0,0.0},  // Yellow
                    {1.0,0.0,0.0}, 	// Red
                    {0.5,0.5,0.5} // Grey
};
GLfloat degrees[3][3][3][3];
char keyPressed;
int rotationSign = 0;

void drawSquare(GLfloat P1[], GLfloat P2[], GLfloat P3[], GLfloat P4[], int colorIndex) {
	// Membuat garis luar kotak
	glColor3f(0, 0, 0);
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	glVertex3fv(P1);
	glVertex3fv(P2);
	glVertex3fv(P3);
	glVertex3fv(P4);
	glEnd();
	// Membuat kotak
	glColor3fv(color[colorIndex]);
	glBegin(GL_POLYGON);
	glVertex3fv(P1);
	glVertex3fv(P2);
	glVertex3fv(P3);
	glVertex3fv(P4);
	glEnd();
}

void drawCube(int i, int j, int k) {
	GLfloat initialPoint[] = {-3,-3,3};
	GLfloat x = i*squareSize + initialPoint[0];
	GLfloat y = j*squareSize + initialPoint[1];
	GLfloat z = initialPoint[2] - k*squareSize;
	// Sisi depan
	GLfloat P1[] = {x,y,z};
	GLfloat P2[] = {x+squareSize,y,z};
	GLfloat P3[] = {x+squareSize,y+squareSize,z};
	GLfloat P4[] = {x,y+squareSize,z};
	if (k == 0) {
		drawSquare(P1,P2,P3,P4,0);
	} else {
		drawSquare(P1,P2,P3,P4,6);
	}
	// Sisi belakang
	P1[2] -= squareSize;
	P2[2] -= squareSize;
	P3[2] -= squareSize;
	P4[2] -= squareSize;
	if (k == 2) {
		drawSquare(P1,P2,P3,P4,1);
	} else {
		drawSquare(P1,P2,P3,P4,6);
	}
	// Sisi atas
	P1[1] += squareSize;
	P1[2] += squareSize;
	P2[1] += squareSize;
	P2[2] += squareSize;
	if (j == 2) {
		drawSquare(P1,P2,P3,P4,2);
	} else {
		drawSquare(P1,P2,P3,P4,6);
	}
	// Sisi bawah
	P1[1] -= squareSize;
	P2[1] -= squareSize;
	P3[1] -= squareSize;
	P4[1] -= squareSize;
	if (j == 0) {
		drawSquare(P1,P2,P3,P4,3);
	} else {
		drawSquare(P1,P2,P3,P4,6);
	}
	// Sisi kiri
	P2[1] += squareSize;
	P2[0] -= squareSize;
	P3[1] += squareSize;
	P3[0] -= squareSize;
	if (i == 0) {
		drawSquare(P1,P2,P3,P4,4);
	} else {
		drawSquare(P1,P2,P3,P4,6);
	}
	// Sisi kanan
	P1[0] += squareSize;
	P2[0] += squareSize;
	P3[0] += squareSize;
	P4[0] += squareSize;
	if (i == 2) {
		drawSquare(P1,P2,P3,P4,5);
	} else {
		drawSquare(P1,P2,P3,P4,6);
	}
}

void drawRubiks() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				glLoadIdentity();
				glRotatef(25+degrees[i][j][k][0],1,0,0);
				glRotatef(-30+degrees[i][j][k][1],0,1,0);
				glRotatef(degrees[i][j][k][2],0,0,1);
				drawCube(i, j, k);
			}
		}
	}
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width <= height) {
		glOrtho(-10.0,10.0,-10.0*(GLfloat)height/(GLfloat)width, 10.0*(GLfloat)height/(GLfloat)width,-10.0,10.0);
	} else {
		glOrtho(-10.0*(GLfloat)width/(GLfloat)height, 10.0*(GLfloat)width/(GLfloat)height,-10.0,10.0,-10.0,10.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	drawRubiks();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void rotate() {
	if (rotationSign >= 180) {
		rotationSign = 0;
		glutIdleFunc(NULL);
	} else {
		if (keyPressed == 'q') {
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					degrees[i][2][k][1] += 0.5;
				}
			}
		}
		rotationSign++;
		glutPostRedisplay();
	}
}

void keyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		case '1':
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						degrees[i][j][k][0] += 5;
					}
				}
			}
			glutPostRedisplay();
			break;
		case '2':
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						degrees[i][j][k][0] -= 5;
					}
				}
			}
			glutPostRedisplay();
			break;
		case '3':
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						degrees[i][j][k][1] += 5;
					}
				}
			}
			glutPostRedisplay();
			break;
		case '4':
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						degrees[i][j][k][1] -= 5;
					}
				}
			}
			glutPostRedisplay();
			break;
		case '5':
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						degrees[i][j][k][2] += 5;
					}
				}
			}
			glutPostRedisplay();
			break;
		case '6':
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						degrees[i][j][k][2] -= 5;
					}
				}
			}
			glutPostRedisplay();
			break;
		case 'q':
			keyPressed = 'q';
			glutIdleFunc(rotate);
			break;
	}
}

void initiateDegrees() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					degrees[i][j][k][l] = 0;
				}
			}
		}
	}
}

int main(int argc, char** argv) {
	initiateDegrees();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("RUBIK'S CUBE");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardFunc);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}