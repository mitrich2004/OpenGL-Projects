#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<math.h>

int alpha = 90;
float px = 0.0f;
float pz = 0.0f;
float s = 0.1f;

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
    float leftX = -0.5f;
    float rightX = 0.5f;
    float bottomY = -0.5f;
    float topY = 0.5f;
    float frontZ = -0.5f;
    float backZ = 0.5f;

    //front
    glBegin(GL_QUADS);
		glVertex3f(leftX, bottomY, frontZ);
		glVertex3f(rightX, bottomY, frontZ);
		glVertex3f(rightX, topY, frontZ);
		glVertex3f(leftX, topY, frontZ);
	glEnd();

	//left
    glBegin(GL_QUADS);
		glVertex3f(leftX, bottomY, frontZ);
		glVertex3f(leftX, topY, frontZ);
		glVertex3f(leftX, topY, backZ);
		glVertex3f(leftX, bottomY, backZ);
	glEnd();

	//back
    glBegin(GL_QUADS);
		glVertex3f(leftX, bottomY, backZ);
		glVertex3f(rightX, bottomY, backZ);
		glVertex3f(rightX, topY, backZ);
		glVertex3f(leftX, topY, backZ);
	glEnd();

	//right
    glBegin(GL_QUADS);
		glVertex3f(rightX, bottomY, frontZ);
		glVertex3f(rightX, topY, frontZ);
		glVertex3f(rightX, topY, backZ);
		glVertex3f(rightX, bottomY, backZ);
	glEnd();

	//top
    glBegin(GL_QUADS);
		glVertex3f(rightX, topY, frontZ);
		glVertex3f(leftX, topY, frontZ);
		glVertex3f(leftX, topY, backZ);
		glVertex3f(rightX, topY, backZ);
	glEnd();

	//bottom
    glBegin(GL_QUADS);
		glVertex3f(rightX, bottomY, frontZ);
		glVertex3f(leftX, bottomY, frontZ);
		glVertex3f(leftX, bottomY, backZ);
		glVertex3f(rightX, bottomY, backZ);
	glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -7.5f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glColor3ub(255, 0, 0);

    glPushMatrix();
        glTranslatef(px, 0.0f, pz);
        glRotatef(alpha, 0.0f, 1.0f, 0.0f);
        drawCube();
    glPopMatrix();

    glColor3ub(100, 100, 100);
    glBegin(GL_QUADS);
		glVertex3f(-5.0f, -0.01f, 5.0f);
		glVertex3f(5.0f, -0.01f, 5.0f);
		glVertex3f(5.0f, -0.01f,  -5.0f);
		glVertex3f(-5.0f, -0.01f, -5.0f);
	glEnd();
}

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    bool loop=true;
    SDL_Event myevent;
    init();
    while (loop)
    {
        while (SDL_PollEvent(&myevent))
        {
            switch(myevent.type)
            {
                case SDL_QUIT:
                loop=0;
                break;

                case SDL_KEYDOWN:
                if (myevent.key.keysym.sym==SDLK_RETURN)
                {
                    loop=0;
                    break;
                }

                if (myevent.key.keysym.sym==SDLK_LEFT)
                {
                    alpha += 5;
                }
                if (myevent.key.keysym.sym==SDLK_RIGHT)
                {
                    alpha -= 5;
                }
                if (myevent.key.keysym.sym==SDLK_UP)
                {
                    px += s * cos(alpha / 180.0f * M_PI);
                    pz -= s * sin(alpha / 180.0f * M_PI);
                }

                break;
            }
        }
        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}

