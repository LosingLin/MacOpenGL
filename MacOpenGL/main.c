//
//  main.c
//  MacOpenGL
//
//  Created by qiusnay on 13-9-2.
//  Copyright (c) 2013年 qiusnay. All rights reserved.
//

#include <stdio.h>
#include <GLUT/GLUT.h>
#include "MYImage.h"

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

static GLfloat rtri = 0.0f;
static GLfloat rquad = 0.0f;

GLuint texture[1] = {0};

GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -7.0f);
    glRotatef(rquad, 1.0f, 1.0f, 1.0f);
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    glBegin(GL_QUADS);
    
//    glColor3f(0.0f, 1.0f, 0.0f);
    glNormal3f( 0.0f, 0.0f, 1.0f);					// 法线指向观察者
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    
//    glColor3f(1.0f, 0.5f, 0.0f);
    glNormal3f( 0.0f, 0.0f,-1.0f);					// 法线背向观察者
    
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    
//    glColor3f(1.0f, 0.0f, 0.0f);
    glNormal3f( 0.0f, 1.0f, 0.0f);					// 法线向上
    
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    
//    glColor3f(1.0f, 1.0f, 0.0f);
    glNormal3f( 0.0f,-1.0f, 0.0f);					// 法线朝下
    
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    
//    glColor3f(0.0f,0.0f,1.0f);			// 颜色改成蓝色
    glNormal3f( 1.0f, 0.0f, 0.0f);					// 法线朝右
    
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    
//    glColor3f(1.0f,0.0f,1.0f);			// 颜色改成紫罗兰色
    glNormal3f(-1.0f, 0.0f, 0.0f);					// 法线朝左
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);

    glEnd();
    
    glutSwapBuffers();
}

void TimeUpdate(int time)
{
    rtri += 0.2f;
    rquad -= 0.15f;
//    printf("time = %d\n", time);
//    printf("rtri = %f, rquad = %f\n", rtri, rquad);
    glutTimerFunc(17, TimeUpdate, ++time);
    glutPostRedisplay();
}

void LoadTexture()
{
    initMYImage("lena.bmp");
    unsigned int width = 0, height = 0;
    unsigned char* data = readBmpData(&width, &height);
    destoryMYImage();
    
    glGenTextures(1, &texture[0]);
    printf("-----texture->%d", texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
}

void SetupRC()
{
    LoadTexture();
    
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); //深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glEnable(GL_LIGHT0);
}



void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        xRot -= 5.0f;
    }
    if (key == GLUT_KEY_DOWN)
    {
        xRot += 5.0f;
    }
    if (key == GLUT_KEY_LEFT)
    {
        yRot -= 5.0f;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        yRot += 5.0f;
    }
    
    if (key < -1.0f)
    {
        xRot = 355.0f;
        yRot = 355.0f;
    }
    if (key > 356.0f)
    {
        yRot = 0.0f;
        xRot = 0.0f;
    }
    
    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    GLfloat fAspect;
    if (h == 0)
    {
        h = 1;
    }
    fAspect = (GLfloat)w / (GLfloat)h;
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0f, fAspect, 0.1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, const char * argv[])
{
    
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(200, 200);
    glutCreateWindow("Test Mac");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);
    glutTimerFunc(17, TimeUpdate, 12);
    
    SetupRC();
    glutMainLoop();

    return 0;
}

