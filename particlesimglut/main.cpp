#include<stdio.h>
#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include<time.h>
#define pi 3.142857

const int height = 700;
const int width= 700;
const int frameratecap = 60;
const int sizeofpointer = 10;

const int nparticles = 10000;
const int gravityconst = 10;
const int massofpointer = 50;

int mousex;
int mousey;

float randomint(float a, float b)
{
    if(b==a){return 0;}
    float x = rand()%(int)abs(b-a);
    return x+ std::min(a,b);

}

void OnMouseClick(int x, int y)
{
    mousex = x-(width/2);
    mousey = -1*(y-(height/2));
}


class particle
{
public:
    float posx = randomint(-width/2,width/2);
    float posy = randomint(-height/2,height/2);
    float velx = 0;
    float vely = 0;
    float vel = 0;
    float accx = 0;
    float accy = 0;
    float acc = 0;
    int mass = 1;
    int life = 300 + (rand()%500);
    float dist = sqrtf((posx-mousex)*(posx-mousex) + (posy-mousey)*(posy-mousey));

    void reset()
    {
        posx = randomint(-width/2,width/2);
        posy = randomint(-height/2,height/2);
        velx = 0;
        vely = 0;
        accx = 0;
        accy = 0;
        mass = 1;
        life = 300 + (rand()%500);
        dist = sqrtf((posx-mousex)*(posx-mousex) + (posy-mousey)*(posy-mousey));
    }

    void update()
    {
        if(life==0)
        {
            reset();
        }
        else{life--;}
        //std::cout<<dist<<std::endl;
        acc = gravityconst*mass*massofpointer/(dist*dist);
        accx = acc * (mousex-posx) / dist;
        accy = acc * (mousey-posy) / dist;

        velx+=accx;
        vely+=accy;
        posx+=velx;
        posy+=vely;
        if(posx>width/2||posx<=-1*width/2){life=0;}
        if(posy>height/2||posy<=-1*height/2){life=0;}


        dist = sqrtf(((posx-mousex)*(posx-mousex)) + ((posy-mousey)*(posy-mousey)));
        vel = sqrt((velx*velx)+(vely*vely));
        if(dist<sizeofpointer){dist=sizeofpointer;}

        //if(vel>=2)
            show();
    }

    void show()
    {
        glVertex2f(posx,posy);
    }


};

particle particles[nparticles];

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/frameratecap,timer,0);
    //update here!!!!!!

}

void myInit (void)
{
    // making background color black as first
    // 3 arguments all are 0.0
    glClearColor(0,0,0, 1.0);

    // making picture color green (in RGB mode), as middle argument is 1.0
    glColor3f(1,1,1);

    // breadth of picture boundary is 1 pixel
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // setting window dimension in X- and Y- direction
    gluOrtho2D(-1*width/2, width/2, -1*height/2, height/2);
}

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    for(int i=0; i<nparticles;i++)
    {
        particles[i].update();

    }

    glEnd();
    glutSwapBuffers();
}

int main (int argc, char** argv)
{

    srand((unsigned) time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // giving window size in X- and Y- direction
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 0);

    // Giving name to window
    glutCreateWindow("Circle Drawing");
    myInit();

    glutDisplayFunc(display);
    glutTimerFunc(0,timer,0);
    glutPassiveMotionFunc(OnMouseClick);
    glutMainLoop();
}
