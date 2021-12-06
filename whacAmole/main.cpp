//#include<windows.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

int molePosX;
int molePosY;

static int score = 0;
static int life = 3;
static int currentHole;

char* gameStatus = "";

void init(){
    glClearColor(0.42, 0.69, 1.00, 1);
}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void holes(double x, double y, double z){
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(x, y, z);
    glutSolidSphere(3.0, 60.0, 10);
    glPopMatrix();
}

void moles(int){
    glPushMatrix();
    glColor3f(1, 0, 0);
    int x = (rand() % 6);
    //currentHole = x;
    switch(x){
        case 1:
            molePosX = -7;
            molePosY = 5;
            break;
        case 2:
            molePosX = -7;
            molePosY = -5;
            break;
        case 3:
            molePosX = 0;
            molePosY = 5;
            break;
        case 4:
            molePosX = 0;
            molePosY = -5;
            break;
        case 5:
            molePosX = 7;
            molePosY = 5;
            break;
        case 6:
            molePosX = 7;
            molePosY = -5;
            break;
    }
    currentHole = x;
    glutTimerFunc(1000, moles, 1);
}

void Text(float x, float y, float z, void *font, char *string){
    char *c;
    glRasterPos3f(x, y, z);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

//Grid
    glPointSize(10.0);
    glTranslatef(3.5, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-14, 0);
    glVertex2f(7, 0);
    glVertex2f(0, 10);
    glVertex2f(0, -10);
    glEnd();

    glTranslatef(-7, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 5);
    glVertex2f(0, -5);
    glVertex2f(0, 10);
    glVertex2f(0, -10);
    glEnd();

//Score Board
    glTranslatef(3.5, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(-3, 1);
    glVertex2f(3, 1);
    glVertex2f(3, -1);
    glVertex2f(-3, -1);
    glEnd();

//Score Board Text
    glColor3f(1, 1, 0);
    glColor3f(0, 1, 0);
    Text(-2.25, -0.25, 0, GLUT_BITMAP_TIMES_ROMAN_24, gameStatus);

//Holes
    holes(-6.8, 5, 0);
    holes(-6.8, -5, 0);
    holes(0, 5, 0);
    holes(0, -5, 0);
    holes(6.8, 5, 0);
    holes(6.8, -5, 0);

//Mole Position///////////////////////////
    glTranslatef(molePosX, molePosY, 0);
    glColor3f(0, 0, 1);
//Head
    glutSolidSphere(1.5, 50.0, 100);
//Left Eye
    glTranslatef(-0.7, 0.5, 0);
    glutSolidSphere(0.1, 50.0, 40);
//Right Eye
    glTranslatef(1.5, 0, 0);
    glutSolidSphere(0.1, 50.0, 40);
//Nose
    glTranslatef(-0.5, -1.2, 0);
    glutSolidSphere(0.2, 50.0, 40);

    glPopMatrix();
    glutPostRedisplay();
    glFlush();
}

void mouse(int button, int state, int x, int y){
    int currentClick;
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            if(x>0 && x<166 && y>0 && y<250){
                currentClick = 1;
            }else if(x>167 && x<333 && y>0 && y<250){
                currentClick = 2;
            }else if(x>334 && x<500 && y>0 && y<250){
                currentClick = 3;
            }else if(x>0 && x<166 && y>251 && y<500){
                currentClick = 4;
            }else if(x>167 && x<333 && y>251 && y<500){
                currentClick = 5;
            }else if(x>334 && x<500 && y>251 && y<500){
                currentClick = 6;
            }

            if(currentClick == currentHole){
                score += 100;
                cout << score << endl;
            }else{
                life--;
                cout << "Missed" << endl;
            }

            if(life<=0){
                cout << "Game Over" << endl;
                gameStatus = "Game Over";
            }
        }
    }
}

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(500, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Whac-A-Mole");
    glutTimerFunc(0, moles, 1);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
}
