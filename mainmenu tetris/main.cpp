#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <conio.h>
#include <bits/stdc++.h>
#include<iostream>
#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include<string>
#include<dos.h>
#include <MMsystem.h>

bool initial = true, firsttime = true, allowkeys = false;
float tx = 600;

using namespace std;

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


void ballanim(){
    float state = tx / 600;
    glClearColor (state, state, state, 0.0);
    drawCircle(5,5,0,tx, 350);
}

long int gethighscore()
{
    long int hs;
      ifstream myfile ("example.txt");
      if (myfile.is_open())
      {
           myfile >> hs;
            myfile.close();
      }
      return hs;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    if(firsttime) {
        Sleep(1000);        firsttime = false;
    }

    if(initial == true){
        if(tx >= 0){
            tx-=10;
            ballanim();
        }else{
            initial = false;
            Sleep(1500);
            ShellExecute(NULL, "open", "Tetris project.exe", NULL, NULL, SW_SHOWNORMAL);
            exit(0);
        }
    }

	glFlush();
}

void init(void)
{
	glClearColor (.1, .1, .1, 0.0);
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
	glutReshapeFunc(my_reshape);
	glutTimerFunc(0, timer,0);
    glutMainLoop();

    return 0;
}
