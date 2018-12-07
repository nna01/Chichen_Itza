#include<stdio.h>
#include <windows.h>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "imageloader.h"

using namespace std;
int flag=1,winter=0,rot=0;
float _angle = 0.0f,_angle2 = 0.0f;
int lrRot=0;
void my_keyboard(unsigned char key, int x, int y)
{

    printf("%c\n",key);
    //day
    if(key=='d')
    {
        flag=1;

    }
    //night
    else if(key=='n')
    {
        flag=0;
    }
    //auto rotate
    else if(key=='r')
    {
        rot=0;
        lrRot=1;
    }
    //stop rotation
    else if(key=='s')
    {
        rot=1;
        lrRot=0;
    }
    printf("%d\n",rot);

}


void mySpecialFunc(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
         lrRot=1;
        _angle2 += 1;
        if (_angle2 > 360) _angle2 = 0.0;
        break;
    case GLUT_KEY_LEFT:
         lrRot=1;
        _angle2 -= 1;
        if (_angle2 > 360) _angle2 = 0.0;
        break;
    }
    glutPostRedisplay();
}

GLuint loadTexture(Image* image)
{
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 image->width, image->height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 image->pixels);
    return textureId;
}

GLuint _textureId;
GLuint _textureId1;
GLuint _textureIdB;
GLuint _textureId3;
GLuint _textureIdG;
GLuint _textureIdS;
GLuint _textureIdN;

void initRendering()
{

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    Image* image1 = loadBMP("E:\\AUST\\4_2\\Graphics_Lab\\Final Project\\working-texture\\stoneD.bmp");
    Image* imageBody = loadBMP("E:\\AUST\\4_2\\Graphics_Lab\\Final Project\\working-texture\\middleSlide.bmp");

    Image* imageG = loadBMP("E:\\AUST\\4_2\\Graphics_Lab\\Final Project\\working-texture\\img2.bmp");
    Image* imageS = loadBMP("E:\\AUST\\4_2\\Graphics_Lab\\Final Project\\working-texture\\img3.bmp");
    Image* imageN = loadBMP("E:\\AUST\\4_2\\Graphics_Lab\\Final Project\\working-texture\\nightSky.bmp");

    _textureIdG = loadTexture(imageG);
    delete imageG;
    _textureIdS = loadTexture(imageS);
    delete imageS;

    _textureId1 = loadTexture(image1);
    delete image1;

    _textureIdB = loadTexture(imageBody);
    delete imageBody;

    _textureIdN = loadTexture(imageN);
    delete imageN;
}

//Called when the window is resized
void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


//Draws the 3D scene
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -8.0f);

    //sky
    if(flag==1)
    {
        //day
        GLfloat ambientColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; //Color (0.2, 0.2, 0.2) and intensity //can be greater than 1 so not like color
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

        //day sky image
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureIdS);

    }
    else if(flag==0)
    {

        //Add ambient light
        //sh that shines everywhere in our scene by the same amount
        //every face gets the same amount

        GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2) and intensity //can be greater than 1 so not like color
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

        //Add positioned light
        GLfloat lightColor0[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.5, 0.5)
        GLfloat lightPos0[] = {4.0f, 5.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

        //Add directed light
        GLfloat lightColor1[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
        //Coming from the direction (-1, 0.5, 0.5)
        // 0 because direced light source
        GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

        //night sky image
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureIdN);

    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-8.2f, -1.8f, -3.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(8.2f, -1.8f,-3.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(8.2f, 4.8f, -3.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-8.2f, 4.8f, -3.5f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    if(rot==0)
        glRotatef(_angle, 0.0f, 1.0f, 0.0f);

    if(lrRot==1)
         glRotatef(_angle2, 0.0f, 1.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 0.0f);

    //glRotatef(_angle, 0.0f, 1.0f, 0.0f);
    //glColor3f(1.0f, 1.0f, 0.0f);

    //grass
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdG);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(0.7f, 0.8f, 0.7f);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-8.5f, -1.8f, 8.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(8.5f, -1.8f, 8.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(8.5f, -1.8f, -8.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-8.5f, -1.8f, -8.5f);

    glEnd();

    glDisable(GL_TEXTURE_2D);

    //**************************************************************************************************************
    //TOP VIEW
    //**************************************************************************************************************

    glBegin(GL_QUADS);
    //Begin quadrilateral coordinates

    //Rectangle Middle part
    glColor3f( 0.752941,0.752941,0.752941);

    //9th quad (Lowermost i.e the one with the ground)
    glVertex3f(-2.5f, -1.6f, 2.5f);
    glVertex3f(2.5f, -1.6f, 2.5f);
    glVertex3f(2.5f, -1.6f, -2.5f);
    glVertex3f(-2.5f, -1.6f, -2.5f);

    //8th quad
    glVertex3f(-2.3f, -1.4f, 2.3f);
    glVertex3f(2.3f, -1.4f, 2.3f);
    glVertex3f(2.3f, -1.4f, -2.3f);
    glVertex3f(-2.3f, -1.4f, -2.3f);


    //7th quad
    glVertex3f(-2.1f, -1.2f, 2.1f);
    glVertex3f(2.1f, -1.2f, 2.1f);
    glVertex3f(2.1f, -1.2f, -2.1f);
    glVertex3f(-2.1f, -1.2f, -2.1f);


    //6th quad
    glVertex3f(-1.9f, -1.0f, 1.9f);
    glVertex3f(1.9f, -1.0f, 1.9f);
    glVertex3f(1.9f, -1.0f, -1.9f);
    glVertex3f(-1.9f, -1.0f, -1.9f);


    //5th quad
    glVertex3f(-1.7f, -0.8f, 1.7f);
    glVertex3f(1.7f, -0.8f, 1.7f);
    glVertex3f(1.7f, -0.8f, -1.7f);
    glVertex3f(-1.7f, -0.8f, -1.7f);


    //4th quad
    glVertex3f(-1.5f, -0.6f, 1.5f);
    glVertex3f(1.5f, -0.6f, 1.5f);
    glVertex3f(1.5f, -0.6f, -1.5f);
    glVertex3f(-1.5f, -0.6f, -1.5f);


    //3rd quad
    glVertex3f(-1.3f, -0.4f, 1.3f);
    glVertex3f(1.3f, -0.4f,  1.3f);
    glVertex3f(1.3f, -0.4f,  -1.3f);
    glVertex3f(-1.3f, -0.4f,  -1.3f);

    //2nd quad
    glVertex3f(-1.1f, -0.2f, 1.1f);
    glVertex3f(1.1f, -0.2f, 1.1f);
    glVertex3f(1.1f, -0.2f, -1.1f);
    glVertex3f(-1.1f, -0.2f, -1.1f);

    //1st quad
    glVertex3f(-0.9f, 0.0f, 0.9f);
    glVertex3f(0.9f, 0.0f, 0.9f);
    glVertex3f(0.9f, 0.0f, -0.9f);
    glVertex3f(-0.9f, 0.0f, -0.9f);


    //Top Room
    glVertex3f(-0.6f, 0.5f, 0.7f);
    glVertex3f(0.6f, 0.5f, 0.7f);
    glVertex3f(0.6f, 0.5f, -0.7f);
    glVertex3f(-0.6f, 0.5f, -0.7f);


    glEnd(); //End quadrilateral coordinate

    //**************************************************************************************************************
    //FRONT VIEW
    //**************************************************************************************************************
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdB);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    //Begin quadrilateral coordinates
    glColor3f( 0.752941,0.752941,0.752941);  //Grey Color

    //9th quad (Lowermost i.e the one with the ground)


    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, -1.8f, 2.5f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(2.5f, -1.8f, 2.5f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(2.5f, -1.6f, 2.5f);
    glTexCoord2f(0.0f,20.0f);
    glVertex3f(-2.5f, -1.6f, 2.5f);

    //8th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.3f, -1.6f, 2.3f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(2.3f, -1.6f, 2.3f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(2.3f, -1.4f, 2.3f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-2.3f, -1.4f, 2.3f);


    //7th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.1f, -1.4f, 2.1f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(2.1f, -1.4f, 2.1f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(2.1f, -1.2f, 2.1f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-2.1f, -1.2f, 2.1f);


    //6th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.9f, -1.2f, 1.9f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.9f, -1.2f, 1.9f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.9f, -1.0f, 1.9f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.9f, -1.0f, 1.9f);


    //5th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.7f, -1.0f, 1.7f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.7f, -1.0f, 1.7f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.7f, -0.8f, 1.7f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.7f, -0.8f, 1.7f);


    //4th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.5f, -0.8f, 1.5f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.5f, -0.8f, 1.5f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.5f, -0.6f, 1.5f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.5f, -0.6f, 1.5f);


    //3rd quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.3f, -0.6f, 1.3f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.3f, -0.6f,  1.3f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.3f, -0.4f,  1.3f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.3f, -0.4f,  1.3f);

    //2nd quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.1f, -0.4f, 1.1f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.1f, -0.4f, 1.1f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.1f, -0.2f, 1.1f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.1f, -0.2f, 1.1f);

    //1st quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.9f, -0.2f, 0.9f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(0.9f, -0.2f, 0.9f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(0.9f, -0.0f, 0.9f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-0.9f, -0.0f, 0.9f);


    //Top Room

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.65f, 0.2f, 0.71f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.65f, 0.2f, 0.71f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.65f, 0.5f, 0.71f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.65f, 0.5f, 0.71f);

    glColor3f( 0,0,0);  //black Color for door
    glVertex3f(-0.1f, 0.0f, 0.71f);
    glVertex3f(0.1f, 0.0f, 0.71f);
    glVertex3f(0.1f, 0.15f, 0.71f);
    glVertex3f(-0.1f, 0.15f, 0.71f);

    glColor3f( 0.752941,0.752941,0.752941);  //Grey Color
    glVertex3f(-0.6f, 0.0f, 0.7f);
    glVertex3f(0.6f, 0.0f, 0.7f);
    glVertex3f(0.6f, 0.5f, 0.7f);
    glVertex3f(-0.6f, 0.5f, 0.7f);



    glEnd(); //End quadrilateral coordinate

    //**************************************************************************************************************
    //Front Slide Type Part of the Stairs
    //**************************************************************************************************************

    //glColor3f( 1,0,0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdB);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);


    //left margin of front quad
    glColor3f( 0.329412,0.329412,0.329412);  //color for the margin
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.4f, -1.8f, 2.82f);
    glVertex3f(-0.3f, -1.8f, 2.82f);
    glVertex3f(-0.3f, 0.0f, 0.92f);
    glVertex3f(-0.4f, 0.0f, 0.92f);

    //right margin of front quad

    glVertex3f(0.3f, -1.8f, 2.85f);
    glVertex3f(0.4f, -1.8f, 2.85f);
    glVertex3f(0.4f, 0.0f, 0.95f);
    glVertex3f(0.3f, 0.0f, 0.95f);

    glColor3f( 0.752941,0.752941,0.752941);  //Grey Color

    //Front Quad
    glNormal3f(0.0f, 0.0f, 1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.4f, -1.8f, 2.8f);

    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(0.4f, -1.8f, 2.8f);

    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(0.4f, 0.0f, 0.9f);

    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-0.4f, 0.0f, 0.9f);


    //Right Side Quad
    glVertex3f(0.4f, -1.8f, 2.8f);
    glVertex3f(0.4f, -1.8f, 0.0f);
    glVertex3f(0.4f, 0.0f, 0.0f);
    glVertex3f(-0.4f, 0.0f, 0.9f);


    //Left Side Quad
    glVertex3f(-0.4f, -1.8f, 2.8f);
    glVertex3f(-0.4f, -1.8f, 0.0f);
    glVertex3f(-0.4f, 0.0f, 0.0f);
    glVertex3f(-0.4f, 0.0f, 0.9f);

    glEnd();


    //**************************************************************************************************************
    //RIGHT SIDE VIEW
    //**************************************************************************************************************

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdB);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    //Begin quadrilateral coordinates

    //Rectangle Middle part
    glColor3f( 0.752941,0.752941,0.752941);
    glNormal3f(1.0f, 0.0f, 0.0f);

    //9th quad (Lowermost i.e the one with the ground)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -1.8f, 2.5f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(2.5f, -1.8f, -2.5f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(2.5f, -1.6f, -2.5f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(2.5f, -1.6f, 2.5f);

    //8th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.3f, -1.6f, 2.3f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(2.3f, -1.6f, -2.3f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(2.3f, -1.4f, -2.3f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(2.3f, -1.4f, 2.3f);

    //7th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.1f, -1.4f, 2.1f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(2.1f, -1.4f, -2.1f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(2.1f, -1.2f, -2.1f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(2.1f, -1.2f, 2.1f);

    //6th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.9f, -1.2f, 1.9f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.9f, -1.2f, -1.9f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.9f, -1.0f, -1.9f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(1.9f, -1.0f, 1.9f);

    //5th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.7f, -1.0f, 1.7f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.7f, -1.0f, -1.7f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.7f, -0.8f, -1.7f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(1.7f, -0.8f, 1.7f);

    //4th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.5f, -0.8f, 1.5f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.5f, -0.8f, -1.5f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.5f, -0.6f, -1.5f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(1.5f, -0.6f, 1.5f);


    //3rd quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.3f, -0.6f, 1.3f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.3f, -0.6f, -1.3f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.3f, -0.4f, -1.3f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(1.3f, -0.4f, 1.3f);

    //2nd quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.1f, -0.4f, 1.1f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.1f, -0.4f, -1.1f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.1f, -0.2f, -1.1f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(1.1f, -0.2f, 1.1f);

    //1st quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.9f, -0.2f, 0.9f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(0.9f, -0.2f, -0.9f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(0.9f, -0.0f, -0.9f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(0.9f, -0.0f, 0.9f);


    //Top Room
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.65f, 0.2f, 0.75f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.65f, 0.2f, -0.75f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.65f, 0.5f, -0.75f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.65f, 0.5f, 0.75f);

    glColor3f( 0,0,0);  //black Color for door
    glVertex3f(0.61f, 0.0f, 0.1f);
    glVertex3f(0.61f, 0.0f, -0.1f);
    glVertex3f(0.61f, 0.15f, -0.1f);
    glVertex3f(0.61f, 0.15f, 0.1f);

    glColor3f( 0.752941,0.752941,0.752941);  //Grey Color

    glVertex3f(0.6f, 0.0f, 0.7f);
    glVertex3f(0.6f, 0.0f, -0.7f);
    glVertex3f(0.6f, 0.5f, -0.7f);
    glVertex3f(0.6f, 0.5f, 0.7f);


    glEnd(); //End quadrilateral coordinates

    //**************************************************************************************************************
    //Right Side Slide Type Part of the Stairs
    //**************************************************************************************************************

    //glColor3f( 1,0,0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdB);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);


    //left margin of front quad
    glColor3f( 0.329412,0.329412,0.329412);  //color for the margin
    glVertex3f(2.82f, -1.8f, -0.4f);
    glVertex3f(2.82f, -1.8f, -0.3f);
    glVertex3f(0.92f, 0.0f, -0.3f);
    glVertex3f(0.92f, 0.0f, -0.4f);

    //right margin of front quad
    glVertex3f(2.82f, -1.8f, 0.4f);
    glVertex3f(2.82f, -1.8f, 0.3f);
    glVertex3f(0.92f, 0.0f, 0.3f);
    glVertex3f(0.92f, 0.0f, 0.4f);

    glColor3f( 0.752941,0.752941,0.752941);  //Grey Color

    //Front Quad
    glNormal3f(0.0f, 0.0f, 1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.8f, -1.8f, 0.4f);

    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(2.8f, -1.8f, -0.4f);

    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(0.9f, 0.0f, -0.4f);

    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(0.9f, 0.0f, 0.4f);

    //Right Quad
    glVertex3f(2.0f, -1.8f, -0.4f);
    glVertex3f(2.8f, -1.8f, -0.4f);
    glVertex3f(0.9f, 0.0f, -0.4f);
    glVertex3f(0.0f, 0.0f, -0.4f);

    //Left Quad
    glVertex3f(2.0f, -1.8f, 0.4f);
    glVertex3f(2.8f, -1.8f, 0.4f);
    glVertex3f(0.9f, 0.0f, 0.4f);
    glVertex3f(0.0f, 0.0f, 0.4f);

    glEnd();


    //**************************************************************************************************************
    //BACK VIEW
    //**************************************************************************************************************

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdB);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    //Begin quadrilateral coordinates

    //Rectangle Middle part
    glColor3f( 0.752941,0.752941,0.752941);
    glNormal3f(0.0f, 0.0f, -1.0f);

    //9th quad (Lowermost i.e the one with the ground)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, -1.8f, -2.5f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(2.5f, -1.8f, -2.5f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(2.5f, -1.6f, -2.5f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-2.5f, -1.6f, -2.5f);

    //8th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.3f, -1.6f, -2.3f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(2.3f, -1.6f, -2.3f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(2.3f, -1.4f, -2.3f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-2.3f, -1.4f, -2.3f);

    //7th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.1f, -1.4f, -2.1f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(2.1f, -1.4f, -2.1f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(2.1f, -1.2f, -2.1f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-2.1f, -1.2f, -2.1f);

    //6th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.9f, -1.2f, -1.9f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.9f, -1.2f, -1.9f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.9f, -1.0f, -1.9f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.9f, -1.0f, -1.9f);

    //5th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.7f, -1.0f, -1.7f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.7f, -1.0f, -1.7f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.7f, -0.8f, -1.7f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.7f, -0.8f, -1.7f);

    //4th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.5f, -0.8f, -1.5f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.5f, -0.8f, -1.5f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.5f, -0.6f, -1.5f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.5f, -0.6f, -1.5f);


    //3rd quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.3f, -0.6f, -1.3f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.3f, -0.6f, -1.3f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.3f, -0.4f, -1.3f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.3f, -0.4f, -1.3f);

    //2nd quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.1f, -0.4f, -1.1f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(1.1f, -0.4f, -1.1f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(1.1f, -0.2f, -1.1f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.1f, -0.2f, -1.1f);

    //1st quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.9f, -0.2f, -0.9f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(0.9f, -0.2f, -0.9f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(0.9f, -0.0f, -0.9f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-0.9f, -0.0f, -0.9f);


    //Top Room
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.65f, 0.2f, -0.71f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.65f, 0.2f, -0.71f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.65f, 0.5f, -0.71f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.65f, 0.5f, -0.71f);

    glColor3f( 0,0,0);  //black Color for door
    glVertex3f(-0.1f, 0.0f, -0.71f);
    glVertex3f(0.1f, 0.0f, -0.71f);
    glVertex3f(0.1f, 0.15f, -0.71f);
    glVertex3f(-0.1f, 0.15f, -0.71f);

    glColor3f( 0.752941,0.752941,0.752941);  //Grey Color

    glVertex3f(-0.6f, 0.0f, -0.7f);
    glVertex3f(0.6f, 0.0f, -0.7f);
    glVertex3f(0.6f, 0.5f, -0.7f);
    glVertex3f(-0.6f, 0.5f, -0.7f);


    glEnd(); //End quadrilateral coordinates

    //**************************************************************************************************************
    //Back Slide Type Part of the Stairs
    //**************************************************************************************************************
    //glColor3f( 1,0,0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdB);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);

    //left margin of front quad
    glColor3f( 0.329412,0.329412,0.329412);  //color for the margin
    glVertex3f(-0.4f, -1.8f, -2.82f);
    glVertex3f(-0.3f, -1.8f, -2.82f);
    glVertex3f(-0.3f, 0.0f, -0.92f);
    glVertex3f(-0.4f, 0.0f, -0.92f);

    //right margin of front quad
    glVertex3f(0.3f, -1.8f, -2.82f);
    glVertex3f(0.4f, -1.8f, -2.82f);
    glVertex3f(0.4f, 0.0f, -0.92f);
    glVertex3f(0.3f, 0.0f, -0.92f);

    glColor3f( 0.752941,0.752941,0.752941);  //Grey Color
    //Front Quad
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.4f, -1.8f, -2.8f);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(0.4f, -1.8f, -2.8f);
    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(0.4f, 0.0f, -0.9f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-0.4f, 0.0f, -0.9f);


    //Right Side Quad
    glVertex3f(0.4f, -1.8f, -2.8f);
    glVertex3f(0.4f, -1.8f, -2.0f);
    glVertex3f(0.4f, 0.0f, 0.0f);
    glVertex3f(-0.4f, 0.0f, -0.9f);


    //Left Side Quad
    glVertex3f(-0.4f, -1.8f, -2.8f);
    glVertex3f(-0.4f, -1.8f, -2.0f);
    glVertex3f(-0.4f, 0.0f, 0.0f);
    glVertex3f(-0.4f, 0.0f, -0.9f);

    glEnd();


    //**************************************************************************************************************
    //LEFT SIDE VIEW
    //**************************************************************************************************************

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdB);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    //Begin quadrilateral coordinates

    //Rectangle Middle part
    glColor3f( 0.752941,0.752941,0.752941);
    glNormal3f(-1.0f, 0.0f, 0.0f);

    //9th quad (Lowermost i.e the one with the ground)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, -1.8f, 2.5f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(-2.5f, -1.8f, -2.5f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(-2.5f, -1.6f, -2.5f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-2.5f, -1.6f, 2.5f);

    //8th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.3f, -1.6f, 2.3f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(-2.3f, -1.6f, -2.3f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(-2.3f, -1.4f, -2.3f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-2.3f, -1.4f, 2.3f);

    //7th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.1f, -1.4f, 2.1f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(-2.1f, -1.4f, -2.1f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(-2.1f, -1.2f, -2.1f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-2.1f, -1.2f, 2.1f);

    //6th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.9f, -1.2f, 1.9f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(-1.9f, -1.2f, -1.9f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(-1.9f, -1.0f, -1.9f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.9f, -1.0f, 1.9f);

    //5th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.7f, -1.0f, 1.7f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(-1.7f, -1.0f, -1.7f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(-1.7f, -0.8f, -1.7f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.7f, -0.8f, 1.7f);

    //4th quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.5f, -0.8f, 1.5f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(-1.5f, -0.8f, -1.5f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(-1.5f, -0.6f, -1.5f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.5f, -0.6f, 1.5f);


    //3rd quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.3f, -0.6f, 1.3f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(-1.3f, -0.6f, -1.3f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(-1.3f, -0.4f, -1.3f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.3f, -0.4f, 1.3f);

    //2nd quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.1f, -0.4f, 1.1f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(-1.1f, -0.4f, -1.1f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(-1.1f, -0.2f, -1.1f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.1f, -0.2f, 1.1f);

    //1st quad
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.9f, -0.2f, 0.9f);
    glTexCoord2f(20.0f, 0.0f);
    glVertex3f(-0.9f, -0.2f, -0.9f);
    glTexCoord2f(20.0f, 20.0f);
    glVertex3f(-0.9f, -0.0f, -0.9f);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-0.9f, -0.0f, 0.9f);


    //Top Room
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.65f, 0.2f, 0.75f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.65f, 0.2f, -0.75f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.65f, 0.5f, -0.75f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.65f, 0.5f, 0.75f);

    glColor3f( 0,0,0);  //black Color for door
    glVertex3f(-0.61f, 0.0f, 0.1f);
    glVertex3f(-0.61f, 0.0f, -0.1f);
    glVertex3f(-0.61f, 0.15f, -0.1f);
    glVertex3f(-0.61f, 0.15f, 0.1f);

    glColor3f( 0.752941,0.752941,0.752941);  //Grey Color

    glVertex3f(-0.6f, 0.0f, 0.7f);
    glVertex3f(-0.6f, 0.0f, -0.7f);
    glVertex3f(-0.6f, 0.5f, -0.7f);
    glVertex3f(-0.6f, 0.5f, 0.7f);


    glEnd(); //End quadrilateral coordinates


    //**************************************************************************************************************
    //LEFT Side Slide Type Part of the Stairs
    //**************************************************************************************************************



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureIdB);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glColor3f( 1,0,0);
    glBegin(GL_QUADS);

    //left margin of front quad
    glColor3f( 0.329412,0.329412,0.329412);  //color for the margin
    glVertex3f(-2.82f, -1.8f, -0.4f);
    glVertex3f(-2.82f, -1.8f, -0.3f);
    glVertex3f(-0.92f, 0.0f, -0.3f);
    glVertex3f(-0.92f, 0.0f, -0.4f);

    //right margin of front quad
    glVertex3f(-2.82f, -1.8f, 0.4f);
    glVertex3f(-2.82f, -1.8f, 0.3f);
    glVertex3f(-0.92f, 0.0f, 0.3f);
    glVertex3f(-0.92f, 0.0f, 0.4f);

    glColor3f( 0.752941,0.752941,0.752941);  //Grey Color

    //Front Quad
    glNormal3f(0.0f, 0.0f, 1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.8f, -1.8f, 0.4f);

    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(-2.8f, -1.8f, -0.4f);

    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(-0.9f, 0.0f, -0.4f);

    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-0.9f, 0.0f, 0.4f);

    //Right Quad
    glVertex3f(-2.0f, -1.8f, -0.4f);
    glVertex3f(-2.8f, -1.8f, -0.4f);
    glVertex3f(-0.9f, 0.0f, -0.4f);
    glVertex3f(0.0f, 0.0f, -0.4f);

    //Left Quad
    glVertex3f(-2.0f, -1.8f, 0.4f);
    glVertex3f(-2.8f, -1.8f, 0.4f);
    glVertex3f(-0.9f, 0.0f, 0.4f);
    glVertex3f(0.0f, 0.0f, 0.4f);

    glEnd();

    glutSwapBuffers();
}

void update(int value)
{
    _angle += 1.5f;
    if (_angle > 360)
    {
        _angle -= 360;
    }

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);

    //Create the window
    glutCreateWindow("Lighting ");
    initRendering();

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(my_keyboard);
    glutReshapeFunc(handleResize);
    glutSpecialFunc(mySpecialFunc);

    glutTimerFunc(25, update, 0); //Add a timer

    glutMainLoop();
    return 0;
}









