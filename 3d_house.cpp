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

void display()
{
    float leftX = -1.0f;
    float rightX = 1.0f;
    float bottomY= -1.0f;
    float topY = 1.0f;
    float frontZ = 1.0f;
    float backZ = -1.0f;
    float centerX = 0.0f;
    float roofY = 2.25;
    float centerZ = 0.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -7.5);
    glRotatef(30, 1, 0, 0);
    glRotatef(60, 0, 1, 0);

    //Front Wall
    glColor3ub(255,165,0);
    glBegin(GL_QUADS);
		glVertex3f(leftX, bottomY, frontZ);
		glVertex3f(leftX, topY, frontZ);
		glVertex3f(rightX, topY, frontZ);
		glVertex3f(rightX, bottomY, frontZ);
	glEnd();

	//Right Wall
	glColor3ub(0,0,205);
    glBegin(GL_QUADS);
		glVertex3f(rightX, bottomY, frontZ);
		glVertex3f(rightX, topY, frontZ);
		glVertex3f(rightX, topY, backZ);
		glVertex3f(rightX, bottomY, backZ);
	glEnd();

	//Left Wall
	glColor3ub(0,0,205);
    glBegin(GL_QUADS);
		glVertex3f(leftX, bottomY, frontZ);
		glVertex3f(leftX, topY, frontZ);
		glVertex3f(leftX, topY, backZ);
		glVertex3f(leftX, bottomY, backZ);
	glEnd();

    //Back Wall
    glColor3ub(255,165,0);
    glBegin(GL_QUADS);
		glVertex3f(leftX, bottomY, backZ);
		glVertex3f(leftX, topY, backZ);
		glVertex3f(rightX, topY, backZ);
		glVertex3f(rightX, bottomY, backZ);
	glEnd();

	//Floor
    glColor3ub(255,165,205);
    glBegin(GL_QUADS);
		glVertex3f(leftX, bottomY, backZ);
		glVertex3f(leftX, bottomY, frontZ);
		glVertex3f(rightX, bottomY, frontZ);
		glVertex3f(rightX, bottomY, backZ);
	glEnd();

	//Front Roof
	glColor3ub(0,0,205);
    glBegin(GL_TRIANGLES);
		glVertex3f(leftX, topY, frontZ);
		glVertex3f(rightX, topY, frontZ);
		glVertex3f(centerX, roofY, centerZ);
	glEnd();

	//Right Roof
	glColor3ub(255,165,0);
    glBegin(GL_TRIANGLES);
		glVertex3f(rightX, topY, frontZ);
		glVertex3f(rightX, topY, backZ);
		glVertex3f(centerX, roofY, centerZ);
	glEnd();

	//Left Roof
	glColor3ub(255,165,0);
    glBegin(GL_TRIANGLES);
		glVertex3f(leftX, topY, frontZ);
		glVertex3f(leftX, topY, backZ);
		glVertex3f(centerX, roofY, centerZ);
	glEnd();

	//Back Roof
	glColor3ub(0,0,205);
    glBegin(GL_TRIANGLES);
		glVertex3f(leftX, topY, backZ);
		glVertex3f(rightX, topY, backZ);
		glVertex3f(centerX, roofY, centerZ);
	glEnd();
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
