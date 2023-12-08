#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <stdlib.h>
#include <time.h>

//variables
float birdPosY = 0.0f;
float blockPosX = 12.0f;
float currBirdSpeed = -0.003f;
float baseBirdSpeed = -0.003f;
float blockSpeed = -0.0015f;
float gravity = 0.0000015f;
float bottomY = -7.3f;
float topY = 7.3f;
float leftX = -12.0f;
float rightX = 12.0f;
float translateZ = -20.0f;
int gap = 6;
int full = 15;
bool gameStarted = false;
float bottomBlockScale;
float topBlockScale;

//functions
int getRandomBlockHeight()
{
    return rand() % gap + 1;
}

int getTopBlockScale()
{
    return full - gap - bottomBlockScale;
}

void generateNewBlocks()
{
    blockPosX = rightX;
    bottomBlockScale = getRandomBlockHeight();
    topBlockScale = getTopBlockScale();
}

void moveObjects()
{
    if (currBirdSpeed > baseBirdSpeed)
    {
        currBirdSpeed -= gravity;
    }

    birdPosY += currBirdSpeed;
    blockPosX += blockSpeed;
}

bool checkForGameOver()
{
    if (birdPosY < bottomY || birdPosY > topY)
    {
        return true;
    }

    if (blockPosX < 2.0f && blockPosX > -2.0f)
    {
        if (birdPosY - 1.0f < bottomY + bottomBlockScale
            || birdPosY + 1.0f > topY - topBlockScale)
        {
            return true;
        }
    }

    return false;
}

void drawBird()
{
    glColor3ub(255, 255, 0);
    glPushMatrix();
        glTranslatef(0.0f, birdPosY, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);
            glVertex3f(1.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, 1.0f, 0.0f);
        glEnd();
    glPopMatrix();
}

void drawBlock(float scale, float posY)
{
    glColor3ub(100, 100, 100);
    glPushMatrix();
        glTranslatef(blockPosX, posY, 0.0f);
        glScalef(1.0f, scale, 1.0f);
        glBegin(GL_QUADS);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);
            glVertex3f(1.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, 1.0f, 0.0f);
        glEnd();
	glPopMatrix();
}

void init()
{
    srand(time(NULL));
    bottomBlockScale = getRandomBlockHeight();
    topBlockScale = getTopBlockScale();
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
    glTranslatef(0.0f, 0.0f, translateZ);
    drawBird();
    drawBlock(bottomBlockScale, bottomY);
    drawBlock(topBlockScale, topY);
}

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    bool loop = true;
    SDL_Event myevent;
    init();
    while (loop)
    {
        while (SDL_PollEvent(&myevent))
        {
            switch(myevent.type)
            {
                case SDL_QUIT:
                loop = false;
                break;

                case SDL_KEYDOWN:
                if (myevent.key.keysym.sym == SDLK_RETURN)
                {
                    loop = false;
                    break;
                }

                if (myevent.key.keysym.sym == SDLK_SPACE)
                {
                    gameStarted = true;
                    currBirdSpeed = -baseBirdSpeed;
                }

                break;
            }
        }

        if (gameStarted)
        {
            moveObjects();

            if (blockPosX < leftX)
            {
                generateNewBlocks();
            }

            if (checkForGameOver())
            {
                loop = false;
                break;
            }
        }

        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
