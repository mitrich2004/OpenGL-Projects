#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>


void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void drawCube()
{
    float rightX = 0.5f;
    float leftX = -0.5f;
    float topY = 0.5;
    float bottomY = -0.5;
    float frontZ = 0.5;
    float backZ = -0.5;

    //Front
    glColor3ub(255, 0, 0);
    glBegin(GL_QUADS);
		glVertex3f(leftX, bottomY, frontZ);
		glVertex3f(leftX, topY, frontZ);
		glVertex3f(rightX, topY, frontZ);
		glVertex3f(rightX, bottomY, frontZ);
	glEnd();

	//Right
    glColor3ub(0, 255, 0);
    glBegin(GL_QUADS);
		glVertex3f(rightX, bottomY, frontZ);
		glVertex3f(rightX, topY, frontZ);
		glVertex3f(rightX, topY, backZ);
		glVertex3f(rightX, bottomY, backZ);
	glEnd();

	//Back
    glColor3ub(0, 0, 255);
    glBegin(GL_QUADS);
		glVertex3f(leftX, bottomY, backZ);
		glVertex3f(leftX, topY, backZ);
		glVertex3f(rightX, topY, backZ);
		glVertex3f(rightX, bottomY, backZ);
	glEnd();

	//Left
    glColor3ub(255, 255, 0);
    glBegin(GL_QUADS);
		glVertex3f(leftX, bottomY, frontZ);
		glVertex3f(leftX, topY, frontZ);
		glVertex3f(leftX, topY, backZ);
		glVertex3f(leftX, bottomY, backZ);
	glEnd();

	//Top
	glColor3ub(0, 255, 255);
    glBegin(GL_QUADS);
		glVertex3f(leftX, topY, frontZ);
		glVertex3f(rightX, topY, frontZ);
		glVertex3f(rightX, topY, backZ);
		glVertex3f(leftX, topY, backZ);
	glEnd();

	//Bottom
	glColor3ub(255, 0, 255);
    glBegin(GL_QUADS);
		glVertex3f(leftX, bottomY, frontZ);
		glVertex3f(rightX, bottomY, frontZ);
		glVertex3f(rightX, bottomY, backZ);
		glVertex3f(leftX, bottomY, backZ);
	glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -7.5f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);

    //Body
    glPushMatrix();
        glScalef(1.25f, 0.75f, 2.25f);
        drawCube();
    glPopMatrix();

    //Tail
    glPushMatrix();
        glTranslatef(0.0f, 0.25f, -2.0f);
        glScalef(0.25f, 0.25f, 2.0f);
        drawCube();
    glPopMatrix();

    //Tail Wing
    glPushMatrix();
        glTranslatef(0.175f, 0.35f, -2.4f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(0.15f, 0.2f, 0.8f);
        drawCube();
    glPopMatrix();

    //Top Wing
    glPushMatrix();
        glTranslatef(0.0f, 0.5f, 0.0f);
        glScalef(3.5f, 0.2f, 0.2f);
        drawCube();
    glPopMatrix();

    //Right Leg
    glPushMatrix();
        glTranslatef(0.5f, -0.55f, 0.0f);
        glScalef(0.2f, 0.2f, 2.25f);
        drawCube();
    glPopMatrix();

    //Left Leg
    glPushMatrix();
        glTranslatef(-0.5f, -0.55f, 0.0f);
        glScalef(0.2f, 0.2f, 2.25f);
        drawCube();
    glPopMatrix();
}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int petla=1;
//    Uint32 start;
    SDL_Event zdarzenie;
    init();
    while (petla==1)
    {
//        start=SDL_GetTicks();
        while (SDL_PollEvent(&zdarzenie))
        {
            switch(zdarzenie.type)
            {
                case SDL_QUIT:
                petla=0;
                break;
            }
        }
        display();
        SDL_GL_SwapBuffers();
//        if (1000/30>(SDL_GetTicks()-start)) SDL_Delay(SDL_GetTicks()-start);
    }
    SDL_Quit();
    return 0;
}
