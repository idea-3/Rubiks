#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>

using namespace std;

GLfloat squareSize = 2, lineWidth = 10;
GLfloat color[][3]={{1.0,1.0,1.0},  // White
                    {1.0,0.5,0.0},  // Orange
                    {0.0,0.0,1.0},  // Blue
                    {0.0,1.0,0.0},  // Green
                    {1.0,1.0,0.0},  // Yellow
                    {1.0,0.0,0.0},  // Red
                    {0.5,0.5,0.5} // Grey
};
GLfloat lightColor[][3]={{1.0,1.0,1.0},
                        {0.3,0.0,0.0},
                        {0.0,0.3,0.0},
                        {0.0,0.0,0.3},
                        {0.0,0.0,0.0}
};
GLfloat theta = 0;
char keyPressed;
int rotationSign = 0;
int rubiksColor[6][9];
int angleX = 0, angleY = 0, angleZ = 0;
int xRot = 0, yRot = 0, xDiff = 0, yDiff = 0;
int lightColorIndex = 0;
int movementIndex = -1;
bool rotationComplete = true, mouseDown = false, isSolving = false;
float rLight = lightColor[lightColorIndex][0], gLight = lightColor[lightColorIndex][1], bLight = lightColor[lightColorIndex][2];
vector<char> movement;

/* 
  PANDUAN MENGGAMBAR
  Tampak atas rubiksColor[0][], bawah rubiksColor[1][], depan rubiksColor[2][]
    6 7 8
    3 4 5
    0 1 2

  Tampak belakang rubiksColor[3][], kiri rubiksColor[4][], kanan rubiksColor[5][]
    8 7 6
    5 4 3
    2 1 0
*/

void initiateRubiksColor() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 9; j++) {
      rubiksColor[i][j] = i;
    }
  }
}

void drawSquare(GLfloat P1[], GLfloat P2[], GLfloat P3[], GLfloat P4[], int colorIndex, GLfloat normal[]) {
  // Membuat garis luar kotak
  glColor3f(0, 0, 0);
  glLineWidth(lineWidth);
  glBegin(GL_LINE_LOOP);
  // glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3fv(P1);
  glVertex3fv(P2);
  glVertex3fv(P3);
  glVertex3fv(P4);
  glEnd();
  // Membuat kotak
  float specReflection[] = { 1.0f, 1.0f, 1.0f, 0.1f };
  glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
  glMateriali(GL_FRONT, GL_SHININESS, 128);

  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glColor3fv(color[colorIndex]);
  glBegin(GL_POLYGON);

  glNormal3f(normal[0], normal[1], normal[2]);
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
    //glNormal3f(0, 0, 1);
    GLfloat normal[] = {0, 0, 1};
    // GLfloat* normal = countNormal(P1, P2, P3, P4);
    drawSquare(P1,P2,P3,P4,rubiksColor[2][i + j * 3], normal);
  } else {
    GLfloat normal[] = {0, 0, 0};
    drawSquare(P1,P2,P3,P4,6,normal);
  }
  // Sisi belakang
  P1[2] -= squareSize;
  P2[2] -= squareSize;
  P3[2] -= squareSize;
  P4[2] -= squareSize;
  if (k == 2) {
    int temp = 1;
    if (i == 0) {
      temp = 2;
    } else if (i == 2) {
      temp = 0;
    }
    //glNormal3f(0, 0, -1);
    GLfloat normal[] = {0, 0, -1};
    drawSquare(P1,P2,P3,P4,rubiksColor[3][temp + j * 3], normal);
  } else {
    GLfloat normal[] = {0, 0, 0};
    drawSquare(P1,P2,P3,P4,6,normal);
  }
  // Sisi atas
  P1[1] += squareSize;
  P1[2] += squareSize;
  P2[1] += squareSize;
  P2[2] += squareSize;
  if (j == 2) {
    // glNormal3f(0, 1, 0);
    GLfloat normal[] = {0, 1, 0};
    drawSquare(P1,P2,P3,P4,rubiksColor[0][i + k * 3], normal);
  } else {
    GLfloat normal[] = {0, 0, 0};
    drawSquare(P1,P2,P3,P4,6,normal);
  }
  // Sisi bawah
  P1[1] -= squareSize;
  P2[1] -= squareSize;
  P3[1] -= squareSize;
  P4[1] -= squareSize;
  if (j == 0) {
    int temp = 1;
    if (k == 0) {
      temp = 2;
    } else if (k == 2) {
      temp = 0;
    }
    // glNormal3f(0, -1, 0);
    GLfloat normal[] = {0, -1, 0};
    drawSquare(P1,P2,P3,P4,rubiksColor[1][i + temp * 3], normal);
  } else {
    GLfloat normal[] = {0, 0, 0};
    drawSquare(P1,P2,P3,P4,6,normal);
  }
  // Sisi kiri
  P2[1] += squareSize;
  P2[0] -= squareSize;
  P3[1] += squareSize;
  P3[0] -= squareSize;
  if (i == 0) {
    // glNormal3f(1, 0, 0);
    GLfloat normal[] = {-1, 0, 0};
    drawSquare(P1,P2,P3,P4,rubiksColor[4][k + j * 3], normal);
  } else {
    GLfloat normal[] = {0, 0, 0};
    drawSquare(P1,P2,P3,P4,6,normal);
  }
  // Sisi kanan
  P1[0] += squareSize;
  P2[0] += squareSize;
  P3[0] += squareSize;
  P4[0] += squareSize;
  if (i == 2) {
    int temp = 1;
    if (k == 0) {
      temp = 2;
    } else if (k == 2) {
      temp = 0;
    }
    // glNormal3f(1, 0, 0);
    GLfloat normal[] = {1, 0, 0};
    drawSquare(P1,P2,P3,P4,rubiksColor[5][temp + j * 3], normal);
  } else {
    GLfloat normal[] = {0, 0, 0};
    drawSquare(P1,P2,P3,P4,6,normal);
  }
}

void drawRubiks() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        glLoadIdentity();
        glRotatef(xRot+angleX,1,0,0);
        glRotatef(yRot+angleY,0,1,0);
        glRotatef(angleZ,0,0,1);
        switch (keyPressed) {
          case 'q':
            if (j == 2) {
              glRotatef(-theta, 0, 1, 0); 
            }
            break;
          case 'w':
            if (j == 2) {
              glRotatef(theta, 0, 1, 0); 
            }
            break;
          case 'e':
            if (j == 0) {
              glRotatef(-theta, 0, 1, 0); 
            }
            break;
          case 'r':
            if (j == 0) {
              glRotatef(theta, 0, 1, 0); 
            }
            break;
          case 'a':
            if (k == 0) {
              glRotatef(-theta, 0, 0, 1);
            }
            break;
          case 's':
            if (k == 0) {
              glRotatef(theta, 0, 0, 1);
            }
            break;
          case 'd':
            if (k == 2) {
              glRotatef(-theta, 0, 0, 1);
            }
            break;
          case 'f':
            if (k == 2) {
              glRotatef(theta, 0, 0, 1);
            }
            break;
          case 'z':
            if (i == 0) {
              glRotatef(theta, 1, 0, 0);
            }
            break;
          case 'x':
            if (i == 0) {
              glRotatef(-theta, 1, 0, 0);
            }
            break;
          case 'c':
            if (i == 2) {
              glRotatef(theta, 1, 0, 0);
            }
            break;
          case 'v':
            if (i == 2) {
              glRotatef(-theta, 1, 0, 0);
            }
            break;
        }
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

// Membuat lighting
void addLighting() {
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_COLOR_MATERIAL);

  GLfloat ambientLight[] = { 0.1f, 0.1f, 0.1f };
  GLfloat diffuseLight[] = { rLight, gLight, bLight };
  GLfloat specularLight[] = { rLight, gLight, bLight };
  GLfloat position[][4] = { {-3.0f, 3.0f, 5.0f, 1.0f}, {3.0f, 3.0f, 5.0f, 1.0f} };

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, position[0]);

  glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT1, GL_POSITION, position[1]);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glPushMatrix();
  addLighting();
  drawRubiks();
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

/*
  Memutar satu sisi kubus dengan posisi:
  6 7 8
  3 4 5
  0 1 2
*/
void rotateColor(int edge) {
  int temp = rubiksColor[edge][0];
  rubiksColor[edge][0] = rubiksColor[edge][2];
  rubiksColor[edge][2] = rubiksColor[edge][8];
  rubiksColor[edge][8] = rubiksColor[edge][6];
  rubiksColor[edge][6] = temp;

  temp = rubiksColor[edge][1];
  rubiksColor[edge][1] = rubiksColor[edge][5];
  rubiksColor[edge][5] = rubiksColor[edge][7];
  rubiksColor[edge][7] = rubiksColor[edge][3];
  rubiksColor[edge][3] = temp;
}

/*
  Memutar satu sisi kubus dengan posisi:
  8 7 6
  5 4 3
  2 1 0
*/
void rotateColorInverse(int edge) {
  int temp = rubiksColor[edge][2];
  rubiksColor[edge][2] = rubiksColor[edge][0];
  rubiksColor[edge][0] = rubiksColor[edge][6];
  rubiksColor[edge][6] = rubiksColor[edge][8];
  rubiksColor[edge][8] = temp;

  temp = rubiksColor[edge][5];
  rubiksColor[edge][5] = rubiksColor[edge][1];
  rubiksColor[edge][1] = rubiksColor[edge][3];
  rubiksColor[edge][3] = rubiksColor[edge][7];
  rubiksColor[edge][7] = temp;
}

/*
  Tampak atas
        3 -> No. Bidang rubiksColor[i][]
      8 7 6 -> No. persegi rubiksColor[][j]
    8       6
  4 7       7 5
    6       8
      6 7 8
        2
*/
void rotateTop() {
  rotateColor(0);
  int temp[3];

  for (int i=0; i<3; i++) {
    temp[i] = rubiksColor[2][i+6];
  }

  rubiksColor[2][6] = rubiksColor[5][8];
  rubiksColor[2][7] = rubiksColor[5][7];
  rubiksColor[2][8] = rubiksColor[5][6];

  rubiksColor[5][8] = rubiksColor[3][6];
  rubiksColor[5][7] = rubiksColor[3][7];
  rubiksColor[5][6] = rubiksColor[3][8];

  rubiksColor[3][6] = rubiksColor[4][8];
  rubiksColor[3][7] = rubiksColor[4][7];
  rubiksColor[3][8] = rubiksColor[4][6];

  rubiksColor[4][8] = temp[0];
  rubiksColor[4][7] = temp[1];
  rubiksColor[4][6] = temp[2];
}

/*
  Tampak atas
        3 -> No. Bidang rubiksColor[i][]
      2 1 0 -> No. persegi rubiksColor[][j]
    2       0
  4 1       1 5
    0       2
      0 1 2
        2
*/
void rotateBottom() {
  rotateColorInverse(1);
  int temp[3];
  for (int i=0; i<3; i++) {
    temp[i] = rubiksColor[2][i];
  }

  rubiksColor[2][0] = rubiksColor[5][2];
  rubiksColor[2][1] = rubiksColor[5][1];
  rubiksColor[2][2] = rubiksColor[5][0];

  rubiksColor[5][2] = rubiksColor[3][0];
  rubiksColor[5][1] = rubiksColor[3][1];
  rubiksColor[5][0] = rubiksColor[3][2];

  rubiksColor[3][0] = rubiksColor[4][2];
  rubiksColor[3][1] = rubiksColor[4][1];
  rubiksColor[3][2] = rubiksColor[4][0];

  rubiksColor[4][2] = temp[0];
  rubiksColor[4][1] = temp[1];
  rubiksColor[4][0] = temp[2];
}

/*
  Tampak depan
        0 -> No. Bidang rubiksColor[i][]
      0 1 2 -> No. persegi rubiksColor[][j]
    6       8
  4 3       5 5
    0       2
      6 7 8
        1
*/
void rotateFront() {
  rotateColor(2);
  int temp[3];
  for (int i=0; i<3; i++) {
    temp[i] = rubiksColor[0][i];
  }

  rubiksColor[0][0] = rubiksColor[4][0];
  rubiksColor[0][1] = rubiksColor[4][3];
  rubiksColor[0][2] = rubiksColor[4][6];

  rubiksColor[4][0] = rubiksColor[1][8];
  rubiksColor[4][3] = rubiksColor[1][7];
  rubiksColor[4][6] = rubiksColor[1][6];

  rubiksColor[1][8] = rubiksColor[5][8];
  rubiksColor[1][7] = rubiksColor[5][5];
  rubiksColor[1][6] = rubiksColor[5][2];

  rubiksColor[5][8] = temp[0];
  rubiksColor[5][5] = temp[1];
  rubiksColor[5][2] = temp[2];
}

/*
  Tampak depan
        0 -> No. Bidang rubiksColor[i][]
      6 7 8 -> No. persegi rubiksColor[][j]
    8       6
  4 5       3 5
    2       0
      0 1 2
        1
*/
void rotateBack() {
  rotateColorInverse(3);
  int temp[3];

  for (int i=0; i<3; i++) {
    temp[i] = rubiksColor[0][i+6];
  }

  rubiksColor[0][6] = rubiksColor[4][2];
  rubiksColor[0][7] = rubiksColor[4][5];
  rubiksColor[0][8] = rubiksColor[4][8];

  rubiksColor[4][2] = rubiksColor[1][2];
  rubiksColor[4][5] = rubiksColor[1][1];
  rubiksColor[4][8] = rubiksColor[1][0];

  rubiksColor[1][2] = rubiksColor[5][6];
  rubiksColor[1][1] = rubiksColor[5][3];
  rubiksColor[1][0] = rubiksColor[5][0];

  rubiksColor[5][6] = temp[0];
  rubiksColor[5][3] = temp[1];
  rubiksColor[5][0] = temp[2];
}

/*
  Tampak kiri
        0 -> No. Bidang rubiksColor[i][]
      6 3 0 -> No. persegi rubiksColor[][j]
    8       6
  3 5       3 2
    2       0
      0 3 6
        1
*/
void rotateLeft() {
  rotateColorInverse(4);
  int temp[3];

  temp[0] = rubiksColor[0][6];
  temp[1] = rubiksColor[0][3];
  temp[2] = rubiksColor[0][0];

  rubiksColor[0][6] = rubiksColor[3][2];
  rubiksColor[0][3] = rubiksColor[3][5];
  rubiksColor[0][0] = rubiksColor[3][8];

  rubiksColor[3][2] = rubiksColor[1][6];
  rubiksColor[3][5] = rubiksColor[1][3];
  rubiksColor[3][8] = rubiksColor[1][0];

  for (int i=0; i<=6; i+=3) {
    rubiksColor[1][i] = rubiksColor[2][i];
  }

  rubiksColor[2][6] = temp[0];
  rubiksColor[2][3] = temp[1];
  rubiksColor[2][0] = temp[2];
}

/*
  Tampak kiri
        0 -> No. Bidang rubiksColor[i][]
      8 5 2 -> No. persegi rubiksColor[][j]
    6       8
  3 3       5 2
    0       2
      2 5 8
        1
*/
void rotateRight() {
  rotateColor(5);
  int temp[3];

  temp[0] = rubiksColor[0][8];
  temp[1] = rubiksColor[0][5];
  temp[2] = rubiksColor[0][2];

  rubiksColor[0][8] = rubiksColor[3][0];
  rubiksColor[0][5] = rubiksColor[3][3];
  rubiksColor[0][2] = rubiksColor[3][6];

  rubiksColor[3][0] = rubiksColor[1][8];
  rubiksColor[3][3] = rubiksColor[1][5];
  rubiksColor[3][6] = rubiksColor[1][2];

  for (int i=2; i<=8; i+=3) {
    rubiksColor[1][i] = rubiksColor[2][i];
  }

  rubiksColor[2][8] = temp[0];
  rubiksColor[2][5] = temp[1];
  rubiksColor[2][2] = temp[2];
}

void reverseMovement() {
  switch (movement[movementIndex]) {
      case 'q':
      keyPressed = 'w';
      break;
    case 'w':
      keyPressed = 'q';
      break;
    case 'e':
      keyPressed = 'r';
      break;
    case 'r':
      keyPressed = 'e';
      break;
    case 'a':
      keyPressed = 's';
      break;
    case 's':
      keyPressed = 'a';
      break;
    case 'd':
      keyPressed = 'f';
      break;
    case 'f':
      keyPressed = 'd';
      break;
    case 'z':
      keyPressed = 'x';
      break;
    case 'x':
      keyPressed = 'z';
      break;
    case 'c':
      keyPressed = 'v';
      break;
    case 'v':
      keyPressed = 'c';
      break;
    }
}

// Memutar bagian rubiks sesuai masukkan keyboard pengguna
void rotate() {
  if (theta == 0 && isSolving) {
    reverseMovement();
  }

  theta += 0.5;

  if (theta == 360) {
    theta -= 360;
  }

  if (theta >= 90) {
    if (!isSolving) {
      rotationComplete = true;
      if (!movement.empty()) {
        int lastIndex = movement.size() - 1;
        switch (keyPressed) {
          case 'q':
            if (movement[lastIndex] != 'w') {
              movement.push_back(keyPressed);
            } else {
              movement.pop_back();
            }
            break;
          case 'w':
            if (movement[lastIndex] != 'q') {
              movement.push_back(keyPressed);
            } else {
              movement.pop_back();
            }
            break;
          case 'e':
            if (movement[lastIndex] != 'r') {
              movement.push_back(keyPressed);
            } else {
              movement.pop_back();
            }
            break;
          case 'r':
            if (movement[lastIndex] != 'e') {
              movement.push_back(keyPressed);
            } else {
              movement.pop_back();
            }
            break;
          case 'a':
            if (movement[lastIndex] != 's') {
              movement.push_back(keyPressed);
            } else {
              movement.pop_back();
            }
            break;
          case 's':
            if (movement[lastIndex] != 'a') {
              movement.push_back(keyPressed);
            } else {
              movement.pop_back();
            }
            break;
          case 'd':
            if (movement[lastIndex] != 'f') {
              movement.push_back(keyPressed);
            } else {
              movement.pop_back();
            }
            break;
          case 'f':
            if (movement[lastIndex] != 'd') {
              movement.push_back(keyPressed);
            } else {
              movement.pop_back();
            }
            break;
          case 'z':
            if (movement[lastIndex] != 'x') {
              movement.push_back(keyPressed);
            } else {
              movement.pop_back();
            }
            break;
          case 'x':
            if (movement[lastIndex] != 'z') {
              movement.push_back(keyPressed);
            } else {
              movement.pop_back();
            }
            break;
          case 'c':
            if (movement[lastIndex] != 'v') {
              movement.push_back(keyPressed);
            } else {
              movement.pop_back();
            }
            break;
          case 'v':
            if (movement[lastIndex] != 'c') {
              movement.push_back(keyPressed);
            } else {
              movement.pop_back();
            }
            break;
        }
      } else {
        movement.push_back(keyPressed);
      }
      glutIdleFunc(NULL);
    } else {
      if (movementIndex == 0) {
        rotationComplete = true;
        movement.clear();
        isSolving = false;
        glutIdleFunc(NULL);
      }
      movementIndex--;
    }
    switch (keyPressed) {
      case 'q':
        rotateTop();
        break;
      case 'w':
        rotateTop();
        rotateTop();
        rotateTop();
        break;
      case 'e':
        rotateBottom();
        break;
      case 'r':
        rotateBottom();
        rotateBottom();
        rotateBottom();
        break;
      case 'a':
        rotateFront();
        break;
      case 's':
        rotateFront();
        rotateFront();
        rotateFront();
        break;
      case 'd':
        rotateBack();
        break;
      case 'f':
        rotateBack();
        rotateBack();
        rotateBack();
        break;
      case 'z':
        rotateLeft();
        break;
      case 'x':
        rotateLeft();
        rotateLeft();
        rotateLeft();
        break;
      case 'c':
        rotateRight();
        break;
      case 'v':
        rotateRight();
        rotateRight();
        rotateRight();
        break;
    }
    theta = 0;
  }
  glutPostRedisplay();
}

void solveRubiks() {
  if (!movement.empty()) {
    movementIndex = movement.size() - 1;
    isSolving = true;
    rotationComplete = false;
    glutIdleFunc(rotate);
  }
}

// Memutar bagian rubiks dan memutar seluruh bagian rubiks sesuai masukkan pengguna
void keyboardFunc(unsigned char key, int x, int y) {
  switch (key) {
    case '1':
      angleX += 5;
      glutPostRedisplay();
      break;
    case '2':
      angleX -= 5;
      glutPostRedisplay();
      break;
    case '3':
      angleY += 5;
      glutPostRedisplay();
      break;
    case '4':
      angleY -= 5;
      glutPostRedisplay();
      break;
    case '5':
      angleZ += 5;
      glutPostRedisplay();
      break;
    case '6':
      angleZ -= 5;
      glutPostRedisplay();
      break;
    case '=':
      rLight += 0.1f;
      gLight += 0.1f;
      bLight += 0.1f;
      glutPostRedisplay();
      break;
    case '-':
      rLight -= 0.1f;
      gLight -= 0.1f;
      bLight -= 0.1f;
      glutPostRedisplay();
      break;
    case '`':
      if (lightColorIndex == 4) {
        lightColorIndex = 0;
      } else {
        lightColorIndex++;
      }
      rLight = lightColor[lightColorIndex][0];
      gLight = lightColor[lightColorIndex][1];
      bLight = lightColor[lightColorIndex][2];
      glutPostRedisplay();
      break;
    case 'q':
    case 'w':
    case 'e':
    case 'r':
    case 'a':
    case 's':
    case 'd':
    case 'f':
    case 'z':
    case 'x':
    case 'c':
    case 'v':
      keyPressed = key;
      rotationComplete = false;
      glutIdleFunc(rotate);
      break;
    case '0':
      solveRubiks();
      break;
    case 't':
      rLight += 0.2;
      glutPostRedisplay();
      break;
    case 'y':
      rLight -= 0.2;
      glutPostRedisplay();
      break;
    case 'g':
      gLight += 0.2;
      glutPostRedisplay();
      break;
    case 'h':
      gLight -= 0.2;
      glutPostRedisplay();
      break;
    case 'b':
      bLight += 0.2;
      glutPostRedisplay();
      break;
    case 'n':
      bLight -= 0.2;
      glutPostRedisplay();
      break;  
  }
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    mouseDown = true;
    xDiff = x - yRot;
    yDiff = -y + xRot;
  } else {
    mouseDown = false; 
  }
}

void mouseMotion(int x, int y) {
  if (mouseDown) {
    xRot = y + yDiff;
    yRot = x - xDiff;
    glutPostRedisplay();
  }
}

int main(int argc, char** argv) {
  initiateRubiksColor();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 0);
  glutCreateWindow("IDEA'S RUBIKS");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardFunc);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);

  addLighting();

  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}