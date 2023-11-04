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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3ub(178, 34, 34);
    glBegin(GL_TRIANGLES);
	glVertex3f( 0.0, 1.0, -10.0);
	glVertex3f(-1.0,-1.0, -10.0);
	glVertex3f( 1.0,-1.0, -10.0);
    glEnd();

    glColor3ub(222,184,135);
    glBegin(GL_QUADS);
        glVertex3f(-1.0, -1.0, -10.0);
        glVertex3f(1.0, -1.0, -10.0);
        glVertex3f(1.0, -3.0, -10.0);
        glVertex3f(-1.0, -3.0, -10.0);
    glEnd();

    glColor3ub(139,69,19);
    glBegin(GL_QUADS);
        glVertex3f(-0.75, -3.0, -9.99);
        glVertex3f(-0.2, -3.0, -9.99);
        glVertex3f(-0.2, -2, -9.99);
        glVertex3f(-0.75, -2, -9.99);
    glEnd();

    glColor3ub(135,206,250);
    glBegin(GL_QUADS);
        glVertex3f(0.0, -2.25, -9.99);
        glVertex3f(0.75, -2.25, -9.99);
        glVertex3f(0.75, -1.5, -9.99);
        glVertex3f(0.0, -1.5, -9.99);
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


