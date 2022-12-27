#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

int FPS = 50; //Game Speed
int start=0; //Game Track
int gv=0; //Game Over
int level = 0; //Game Level
int score = 0; //Track Score
int roadDivTop = 0; //Track Movement
int roadDivMdl = 0;
int roadDivBtm = 0;
int lrIndex = 0; //Car Left or RIGHT Movement
//Car Coming
int car1 = 0;
int lrIndex1=0;
int car2 = +35;
int lrIndex2=0;
int car3 = +70;
int lrIndex3=0;
//Display TEXT
const int font1=(int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2=(int)GLUT_BITMAP_HELVETICA_18 ;
const int font3=(int)GLUT_BITMAP_8_BY_13;
char s[30];
//Function To Display Text
void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y); //display bitmap write operation
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c); //rendering text
    }
}
//Function To Start Game
void startGame(){
    //Road
    glColor3f(0.412, 0.412, 0.412);
    glRectd(20,0,80,100);
    //Road Left Border
    glColor3f(1.000, 1.000, 1.000);
    glRectd(20,0,23,100);
    //Road Right Border
    glColor3f(1.000, 1.000, 1.000);
    glRectd(77,0,80,100);
    //Top Divider
    glColor3f(1.000, 1.000, 0.000);
    glRectd(48,roadDivTop+80,52,roadDivTop+100);
    roadDivTop--;
    if(roadDivTop<-100){
        roadDivTop =20;
        score++;
    }
    //Middle Divider
    glColor3f(1.000, 1.000, 0.000);
    glRectd(48,roadDivMdl+40,52,roadDivMdl+60);
    roadDivMdl--;
    if(roadDivMdl<-60){
        roadDivMdl =60;
        score++;
    }
    //Bottom Divider
    glColor3f(1.000, 1.000, 0.000);
    glRectd(48,roadDivBtm+0,52,roadDivBtm+20);
    roadDivBtm--;
    if(roadDivBtm<-20){
        roadDivBtm=100;
        score++;
    }
    //Score Board
    glColor3f(0.000, 0.000, 0.000);
    glRectd(80,97,100,98-8);
    //Score Print
    char buffer [50];
    sprintf (buffer, "SCORE: %d", score);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5,95,(void *)font3,buffer);
    //Speed Print
    char buffer1 [50];
    sprintf (buffer1, "SPEED:%dKm/h", FPS);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5,95-2,(void *)font3,buffer1);
    //Level Print
    if(score % 50 == 0){
        int last = score /50;
        if(last!=level){
            level = score /50;
            FPS=FPS+2;
        }
    }
    char level_buffer [50];
    sprintf (level_buffer, "LEVEL: %d", level);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5,95-4,(void *)font3,level_buffer);
    //Main Car Body
    //Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glRectd(lrIndex+26-2,5,lrIndex+30+2,7);
    //Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glRectd(lrIndex+26-2,1,lrIndex+30+2,3);
    //Car Body
    glColor3f(0.678, 1.000, 0.184);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex+26,1);
    glVertex2f(lrIndex+26,8);
    glColor3f(0.000, 0.545, 0.545);
    glVertex2f(lrIndex+28,10);
    glVertex2f(lrIndex+30,8);
    glVertex2f(lrIndex+30,1);
    glEnd();
    //Opposite car 1
    //Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glRectd(lrIndex1+26-2,car1+100-4,lrIndex1+30+2,car1+100-6);
    //Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glRectd(lrIndex1+26-2,car1+100,lrIndex1+30+2,car1+100-2);
    //Car Body
    glColor3f(1.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1+26,car1+100);
    glVertex2f(lrIndex1+26,car1+100-7);
    glVertex2f(lrIndex1+28,car1+100-9);
    glVertex2f(lrIndex1+30,car1+100-7);
    glVertex2f(lrIndex1+30,car1+100);
    glEnd();
    car1--;
    if(car1<-100){
        car1=0;
        lrIndex1=lrIndex;
    }
    //KIll check car 1
    if((abs(lrIndex-lrIndex1)<8) && (car1+100<10)){
            start = 0;
            gv=1;
    }
    //Opposite car 2
    //Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glRectd(lrIndex2+26-2,car2+100-4,lrIndex2+30+2,car2+100-6);
    //Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glRectd(lrIndex2+26-2,car2+100,lrIndex2+30+2,car2+100-2);
    //Car Body
    glColor3f(0.294, 0.000, 0.510);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2+26,car2+100);
    glVertex2f(lrIndex2+26,car2+100-7);
    glVertex2f(lrIndex2+28,car2+100-9);
    glVertex2f(lrIndex2+30,car2+100-7);
    glVertex2f(lrIndex2+30,car2+100);
    glEnd();
    car2--;
    if(car2<-100){
        car2=0;
        lrIndex2=lrIndex;
    }
    //KIll check car2
    if((abs(lrIndex-lrIndex2)<8) && (car2+100<10)){
            start = 0;
            gv=1;
    }
    //Opposite car 3
    //Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glRectd(lrIndex3+26-2,car3+100-4,lrIndex3+30+2,car3+100-6);
    //Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glRectd(lrIndex3+26-2,car3+100,lrIndex3+30+2,car3+100-2);
    //Car Body
    glColor3f(1.000, 0.271, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3+26,car3+100);
    glVertex2f(lrIndex3+26,car3+100-7);
    glVertex2f(lrIndex3+28,car3+100-9);
    glVertex2f(lrIndex3+30,car3+100-7);
    glVertex2f(lrIndex3+30,car3+100);
    glEnd();
    car3--;
    if(car3<-100){
        car3=0;
        lrIndex3=lrIndex;
    }
    //KIll check car3
    if((abs(lrIndex-lrIndex3)<8) && (car3+100<10)){
            start = 0;
            gv=1;
    }
}
//Front Page Design
void fristDesign(){
    //Road Background
    glColor3f(0.000, 0.392, 0.000);
    glRectd(0,55,100,50-50);
    //Road Design In Front Page
    glColor3f(00, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(32-2+21,55);
    glVertex2f(32+58,50-50);
    glVertex2f(32-22,50-50);
    glEnd();
    //Road Divider
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    glVertex2f(32-2+21,55);
    glVertex2f(50+2,50-50);
    glVertex2f(50-2,50-50);
    glEnd();
     //Road Sky
    glColor3f(0.000, 0.749, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(100,100);
    glVertex2f(0,100);
    glColor3f(0.686, 0.933, 0.933);
    glVertex2f(0,55);
    glVertex2f(100,55);
    glEnd();
    //Menu Place Holder
    glColor3f(0.098, 0.098, 0.439);
    glRectd(32-4,50+5+10,32+46,50-15+10);
    //Text Information in First Page
    if(gv==1)
    {
        glColor3f(1.000, 0.000, 0.000);
        renderBitmapString(35,60+10,(void *)font1,"GAME OVER");
        glColor3f(1.000, 0.000, 0.000);
        char buffer2 [50];
        sprintf (buffer2, "Your Score is : %d", score);
        renderBitmapString(33,60-4+10,(void *)font1,buffer2);
    }
    glColor3f(1.000, 1.000, 0.000);
    renderBitmapString(35,80,(void *)font1,"Car Racing Game");
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(30,50+10,(void *)font2,"Press SPACE to START");
    renderBitmapString(30,50-3+10,(void *)font2,"Press ESC to Exit");
    glColor3f(1.000, 1.000, 1.000);
    renderBitmapString(30,50-6+10,(void *)font3,"Press UP to increase Speed");
    renderBitmapString(30,50-8+10,(void *)font3,"Press DWON to decrease Speed");
    renderBitmapString(30,50-10+10,(void *)font3,"Press RIGHT to turn Right");
    renderBitmapString(30,50-12+10,(void *)font3,"Press LEFT to turn Left");
    glColor3f(0.000, 1.000, 1.000);
    renderBitmapString(30-5,50-48,(void *)font3,"Project By:        Kazi Samsul Arefin");
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(start==1){
        glClearColor(0.000, 0.392, 0.000,1);
        startGame();
    }
    else{
        fristDesign();
    }
    glFlush(); //forces execution
    glutSwapBuffers(); //forces execution for animation
}
void spe_key(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_DOWN:
            if(FPS>(50+(level*2)))
            FPS=FPS-2;
            break;
        case GLUT_KEY_UP:
            FPS=FPS+2;
            break;
        case GLUT_KEY_LEFT:
            if(lrIndex>=0)
            {
                lrIndex = lrIndex - (FPS/10);
                if(lrIndex<0)
                {
                    lrIndex=-1;
                }
            }
            break;
        case GLUT_KEY_RIGHT:
            if(lrIndex<=44)
            {
                lrIndex = lrIndex + (FPS/10);
                if(lrIndex>44)
                {
                    lrIndex = 45;
                }
            }
            break;
        default:
            break;
    }
}
void processKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':
        if(start==0)
        {
            start = 1;
            gv = 0;
            FPS = 50;
            roadDivTop = 0;
            roadDivMdl = 0;
            roadDivBtm = 0;
            lrIndex = 0 ;
            car1 = 0;
            lrIndex1=0;
            car2 = +35;
            lrIndex2=0;
            car3 = +70;
            lrIndex3=0;
            score=0;
            level=0;
        }
        break;
        case 27:
            exit(0);
        break;
        default:
        break;
    }
}
void timer(int)
{
    glutPostRedisplay(); //current window redisplaying
    glutTimerFunc(1000/FPS,timer,0); //calls certain function after specified time
}
int main(int argc, char *argv[]) //arguments to initialize glut library
{
    glutInit(&argc, argv); //initializing glut library
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //initializing display mood
    glutInitWindowSize(500,650);
    glutInitWindowPosition(200,20);
    glutCreateWindow("Car Game");
    glutDisplayFunc(display); //to display window
    glutSpecialFunc(spe_key); //navigation key
    glutKeyboardFunc(processKeys ); //start-end key
    glOrtho(0,100,0,100,-1,1); //transformation to produce parallel projection
    glClearColor(0.184, 0.310, 0.310,1); //setting background color
    glutTimerFunc(1000,timer,0); //calls certain function after specified time
    glutMainLoop();
    return 0;
}
