//181-15-11009
//Mehedi_Hasan
//Solar System

#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include<iostream>
#include<utility>
#include<vector>
#include<stack>
using namespace std;

struct RGB{//structure for color
    float r;
    float g;
    float b;
};

stack<pair<double, double>>  circle(double x, double y, double r, struct RGB rgb,
                                    pair<double, double>eq, bool B_ellipse, double planetDeg);//function for orbit draw and planet path
void planet(double x, double y, double r, struct RGB rgb);//function for drawing planet,NB>: plant can be different in size
void wait(int timer);//wait function for delay, basically speed

void wait(int timer){
    for(int i=0;i<timer;i++){}
}

void planet(double x, double y, double r, struct RGB rgb){
    double RadTheta=0.0;
    double PI=3.14159265;
    double xr, yr;
    //x & y is the planet moving path
    glColor3ub(rgb.r, rgb.g, rgb.b);
    glBegin(GL_POLYGON);
    for(double deg=0.0;deg<=360.0;deg+=0.51){
            RadTheta=deg*(PI/180);
            xr=x+(r*cos(RadTheta));
            yr=y+(r*sin(RadTheta));
            glVertex2d(xr, yr);
    }
    glEnd();
}
stack<pair<double, double>>  circle(double x, double y, double r, struct RGB rgb,
                                    pair<double, double>eq, bool B_ellipse, double planetDeg){
    double RadTheta=0.0;
    double PI=3.14159265;
    double xr, yr;

    if(!B_ellipse){//if the B_eclips is false it will circle otherwise ellipse
        eq.first=1.0;
        eq.second=1.0;
    }
    glBegin(GL_LINES);
    glColor3ub(rgb.r, rgb.g, rgb.b);

    stack<pair<double, double>> orbitPath;
    //added planetDeg cause all planets stating degree won't be same
    for(double deg=0.0+planetDeg;deg<=360.0+planetDeg;deg+=0.6){
            RadTheta=deg*(PI/180);
            xr=x+(r*cos(RadTheta)*eq.first);
            yr=y+(r*sin(RadTheta)*eq.second);
            glVertex2d(xr, yr);//draw orbit
            orbitPath.push(make_pair(xr, yr));//store orbit path in stack
    }
    glEnd();
        return orbitPath;
}
//for create orbit path and planet
vector<stack<pair<double, double>>> AllPlanet_tempCircle(8), AllPlanet_circlePath(8);
void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(255,255,0);
    RGB orbitColor;
    orbitColor.r=255.0;
    orbitColor.g=255.0;
    orbitColor.b=255.0;

    //planet starting degree
    double planetDeg[8]={0.0, 30.0, 60.0, 90.0, 150.0, 220.0, 270.0, 330.0};
    double planetRadius[8]={30.0, 32.0, 35.0, 33.0, 40.0, 38.0, 33.0, 32.0};

    vector<struct RGB>planetColor{
        {99.0, 99.0, 99.0},    //mercury
        {255.0, 202.0, 146.0}, //venus
        {68.0, 116.0, 162.0},  //earth
        {210.0, 157.0, 91.0},  //mars
        {204.0, 201.0, 168.0}, //jupiter
        {190.0, 163.0, 108.0}, //saturn
        {176.0, 209.0, 216.0}, //uranus
        {148.0, 125.0, 255.0}  //neptune
        };
    //initial point x, y
    double x = 0.0, y=30.0;
    //ellipse ratio x_, y_;
    double _x=2.0, _y=1.0;
    //sun
    RGB sunColor;
    sunColor.r=211.0;
    sunColor.g=30.0;
    sunColor.b=10.0;
    planet(x, y, 70, sunColor);//sun
    for(int i=100, j=0;i<=450;i+=50, j++)
        {
            wait(700000);
            //for ellipse boolean will true otherwise false
            AllPlanet_tempCircle[j]=circle(x, y, i, orbitColor, make_pair(_x, _y), true, planetDeg[j]);
            //orbit drawn and path store in allplanet_tempcircle

            if(AllPlanet_circlePath[j].empty())//if the stack is empty store path on new stack orbit wise
            {
                AllPlanet_circlePath[j]=AllPlanet_tempCircle[j];
            }else{//next time planet will drawn
                planet(AllPlanet_circlePath[j].top().first, AllPlanet_circlePath[j].top().second, planetRadius[j], planetColor[j]);

                for(int k=0;k<=abs(8-j);k++)//popped more for lower orbital for fast rotate
                if(!AllPlanet_circlePath[j].empty())
                AllPlanet_circlePath[j].pop();
            }
        }
         glutPostRedisplay();

    glFlush();
}

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-960, 960, -540, 540);
}

int main(int argc, char** argv)
{
    cout<<"MEHEDI HASAN"<<endl<<"ID:181-15-11009"<<endl<<"Solar System, computer graphics lab project"<<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (1920, 1080);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("181-15-11009_Mehedi_Hasan");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
return 0;
}
