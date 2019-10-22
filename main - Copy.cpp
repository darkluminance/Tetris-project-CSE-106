#include<iostream>
#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include<fstream>
#include<string>
#include<bits/stdc++.h>
#include<dos.h>
#include <mmsystem.h>

using namespace std;

static GLfloat spin = 0.0;
static float	tx	=  0.0;
static float	ty	=  0.0, angle = 0.0;
int counter = 0;
long long score = 0;
bool rot = false;
bool gameover = false;
int blox[4][8] ={  {114, 148, 182, 216, 12, 12, 12, 12},
                            {114, 148, 182, 182, 12, 12, 12, 46},
                            {114, 114, 114, 114, 12, 46, 80, 114},
                            {114, 114, 148, 182, 12, 46, 12, 12},
                        };
float maxdistX[4][2] = {{-98, 98},{ -98, 132}, {-98, 200}, {-98,132} };
float maxdistY[4] = {645, 611, 543, 611};

int blockNo = rand() % 4;
int cA[100] = {0};
float cB[100] = {0};
int cBlock[100] = {0};

void renderbitmap(float x, float y, void *font, char *Xtring){
    char *c;
    glRasterPos2f(x,y);
    for(c=Xtring; *c!='\0'; c++)    glutBitmapCharacter(font,*c);
}

void writeText(char *a, float x, float y, void *font){
    glColor3f(0,0,0);
    char buf[100] = {0};
    sprintf(buf,a);
    renderbitmap(x,y,font,buf);
}

void writeIntText(int a, float x, float y, void *font){
    glColor3f(0,0,0);
    char buf[100] = {0};
    sprintf(buf, "%d" ,a);
    renderbitmap(x,y,font,buf);
}


void drawCircle(float rx, float ry, int half, int xp, int yp){
    glPushMatrix();
    glPointSize(3);
    glBegin(GL_POLYGON);
    int i;
    int len = 360;
    if(half == 1)   len = 180;
    for(i=0; i<len; i++){
        float theta = (i*3.1416)/180.0;
        glVertex2f(rx*cos(theta)  + xp, ry*sin(theta) + yp);
    }
    glEnd();
    glPopMatrix();
}

void DrawBox(int x1, int x2, int y1, int y2){
    glPushMatrix();
    glBegin(GL_POLYGON);

    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);

    glEnd();
    glPopMatrix();
}

void DrawTetramino(int bl)
{
    glPushMatrix();

        glTranslatef(tx,ty,0);

        glColor3f(.75,.25,.25);
        DrawBox(blox[bl][0], blox[bl][0]+30, blox[bl][4], blox[bl][4]+30);
        glColor3f(.15,.5,.85);
        DrawBox(blox[bl][1], blox[bl][1]+30, blox[bl][5], blox[bl][5]+30);
        glColor3f(.75,.25,.25);
        DrawBox(blox[bl][2], blox[bl][2]+30, blox[bl][6], blox[bl][6]+30);
        glColor3f(.15,.5,.85);
        DrawBox(blox[bl][3], blox[bl][3]+30, blox[bl][7], blox[bl][7]+30);


    glPopMatrix();
}


void DrawFinishedTetramino0(float x, float y)
{
    //printf("Teta 1 e\n");
    glPushMatrix();
     x+=114;    y+= 12;
        glColor3f(.75,.25,.25);
        DrawBox(x, x+30, y, y+30);
        glColor3f(.15,.5,.85);
        x+=34;
        DrawBox(x, x+30, y, y+30);
        glColor3f(.75,.25,.25);
        x+=34;
        DrawBox(x, x+30, y, y+30);
        glColor3f(.15,.5,.85);
        x+=34;
        DrawBox(x, x+30, y, y+30);
    glPopMatrix();
}



void DrawFinishedTetramino1(float x, float y)
{
   // printf("Teta 2 e\n");
    glPushMatrix();
     x+=114;    y+= 12;
        glColor3f(.75,.25,.25);
        DrawBox(x, x+30, y, y+30);
        glColor3f(.15,.5,.85);
        x+=34;
        DrawBox(x, x+30, y, y+30);
        glColor3f(.75,.25,.25);
        x+=34;
        DrawBox(x, x+30, y, y+30);
        glColor3f(.15,.5,.85);
        y+=34;
        DrawBox(x, x+30, y, y+30);
    glPopMatrix();
}



void DrawFinishedTetramino3(float x, float y)
{
  //  printf("Teta 4 e\n");
    glPushMatrix();
     x+=114;    y+= 12;
        glColor3f(.75,.25,.25);
        DrawBox(x, x+30, y, y+30);
        glColor3f(.15,.5,.85);
        y+=34;
        DrawBox(x, x+30, y, y+30);
        glColor3f(.75,.25,.25);
        x+=34; y-=34;
        DrawBox(x, x+30, y, y+30);
        glColor3f(.15,.5,.85);
        x+=34;
        DrawBox(x, x+30, y, y+30);
    glPopMatrix();
}



void DrawFinishedTetramino2(float x, float y)
{
   // printf("Teta 3 e\n");
    glPushMatrix();
     x+=114;    y+= 12;
        glColor3f(.75,.25,.25);
        DrawBox(x, x+30, y, y+30);
        glColor3f(.15,.5,.85);
        y+=34;
        DrawBox(x, x+30, y, y+30);
        glColor3f(.75,.25,.25);
        y+=34;
        DrawBox(x, x+30, y, y+30);
        glColor3f(.15,.5,.85);
        y+=34;
        DrawBox(x, x+30, y, y+30);
    glPopMatrix();
}
void DrawLinesX(float x)
{
    glBegin(GL_LINE_LOOP);

    glColor3f(.25,.25,.25);
    glVertex2f(x, 10);
    glVertex2f(x, 690);

    glEnd();
}


void DrawLinesY(float y)
{
    glBegin(GL_LINE_LOOP);

    glColor3f(.25,.25,.25);
    glVertex2f(10, y);
    glVertex2f(350, y);

    glEnd();
}

void DrawGameArea(){
    glColor3f(.1,.1,.1);
    DrawBox(10, 350, 10, 690);
    int s = 44;
    for(int i = 1; i<=10; i++, s+= 34){
        DrawLinesX(s);
    }

    s = 44;

    for(int i = 1; i<=20; i++, s+= 34){
        DrawLinesY(s);
    }
}


void display(void)
{


    if(gameover) exit(0);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


    DrawGameArea();
    DrawTetramino(blockNo);

    if(ty<=645) ty += 3.4;

    for(int i = 0; i<counter; i++){
        if(cBlock[i] == 0)
            {DrawFinishedTetramino0(cA[i], cB[i]);}
        else if(cBlock[i] == 1)
            {DrawFinishedTetramino1(cA[i], cB[i]);}
        else if(cBlock[i] == 2)
            {DrawFinishedTetramino2(cA[i], cB[i]);}
        else if(cBlock[i] == 3)
            {DrawFinishedTetramino3(cA[i], cB[i]);}
    }


    writeText("TETRIS", 435, 50, GLUT_BITMAP_TIMES_ROMAN_24);
    writeText("Score: ", 360, 250, GLUT_BITMAP_HELVETICA_18);
    writeIntText(score, 420, 250, GLUT_BITMAP_HELVETICA_18);
    writeText("High Score: ", 360, 300, GLUT_BITMAP_HELVETICA_18);



    if(ty >= maxdistY[blockNo]){
        cA[counter] = tx; cB[counter] =ty;
        cBlock[counter] = blockNo;
        counter++;
        score += 100;
        ty = 0;
        blockNo = rand() % 4;
    }else
    {
        for(int i = 0; i<counter; i++){
            if(cB[i] - ty <= 34.015  &&  abs(cA[i] - tx) <= 108) {
                cA[counter] = tx; cB[counter] = ty;
                cBlock[counter] = blockNo;
                if(cB[counter] <= 3.41){
                    cout << "Game Over";
                    gameover = true;
                }
                counter++;
                score += 100;
                ty = 0;
                blockNo = rand() % 4;
                break;
            }
        }
    }



	glFlush();
}


void init(void)
{
	glClearColor (.898, .8941, .8863, 0.0);
    //PlaySound(TEXT("starwars.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
}


void my_keyboard(unsigned char key, int x, int y)
{

	switch (key) {

		case '4':
		    if(tx >= maxdistX[blockNo][0] && ty<=maxdistY[blockNo])
                tx -= 34;
			break;

		case '6':
		    if(tx <= maxdistX[blockNo][1] && ty<=maxdistY[blockNo])
                tx += 34;
			break;

		case '5':
			 ty = 646;
			 break;
        case '8':
            rot = true;
            break;

	  default:
			break;
	}
}

void my_reshape(int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,600,700,0);
    glMatrixMode(GL_MODELVIEW);

}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
}

int main()
{
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (600, 700);
	glutCreateWindow ("Just a game of T E T R I S");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(my_keyboard);
	glutReshapeFunc(my_reshape);
	glutTimerFunc(0, timer,0);
	glutMainLoop();
	return 0;
}
