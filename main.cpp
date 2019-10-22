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

std::vector<std::vector<int>> stage(22, std::vector<int>(13, 0));
std::vector<std::vector<int>> block =
{
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
};

std::vector<std::vector<int>> field(22, std::vector<int>(13, 0));
// coordinate
int y = 0;
int x = 4;
bool gameover = false;
int GAMESPEED = 25;

std::vector<std::vector<std::vector<int>>> block_list =
{
    {
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 }
    },
    {
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 }
    },
    {
        { 0, 0, 1, 0 },
        { 0, 1, 1, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 1, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 1, 0 }
    }
};

int Main_Menu();
int gameOver();
void title();
void gameLoop();
void display();
bool makeBlocks();
void initializeGame();
void moveBlock(int, int);
void collidable();
bool isCollide(int, int);
void userInput();
bool rotateBolck();
void spwanBlock();
int checkequality();
 int score=0;
int timeG = 0;
int gc = 0;

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
    glVertex2f(44, y);
    glVertex2f(350 + 34, y);

    glEnd();
}

void DrawGameArea(){
    if(gameover)
        glColor3f(.5,.5,.75);
    else
        glColor3f(.1,.1,.1);
    DrawBox(44, 350 + 34, 10, 690);
    int s = 44+34;
    for(int i = 1; i<11; i++, s+= 34){
        DrawLinesX(s);
    }

    s = 44;

    for(int i = 1; i<20; i++, s+= 34){
        DrawLinesY(s);
    }
}

void DrawBlocks()
{
    float colorcodes[2][2][3] = {   {   {.75,.25,.25}, {.25,.25,.75}   },
                                                    {   {.25,.75,.25}, {.25,.75,.75}   }
                                                };
    int p = 0;
    int q = rand() % 2;
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (field[i][j] == 1)
            {
                q = !q;
               glColor3f(colorcodes[p][q][0] ,colorcodes[p][q][1],colorcodes[p][q][2]);
               DrawBox(12+34*j, 42+34*j, 12+34*i, 42+34*i);
               //break;
                //writeText("TETRIS", 435, 100, GLUT_BITMAP_TIMES_ROMAN_24);

            }
        }
    }
}

void display(void)
{
    long int highscore;
      ifstream myfile ("example.txt");
      if (myfile.is_open())
      {
           myfile >> highscore;
            myfile.close();
      }

    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    DrawGameArea();
    if(gameover){
            if(gc == 0){
                PlaySound(TEXT("D:\\Programming\\Tetris project\\explosion.wav"), NULL,SND_FILENAME);
                gc++;
            }
            gameOver();
    }
    else
    {
        DrawBlocks();
       if (_kbhit())//for keys input by user
        {
            userInput();//reference to the game commands key
        }

        if (timeG < GAMESPEED)//increase with the time;
        {
            timeG++;
        }
        else
        {

         int M = 20,  N = 12;
            ///////check lines//////////
            int k=M-1;
            for (int i=M-1;i>0;i--)
            {
                int counter=0;
                for (int j=1;j<11;j++)
                {
                    if (field[i][j] == 1){
                            counter++;
                    }
                    field[k][j]=field[i][j];
                }
                if (counter<10) {k--;}
                if(counter == 10){
                        Beep(783.9909,500);
                         score += 120;
                }
            }

            spwanBlock();
            timeG = 0;

            if(score>=highscore){

            ofstream myfile2 ("example.txt");
                if (myfile2.is_open())
                {
                    myfile2 << score;
                    myfile2.close();
                }
            }

    }

        }

    writeText("TETRIS", 435+14, 50, GLUT_BITMAP_TIMES_ROMAN_24);
    writeText("Score: ", 360+34, 225, GLUT_BITMAP_HELVETICA_18);
    writeIntText(score, 420+34, 225, GLUT_BITMAP_HELVETICA_18);
    writeText("High Score: ", 360+34, 275, GLUT_BITMAP_HELVETICA_18);
    writeText("Controls", 435, 350, GLUT_BITMAP_HELVETICA_18);
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    glVertex2f(430, 355);
    glVertex2f(510, 355);
    glEnd();
    writeText("Left arrow : Left", 394, 400, GLUT_BITMAP_HELVETICA_18);
    writeText("Right arrow : Right", 394, 425, GLUT_BITMAP_HELVETICA_18);
    writeText("Down arrow : Down", 394, 450, GLUT_BITMAP_HELVETICA_18);
    writeText("Up arrow : Rotate", 394, 475, GLUT_BITMAP_HELVETICA_18);
    writeIntText(highscore, 500, 275, GLUT_BITMAP_HELVETICA_18);


	glFlush();
}

void my_keyboard(unsigned char key, int x, int y)
{

	 switch (key)
    {
        case 'd':
        if (!isCollide(x + 1, y))//check collision and move
        {
            moveBlock(x + 1, y);//check collision and move
        }
        break;
    case 'a':
        if (!isCollide(x - 1, y))//check collision and move
        {
            moveBlock(x - 1, y);//check collision and move
        }
        break;
    case 's':
        if (!isCollide(x, y + 1))//check collision and move
        {
            moveBlock(x, y + 1);//check collision and move
        }
        break;
        case ' ':
            rotateBolck();//Rotation through 90 degree for every in spacekey
    }
}
void special_keyboard(int key, int x, int y)
{

	 switch (key)
    {
        case GLUT_KEY_RIGHT:
        if (!isCollide(x + 1, y))//check collision and move
        {
            moveBlock(x + 1, y);//check collision and move
        }
        break;
    case GLUT_KEY_LEFT:
        if (!isCollide(x - 1, y))//check collision and move
        {
            moveBlock(x - 1, y);//check collision and move
        }
        break;
    case GLUT_KEY_DOWN:
        if (!isCollide(x, y + 1))//check collision and move
        {
            moveBlock(x, y + 1);//check collision and move
        }
        break;
        case ' ':
            rotateBolck();//Rotation through 90 degree for every in spacekey
    }
}

void init(void)
{
	glClearColor (.898, .8941, .8863, 0.0);
}


void my_reshape(int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,600,700,0);
    glMatrixMode(GL_MODELVIEW);
	 initializeGame();

}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
}

int checkequality(){
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            cout << block[i][j] << " ";
        }
        cout << endl;
    }
}


int main()
{
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (600, 700);
	glutCreateWindow ("Just a game of T E T R I S");
	init();
	glutDisplayFunc(display);
    //glutKeyboardFunc(my_keyboard);
    //glutSpecialFunc(special_keyboard);
	glutReshapeFunc(my_reshape);
	glutTimerFunc(0, timer,0);
    switch (Main_Menu())
    {
    case 1://Goto Game Loop for input 1
        PlaySound(TEXT("D:\\Programming\\Tetris project\\spacejam.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
        //PlaySound("./spacejam.wav", NULL, SND_FILENAME | SND_ASYNC);
        gameLoop();
        glutMainLoop();
        break;
    case 2://Program will End
        return 0;
    }
    return 0;
}



int gameOver()//when user fail in Game
{
	glClearColor (.1898, .18941, .18863, 0.0);
    writeText("G  A   M  E", 155, 310, GLUT_BITMAP_TIMES_ROMAN_24);
    writeText("O  V   E   R", 155, 342, GLUT_BITMAP_TIMES_ROMAN_24);
    writeText("Press R to Restart, C to Exit", 75, 342+34+34, GLUT_BITMAP_TIMES_ROMAN_24);

    if (_kbhit())//for keys input by user
        {
            userInput();//reference to the game commands key
        }
}

void gameLoop()
{
    initializeGame();
}

int Main_Menu()
{
    title();//value to choose during title()

    int select_num = 0;
    cout << "Press enter to continue: ";
    char ch = getchar();
    //std::cin >> select_num;

    switch (select_num)
    {
    case 1:
    case 2:
    case 3:
        break;
    default:
        select_num = 0;
        break;
    }

    return 1;
}

void title()
{
    using namespace std;

    system("cls");//Clear screen

    cout << "\n\n\n\t####### ####### ####### ######    ###    #####\n";
    cout << "\t   #    #          #    #     #    #    #     #\n";
    cout << "\t   #    #          #    #     #    #    #\n";
    cout << "\t   #    #####      #    ######     #     #####\n";
    cout << "\t   #    #          #    #   #      #          #\n";
    cout << "\t   #    #          #    #    #     #    #     #\n";
    cout << "\t   #    #######    #    #     #   ###    #####\t\t";
    cout << "\n";
   cout << "\n\n\n\n";
    //cout << "\n\n\n";

    //cout << "\t\t<Main_Menu>\n";
    //cout << "\t\t1: Start Game\n\t\t2: Quit\n\n";
    //cout << "\t\tChoose >> ";
}

void initializeGame()
{
    for (int i = 0; i <= 20; i++)
    {
        for (int j = 0; j <= 11; j++)
        {
            if ((j == 0) || (j == 11) || (i == 20))
            {
                field[i][j] = stage[i][j] = 9;
            }
            else
            {
                field[i][j] = stage[i][j] = 0;
            }
        }
    }

    makeBlocks();
}

bool makeBlocks()//makes block from four elements
{
    srand(time(NULL));
    x = 4;
    y = 0;

    int blockType = rand() % 7;//Get random blocks from black types

    for (int i = 0; i < 4; i++)
    {

        for (int j = 0; j < 4; j++)
        {
            block[i][j] = 0;
            block[i][j] = block_list[blockType][i][j];
        }
         score++;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            field[i][j + 4] = stage[i][j + 4] + block[i][j];//for block check

            if (field[i][j + 4] > 1)//when reached to top
            {
                gameover = true;
                return true;
            }
        }
    }
    return false;
}

void moveBlock(int x2, int y2)
{

    //Remove block
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            field[y + i][x + j] -= block[i][j];
        }
    }
    //Update coordinates
    x = x2;
    y = y2;

    // assign a block with the updated value
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            field[y + i][x + j] += block[i][j];
        }
    }
}

void collidable()
{
    for (int i = 0; i<21; i++)
    {
        for (int j = 0; j<12; j++)
        {
            stage[i][j] = field[i][j];
        }
    }
}

bool isCollide(int x2, int y2)//check for collision after every update
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[i][j] && stage[y2 + i][x2 + j] != 0)//when there is no 1 but zero
            {
                return true;
            }
        }
    }
    return false;
}

void userInput()
{
    char key;

    key = _getch();

    switch (key)
    {
        if(!gameover){
            case 77:
                if (!isCollide(x + 1, y))//check collision and move
                {
                    moveBlock(x + 1, y);//check collision and move
                }
                break;
            case 75:
                if (!isCollide(x - 1, y))//check collision and move
                {
                    moveBlock(x - 1, y);//check collision and move
                }
                break;
            case 80:
                if (!isCollide(x, y + 1))//check collision and move
                {
                    moveBlock(x, y + 1);//check collision and move
                }
                break;
            case ' ':
                rotateBolck();//Rotation through 90 degree for every in spacekey
                break;
            case 72:
                rotateBolck();//Rotation through 90 degree for every in spacekey
                break;
        }else if(gameover)
        {
            case 'r':
                ShellExecute(NULL, "open", "Tetris project.exe", NULL, NULL, SW_SHOWNORMAL);
                exit(0);
                break;
            case 'R':
                ShellExecute(NULL, "open", "Tetris project.exe", NULL, NULL, SW_SHOWNORMAL);
                exit(0);
                break;
            case 'c':
                exit(0);
                break;
            case 'C':
                exit(0);
                break;

        }

    }
}

bool rotateBolck()
{
    std::vector<std::vector<int>> tmp(4, std::vector<int>(4, 0));

    for (int i = 0; i < 4; i++)
    { //Save temporarily block
        for (int j = 0; j < 4; j++)
        {
            tmp[i][j] = block[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    { //Rotate
        for (int j = 0; j < 4; j++)
        {
            block[i][j] = tmp[3 - j][i];
        }
    }

    if (isCollide(x, y))
    { // And stop if it overlaps not be rotated
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                block[i][j] = tmp[i][j];
            }
        }
        return true;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            field[y + i][x + j] -= tmp[i][j];
            field[y + i][x + j] += block[i][j];
        }
    }

    //display();

    return false;
}

void spwanBlock()//block to move down with speed
{
    if (!isCollide(x, y + 1))//no collision
    {
        moveBlock(x, y + 1);
    }
    else
    {
        collidable();//when collision occur

        makeBlocks();//another block started
        //display();
    }
}
