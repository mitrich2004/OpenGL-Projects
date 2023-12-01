#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>

float height = 5.0f;
float c = 0.9;
float g = 0.01;
float speed = 0.0f;
float deltaTime = 0.01f;

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
    glTranslatef(0.0f, -2.5f, -10.0f);

    glColor3ub(0, 0, 255);
    glPushMatrix();
        glTranslatef(0.0f, height, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(-0.5f, -0.5f, 0.0f);
            glVertex3f(0.5f, -0.5f, 0.0f);
            glVertex3f(0.5f, 0.5f, 0.0f);
            glVertex3f(-0.5f, 0.5f, 0.0f);
        glEnd();
    glPopMatrix();

    glColor3ub(150, 150, 150);
    glBegin(GL_QUADS);
        glVertex3f(-4.5f, -0.1f, 0.0f);
        glVertex3f(4.5f, -0.1f, 0.0f);
        glVertex3f(4.5f, 0.1f, 0.0f);
        glVertex3f(-4.5f, 0.1f, 0.0f);
    glEnd();
}

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    bool loop = true;
    SDL_Event myEvent;
    init();
    while (loop)
    {
        while (SDL_PollEvent(&myEvent))
        {
            switch(myEvent.type)
            {
                case SDL_QUIT: loop = false; break;
            }
        }

        speed += g * deltaTime;
        float deltaHeight = speed * deltaTime + 0.5 * g * deltaTime * deltaTime;
        height -= deltaHeight;

        if (height <= 0.6)
        {
            speed *= -c;
            height = 0.6;
        }

        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}



