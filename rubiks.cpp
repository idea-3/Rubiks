#include <windows.h>
#include <string.h>
#include <GL/glut.h>

static int top[3][3]={{0,0,0},{0,0,0},{0,0,0}},
right[3][3]={{1,1,1},{1,1,1},{1,1,1}},
front[3][3]={{2,2,2},{2,2,2},{2,2,2}},
back[3][3]={{3,3,3},{3,3,3},{3,3,3}},
bottom[3][3]={{4,4,4},{4,4,4},{4,4,4}},
left[3][3]={{5,5,5},{5,5,5},{5,5,5}},
temp[3][3];

static GLfloat p=0.0,q=0.0,r=0.0;

GLfloat vertices[][3]={ //center
						{-1.0,-1.0,-1.0},
                       	{1.0,-1.0,-1.0},
                       	{1.0,1.0,-1.0},
                       	{-1.0,1.0,-1.0},
                       	{-1.0,-1.0,1.0},
                       	{1.0,-1.0,1.0},
                       	{1.0,1.0,1.0},
                       	{-1.0,1.0,1.0},

                       	// Bottom center
                       	{-1.0,-3.0,-1.0},
                       	{1.0,-3.0,-1.0},
                       	{1.0,-1.0,-1.0},
                       	{-1.0,-1.0,-1.0},
                       	{-1.0,-3.0,1.0},
                       	{1.0,-3.0,1.0},
                       	{1.0,-1.0,1.0},
                       	{-1.0,-1.0,1.0},

                       	// Left center
                       	{-3.0,-1.0,-1.0},
                       	{-1.0,-1.0,-1.0},
                       	{-1.0,1.0,-1.0},
                       	{-3.0,1.0,-1.0},
                       	{-3.0,-1.0,1.0},
                       	{-1.0,-1.0,1.0},
                       	{-1.0,1.0,1.0},
                       	{-3.0,1.0,1.0},

                       	// Right center
                       	{1.0,-1.0,-1.0},
                       	{3.0,-1.0,-1.0},
                       	{3.0,1.0,-1.0},
                       	{1.0,1.0,-1.0},
                       	{1.0,-1.0,1.0},
                       	{3.0,-1.0,1.0},
                       	{3.0,1.0,1.0},
                       	{1.0,1.0,1.0},

                       	// Top center
                       	{-1.0,1.0,-1.0},
                       	{1.0,1.0,-1.0},
                       	{1.0,3.0,-1.0},
                       	{-1.0,3.0,-1.0},
                       	{-1.0,1.0,1.0},
                       	{1.0,1.0,1.0},
                       	{1.0,3.0,1.0},
                       	{-1.0,3.0,1.0},

                       	// Front center
                       	{-1.0,-1.0,1.0},
                       	{1.0,-1.0,1.0},
                       	{1.0,1.0,1.0},
                       	{-1.0,1.0,1.0},
                       	{-1.0,-1.0,3.0},
                       	{1.0,-1.0,3.0},
                       	{1.0,1.0,3.0},
                       	{-1.0,1.0,3.0},

                       	// Back center
                       	{-1.0,-1.0,-3.0},
                       	{1.0,-1.0,-3.0},
                       	{1.0,1.0,-3.0},
                       	{-1.0,1.0,-3.0},
                       	{-1.0,-1.0,-1.0},
                       	{1.0,-1.0,-1.0},
                       	{1.0,1.0,-1.0},
                       	{-1.0,1.0,-1.0},		

                       	// Top left center
                       	{-3.0,1.0,-1.0},
                       	{-1.0,1.0,-1.0},
                       	{-1.0,3.0,-1.0},
                       	{-3.0,3.0,-1.0},
                       	{-3.0,1.0,1.0},
                       	{-1.0,1.0,1.0},
                       	{-1.0,3.0,1.0},
                       	{-3.0,3.0,1.0},

                       	// Top right center
                       	{1.0,1.0,-1.0},
                       	{3.0,1.0,-1.0},
                       	{3.0,3.0,-1.0},
                       	{1.0,3.0,-1.0},
                       	{1.0,1.0,1.0},
                       	{3.0,1.0,1.0},
                       	{3.0,3.0,1.0},
                       	{1.0,3.0,1.0},

                       	// Top front center
                       	{-1.0,1.0,1.0},
                       	{1.0,1.0,1.0},
                       	{1.0,3.0,1.0},
                       	{-1.0,3.0,1.0},
                       	{-1.0,1.0,3.0},
                       	{1.0,1.0,3.0},
                       	{1.0,3.0,3.0},
                       	{-1.0,3.0,3.0},

                       	// Top back center
                       	{-1.0,1.0,-3.0},
                       	{1.0,1.0,-3.0},
                       	{1.0,3.0,-3.0},
                       	{-1.0,3.0,-3.0},
                       	{-1.0,1.0,-1.0},
                       	{1.0,1.0,-1.0},
                       	{1.0,3.0,-1.0},
                       	{-1.0,3.0,-1.0},

                       	// Bottom left center
					   	{-3.0,-3.0,-1.0},
                       	{-1.0,-3.0,-1.0},
                       	{-1.0,-1.0,-1.0},
                       	{-3.0,-1.0,-1.0}, 
                       	{-3.0,-3.0,1.0},
                       	{-1.0,-3.0,1.0},
                       	{-1.0,-1.0,1.0},
                       	{-3.0,-1.0,1.0},

                       	// Bottom  right center
					   	{1.0,-3.0,-1.0},
                       	{3.0,-3.0,-1.0},
                       	{3.0,-1.0,-1.0},
                       	{1.0,-1.0,-1.0},  
                       	{1.0,-3.0,1.0},
                       	{3.0,-3.0,1.0},
                       	{3.0,-1.0,1.0},
                       	{1.0,-1.0,1.0},

                       	// Bottom front center
					   	{-1.0,-3.0,1.0},
                       	{1.0,-3.0,1.0},
                       	{1.0,-1.0,1.0},
                       	{-1.0,-1.0,1.0},
                       	{-1.0,-3.0,3.0},
                       	{1.0,-3.0,3.0},
                       	{1.0,-1.0,3.0},
                       	{-1.0,-1.0,3.0},

                       	// Bottom back center
                       	{-1.0,-3.0,-3.0},
                       	{1.0,-3.0,-3.0},
                       	{1.0,-1.0,-3.0},
                       	{-1.0,-1.0,-3.0},  
                       	{-1.0,-3.0,-1.0},
                       	{1.0,-3.0,-1.0},
                       	{1.0,-1.0,-1.0},
                       	{-1.0,-1.0,-1.0},

                       	// Top left back
					   	{-3.0,1.0,-3.0},
                       	{-1.0,1.0,-3.0},
                       	{-1.0,3.0,-3.0},
                       	{-3.0,3.0,-3.0}, 
                       	{-3.0,1.0,-1.0},
                       	{-1.0,1.0,-1.0},
                       	{-1.0,3.0,-1.0},
                       	{-3.0,3.0,-1.0},

                       	// Top left front
					   	{-3.0,1.0,1.0},
                       	{-1.0,1.0,1.0},
                       	{-1.0,3.0,1.0},
                       	{-3.0,3.0,1.0},
                       	{-3.0,1.0,3.0},
                       	{-1.0,1.0,3.0},
                       	{-1.0,3.0,3.0},
                       	{-3.0,3.0,3.0},

                       	// Top right  back
					   	{1.0,1.0,-3.0},
                       	{3.0,1.0,-3.0},
                       	{3.0,3.0,-3.0},
                       	{1.0,3.0,-3.0}, 
                       	{1.0,1.0,-1.0},
                       	{3.0,1.0,-1.0},
                       	{3.0,3.0,-1.0},
                       	{1.0,3.0,-1.0},

                       	// Top right front
					   	{1.0,1.0,1.0},
                       	{3.0,1.0,1.0},
                       	{3.0,3.0,1.0},
                       	{1.0,3.0,1.0}, 
                       	{1.0,1.0,3.0},
                       	{3.0,1.0,3.0},
                       	{3.0,3.0,3.0},
                       	{1.0,3.0,3.0},

                       	// Center left back
					   	{-3.0,-1.0,-3.0},
                       	{-1.0,-1.0,-3.0},
                       	{-1.0,1.0,-3.0},
                       	{-3.0,1.0,-3.0},  
                       	{-3.0,-1.0,-1.0},
                       	{-1.0,-1.0,-1.0},
                       	{-1.0,1.0,-1.0},
                       	{-3.0,1.0,-1.0},

                       	// Center left front
					   	{-3.0,-1.0,1.0},
                       	{-1.0,-1.0,1.0},
                       	{-1.0,1.0,1.0},
                       	{-3.0,1.0,1.0},  
                       	{-3.0,-1.0,3.0},
                       	{-1.0,-1.0,3.0},
                       	{-1.0,1.0,3.0},
                       	{-3.0,1.0,3.0},

                       	// Center right back
					   	{1.0,-1.0,-3.0},
                       	{3.0,-1.0,-3.0},
                       	{3.0,1.0,-3.0},
                       	{1.0,1.0,-3.0}, 
                       	{1.0,-1.0,-1.0},
                       	{3.0,-1.0,-1.0},
                       	{3.0,1.0,-1.0},
                       	{1.0,1.0,-1.0},

                       	// Center right front
					   	{1.0,-1.0,1.0},
                       	{3.0,-1.0,1.0},
                       	{3.0,1.0,1.0},
                       	{1.0,1.0,1.0}, 
                       	{1.0,-1.0,3.0},
                       	{3.0,-1.0,3.0},
                       	{3.0,1.0,3.0},
                       	{1.0,1.0,3.0},

                       	// Bottom left back
					   	{-3.0,-3.0,-3.0},
                       	{-1.0,-3.0,-3.0},
                       	{-1.0,-1.0,-3.0},
                       	{-3.0,-1.0,-3.0},  
                       	{-3.0,-3.0,-1.0},
                       	{-1.0,-3.0,-1.0},
                       	{-1.0,-1.0,-1.0},
                       	{-3.0,-1.0,-1.0},

                       	// Bottom left front
					   	{-3.0,-3.0,1.0},
                       	{-1.0,-3.0,1.0},
                       	{-1.0,-1.0,1.0},
                       	{-3.0,-1.0,1.0},  
                       	{-3.0,-3.0,3.0},
                       	{-1.0,-3.0,3.0},
                       	{-1.0,-1.0,3.0},
                       	{-3.0,-1.0,3.0},

                       	//Bottom right back
					   	{1.0,-3.0,-3.0},
                       	{3.0,-3.0,-3.0},
                       	{3.0,-1.0,-3.0},
                       	{1.0,-1.0,-3.0},  
                       	{1.0,-3.0,-1.0},
                       	{3.0,-3.0,-1.0},
                       	{3.0,-1.0,-1.0},
                       	{1.0,-1.0,-1.0},

                       	// Bottom right front
					   	{1.0,-3.0,1.0},
                       	{3.0,-3.0,1.0},
                       	{3.0,-1.0,1.0},
                       	{1.0,-1.0,1.0},  
                       	{1.0,-3.0,3.0},
                       	{3.0,-3.0,3.0},
                       	{3.0,-1.0,3.0},
                       	{1.0,-1.0,3.0},
};

GLfloat color[][3]={{1.0,1.0,1.0},  // White
                    {1.0,0.5,0.0},  // Orange
                    {0.0,0.0,1.0},  // Blue
                    {0.0,1.0,0.0},  // Green
                    {1.0,1.0,0.0},  // Yellow
                    {1.0,0.0,0.0}, 	// Red
                    {0.5,0.5,0.5} // Grey
};

void polygon(int colorIdx,int b,int c,int d,int e) {

	// Draw outer line
	glColor3f(0,0,0);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glVertex3fv(vertices[e]);
	glEnd();

	// Draw square
	glColor3fv(color[colorIdx]);
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glVertex3fv(vertices[e]);
	glEnd();
}

void colorcube1()
{
	polygon(6,0,3,2,1);
	polygon(6,2,3,7,6);
	polygon(6,0,4,7,3);    // center piece
    polygon(6,1,2,6,5);
	polygon(6,4,5,6,7);
	polygon(6,0,1,5,4);
}
void colorcube2()
{
	polygon(6,8,11,10,9);
	polygon(6,10,11,15,14);
	polygon(6,8,12,15,11);    // bottom center
    polygon(6,9,10,14,13);
	polygon(6,12,13,14,15);
	polygon(bottom[1][1],8,9,13,12);


}

void colorcube3()
{

	polygon(6,16,19,18,17);
	polygon(6,18,19,23,22);
	polygon(left[1][1],16,20,23,19);    // left center
    polygon(6,17,18,22,21);
	polygon(6,20,21,22,23);
	polygon(6,16,17,21,20);


}

void colorcube4()
{
	polygon(6,24,27,26,25);
	polygon(6,26,27,31,30);
	polygon(6,24,28,31,27);    // right center
    polygon(right[1][1],25,26,30,29);
	polygon(6,28,29,30,31);
	polygon(6,24,25,29,28);


}

void colorcube5()
{
	polygon(6,32,35,34,33);
	polygon(top[1][1],34,35,39,38);
	polygon(6,32,36,39,35);    // top center
    polygon(6,33,34,38,37);
	polygon(6,36,37,38,39);
	polygon(6,32,33,37,36);


}

void colorcube6()
{
	polygon(6,40,43,42,41);
	polygon(6,42,43,47,46);
	polygon(6,40,44,47,43);    // front center
    polygon(6,41,42,46,45);
	polygon(front[1][1],44,45,46,47);
	polygon(6,40,41,45,44);


}

void colorcube7()
{
	polygon(back[1][1],48,51,50,49);
	polygon(6,50,51,55,54);
	polygon(6,48,52,55,51);    //back center
    polygon(6,49,50,54,53);
	polygon(6,52,53,54,55);
	polygon(6,48,49,53,52);


}


void colorcube8()
{
	polygon(6,56,59,58,57);
	polygon(top[1][0],58,59,63,62);
	polygon(left[0][1],56,60,63,59);    // top left center
    polygon(6,57,58,62,61);
	polygon(6,60,61,62,63);
	polygon(6,56,57,61,60);


}

void colorcube9()
{
	polygon(6,64,67,66,65);
	polygon(top[1][2],66,67,71,70);
	polygon(6,64,68,71,67);    // top right center
    polygon(right[0][1],65,66,70,69);
	polygon(6,68,69,70,71);
	polygon(6,64,65,69,68);


}

void colorcube10()
{
	polygon(6,72,75,74,73);
	polygon(top[2][1],74,75,79,78);
	polygon(6,72,76,79,75);    // top front center
    polygon(6,73,74,78,77);
	polygon(front[0][1],76,77,78,79);
	polygon(6,72,73,77,76);


}

void colorcube11()
{
	polygon(back[0][1],80,83,82,81);
	polygon(top[0][1],82,83,87,86);
	polygon(6,80,84,87,83);    // top back center
    polygon(6,81,82,86,85);
	polygon(6,84,85,86,87);
	polygon(6,80,81,85,84);


}

void colorcube12()
{
	polygon(6,80+8,83+8,82+8,81+8);
	polygon(6,82+8,83+8,87+8,86+8);
	polygon(left[2][1],80+8,84+8,87+8,83+8);    // bottom left center
    polygon(6,81+8,82+8,86+8,85+8);
	polygon(6,84+8,85+8,86+8,87+8);
	polygon(bottom[1][0],80+8,81+8,85+8,84+8);


}

void colorcube13()
{
	polygon(6,80+16,83+16,82+16,81+16);
	polygon(6,82+16,83+16,87+16,86+16);
	polygon(6,80+16,84+16,87+16,83+16);    // bottom right center
    polygon(right[2][1],81+16,82+16,86+16,85+16);
	polygon(6,84+16,85+16,86+16,87+16);
	polygon(bottom[1][2],80+16,81+16,85+16,84+16);


}

void colorcube14()
{
	polygon(6,80+24,83+24,82+24,81+24);
	polygon(6,82+24,83+24,87+24,86+24);
	polygon(6,80+24,84+24,87+24,83+24);    // bottom front center
    polygon(6,81+24,82+24,86+24,85+24);
	polygon(front[2][1],84+24,85+24,86+24,87+24);
	polygon(bottom[0][1],80+24,81+24,85+24,84+24);


}
void colorcube15()
{
	polygon(back[2][1],112,115,114,113);
	polygon(6,114,115,119,118);
	polygon(6,112,116,119,115);    // bottom back center
    polygon(6,113,114,118,117);
	polygon(6,116,117,118,119);
	polygon(bottom[2][1],112,113,117,116);


}

void colorcube16()
{
	polygon(back[0][2],120,123,122,121);
	polygon(top[0][0],122,123,127,126);
	polygon(left[0][0],120,124,127,123);    // top left back
    polygon(6,121,122,126,125);
	polygon(6,124,125,126,127);
	polygon(6,120,121,125,124);


}

void colorcube17()
{
	polygon(6,128,131,130,129);
	polygon(top[2][0],130,131,135,134);
	polygon(left[0][2],128,132,135,131);    // top left front
    polygon(6,129,130,134,133);
	polygon(front[0][0],132,133,134,135);
	polygon(6,128,129,133,132);


}


void colorcube18()
{
	polygon(back[0][0],136,139,138,137);
	polygon(top[0][2],138,139,143,142);
	polygon(6,136,140,143,139);    // top right back
    polygon(right[0][2],137,138,142,141);
	polygon(6,140,141,142,143);
	polygon(6,136,137,141,140);


}


void colorcube19()
{
	polygon(6,144,147,146,145);
	polygon(top[2][2],146,147,151,150);
	polygon(6,144,148,151,147);    // top right front
    polygon(right[0][0],145,146,150,149);
	polygon(front[0][2],148,149,150,151);
	polygon(6,144,145,149,148);


}

void colorcube20()
{
	polygon(back[1][2],152,155,154,153);
	polygon(6,154,155,159,158);
	polygon(left[1][0],152,156,159,155);    //center left back
    polygon(6,153,154,158,157);
	polygon(6,156,157,158,159);
	polygon(6,152,153,157,156);


}

void colorcube21()
{
	polygon(6,160,163,162,161);
	polygon(6,162,163,167,166);
	polygon(left[1][2],160,164,167,163);    // center left front
    polygon(6,161,162,166,165);
	polygon(front[1][0],164,165,166,167);
	polygon(6,160,161,165,164);


}


void colorcube22()
{
	polygon(back[1][0],168,171,170,169);
	polygon(6,170,171,175,174);
	polygon(6,168,172,175,171);    // center right back
    polygon(right[1][2],169,170,174,173);
	polygon(6,172,173,174,175);
	polygon(6,168,169,173,172);


}


void colorcube23()
{
	polygon(6,176,179,178,177);
	polygon(6,178,179,183,182);
	polygon(6,176,180,183,179);    //center right front
    polygon(right[1][0],177,178,182,181);
	polygon(front[1][2],180,181,182,183);
	polygon(6,176,177,181,180);


}

void colorcube24()
{
	polygon(back[2][2],184,187,186,185);
	polygon(6,186,187,191,190);
	polygon(left[2][0],184,188,191,187);    // bottom left back
    polygon(6,185,186,190,189);
	polygon(6,188,189,190,191);
	polygon(bottom[2][0],184,185,189,188);


}
void colorcube25()
{
	polygon(6,192,195,194,193);
	polygon(6,194,195,199,198);
	polygon(left[2][2],192,196,199,195);    // bottom left front
    polygon(6,193,194,198,197);
	polygon(front[2][0],196,197,198,199);
	polygon(bottom[0][0],192,193,197,196);


}

void colorcube26()
{
	polygon(back[2][0],200,203,202,201);
	polygon(6,202,203,207,206);
	polygon(6,200,204,207,203);    // bottom right back
    polygon(right[2][2],201,202,206,205);
	polygon(6,204,205,206,207);
	polygon(bottom[2][2],200,201,205,204);


}

void colorcube27()
{
	polygon(6,208,211,210,209);
	polygon(6,210,211,215,214);
	polygon(6,208,212,215,211);    // bottom right front
    polygon(right[2][0],209,210,214,213);
	polygon(front[2][2],212,213,214,215);
	polygon(bottom[0][2],208,209,213,212);


}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3fv(color[0]);

	glPushMatrix();
    glRotatef(25.0+p,1.0,0.0,0.0);
    glRotatef(-30.0+q,0.0,1.0,0.0);
    glRotatef(0.0+r,0.0,0.0,1.0);

	colorcube1();
	colorcube2();
	colorcube3();
	colorcube4();
	colorcube5();
	colorcube6();
	colorcube7();
	colorcube8();
	colorcube9();
	colorcube10();
	colorcube11();
	colorcube12();
	colorcube13();
	colorcube14();
	colorcube15();
	colorcube16();
	colorcube17();
	colorcube18();
	colorcube19();
	colorcube20();
	colorcube21();
	colorcube22();
	colorcube23();
	colorcube24();
	colorcube25();
	colorcube26();
	colorcube27();

	glPopMatrix();
	glFlush();
  	glutSwapBuffers();
}

void myreshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	glOrtho(-10.0,10.0,-10.0*(GLfloat)h/(GLfloat)w, 10.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else
	glOrtho(-10.0*(GLfloat)w/(GLfloat)h, 10.0*(GLfloat)w/(GLfloat)h,-10.0,10.0,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition(100, 0);
	glutCreateWindow ("RUBIK'S CUBE");
	glutReshapeFunc (myreshape);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}