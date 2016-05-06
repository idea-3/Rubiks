#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <stdint.h>
#include <fstream>
#include <iostream>

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

string textures[7]={"white.bmp", "orange.bmp", "blue.bmp", "green.bmp", "yellow.bmp", "red.bmp", "grey.bmp"};

GLfloat theta = 0;
char keyPressed;
int rotationSign = 0;
//int rubiksColor[6][9];
GLuint rubiksColor[6][9];
int angleX = 0, angleY = 0, angleZ = 0;
int xRot = 25, yRot = -30, xDiff = 0, yDiff = 0;
bool rotationComplete = true, mouseDown = false;

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

GLuint LoadBMP(const char *fileName)
{
  FILE *file;
  unsigned char header[54];
  unsigned int dataPos;
  unsigned int size;
  unsigned int width, height;
  unsigned char *data;
  

  file = fopen(fileName, "rb");

  if (file == NULL)
  {
    cout << "Error: Invaild file path!" << endl;
    return false;
  }

  if (fread(header, 1, 54, file) != 54)
  {
    cout << "Error: Invaild file!" << endl;;
    return false;
  }

  if (header[0] != 'B' || header[1] != 'M')
  {
    cout << "Error: Invaild file!" << endl;
    return false;
  }

  dataPos   = *(int*)&(header[0x0A]);
  size    = *(int*)&(header[0x22]);
  width   = *(int*)&(header[0x12]);
  height    = *(int*)&(header[0x16]);

  if (size == 0)
    size = width * height * 3;
  if (dataPos == 0)
    dataPos = 54;

  data = new unsigned char[size];

  fread(data, 1, size, file);

  fclose(file);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

  delete [] data;
  return texture;
}

void initiateRubiksColor() {
  for (int i = 0; i < 6; i++) {
    // char *location = new char[textures[i].length() + 1];
    // strcpy(location, textures[i].c_str());
    // GLuint texture = 4721584/*= LoadBMP(location)*/;
    // cout << LoadBMP(location) << endl;
    for (int j = 0; j < 9; j++) {
      rubiksColor[i][j] = i;
    }
    //delete [] location;
  }
}


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
  char *location = new char[textures[colorIndex].length() + 1];
  strcpy(location, textures[colorIndex].c_str());
  GLuint texture = LoadBMP(location);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, texture);
  // glColor3fv(color[colorIndex]);
  glBegin(GL_POLYGON);
  glTexCoord2i(0, 0);
  glVertex3fv(P1);
  glTexCoord2i(0, 1);
  glVertex3fv(P2);
  glTexCoord2i(1, 1);
  glVertex3fv(P3);
  glTexCoord2i(1, 0);
  glVertex3fv(P4);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDeleteTextures(1, &texture);
  delete [] location;
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
    drawSquare(P1,P2,P3,P4,rubiksColor[2][i + j * 3]);
  } else {
    drawSquare(P1,P2,P3,P4,6);
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
    drawSquare(P1,P2,P3,P4,rubiksColor[3][temp + j * 3]);
  } else {
    drawSquare(P1,P2,P3,P4,6);
  }
  // Sisi atas
  P1[1] += squareSize;
  P1[2] += squareSize;
  P2[1] += squareSize;
  P2[2] += squareSize;
  if (j == 2) {
    drawSquare(P1,P2,P3,P4,rubiksColor[0][i + k * 3]);
  } else {
    drawSquare(P1,P2,P3,P4,6);
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
    drawSquare(P1,P2,P3,P4,rubiksColor[1][i + temp * 3]);
  } else {
    drawSquare(P1,P2,P3,P4,6);
  }
  // Sisi kiri
  P2[1] += squareSize;
  P2[0] -= squareSize;
  P3[1] += squareSize;
  P3[0] -= squareSize;
  if (i == 0) {
    drawSquare(P1,P2,P3,P4,rubiksColor[4][k + j * 3]);
  } else {
    drawSquare(P1,P2,P3,P4,6);
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
    drawSquare(P1,P2,P3,P4,rubiksColor[5][temp + j * 3]);
  } else {
    drawSquare(P1,P2,P3,P4,6);
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

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glPushMatrix();
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

// Memutar bagian rubiks sesuai masukkan keyboard pengguna
void rotate() {
  theta += 20.0;

  if (theta == 360) {
    theta -= 360;
  }

  if (theta >= 90) {
    rotationComplete = true;
    glutIdleFunc(NULL);
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
    case 'q':
      keyPressed = 'q';
      rotationComplete = false;
      glutIdleFunc(rotate);
      break;
    case 'w':
      keyPressed = 'w';
      rotationComplete = false;
      glutIdleFunc(rotate);
      break;
    case 'e':
      keyPressed = 'e';
      rotationComplete = false;
      glutIdleFunc(rotate);
      break;
    case 'r':
      keyPressed = 'r';
      rotationComplete = false;
      glutIdleFunc(rotate);
      break;
    case 'a':
      keyPressed = 'a';
      rotationComplete = false;
      glutIdleFunc(rotate);
      break;
    case 's':
      keyPressed = 's';
      rotationComplete = false;
      glutIdleFunc(rotate);
      break;
    case 'd':
      keyPressed = 'd';
      rotationComplete = false;
      glutIdleFunc(rotate);
      break;
    case 'f':
      keyPressed = 'f';
      rotationComplete = false;
      glutIdleFunc(rotate);
      break;
    case 'z':
      keyPressed = 'z';
      rotationComplete = false;
      glutIdleFunc(rotate);
      break;
    case 'x':
      keyPressed = 'x';
      rotationComplete = false;
      glutIdleFunc(rotate);
      break;
    case 'c':
      keyPressed = 'c';
      rotationComplete = false;
      glutIdleFunc(rotate);
      break;
    case 'v':
      keyPressed = 'v';
      rotationComplete = false;
      glutIdleFunc(rotate);
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
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}