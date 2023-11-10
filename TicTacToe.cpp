#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>

using namespace std;

const int n = 3;

int board[n][n];
int i, j;
int posX = 1, posY = 1;
bool firstPlayerMove = true;

const int passive = 0;
const int active = 1;
const int crossPassive = 10;
const int crossActive = 11;
const int crossTotal = crossPassive * 2 + crossActive;
const int oPassive = -10;
const int oActive = -9;
const int oTotal = oPassive * 2 + oActive;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            board[i][j] = passive;
        }
    }

    board[1][1] = active;
}

void drawSquare()
{
    glBegin(GL_QUADS);
		glVertex3f(-0.5f, -0.5f, -5.0f);
		glVertex3f(0.5f, -0.5f, -5.0f);
		glVertex3f(0.5f, 0.5f, -5.0f);
		glVertex3f(-0.5f, 0.5f, -5.0f);
	glEnd();
}

bool checkForWin()
{
    for (i = 0; i < n; ++i)
    {
        int sumRow = 0;
        int sumColumn = 0;

        for (j = 0; j < n; ++j)
        {
            sumRow += board[i][j];
            sumColumn += board[j][i];
        }

        if (sumRow == oTotal || sumRow == crossTotal
            || sumColumn == oTotal || sumColumn == crossTotal)
        {
            return true;
        }
    }

    int sumFirstDiagonal = board[0][0] + board[1][1] + board[2][2];
    int sumSecondDiagonal = board[0][2] + board[1][1] + board[2][0];

    if (sumFirstDiagonal == oTotal || sumFirstDiagonal == crossTotal
        || sumSecondDiagonal == oTotal || sumSecondDiagonal == crossTotal)
    {
        return true;
    }

    return false;
}

bool checkForDraw()
{
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-1.0f, 1.0f, 0.0f);

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            glPushMatrix();
                glTranslatef(j * 1.05f, -i * 1.05f, 0.0f);

                switch (board[i][j])
                {
                    case passive: glColor3ub(255, 255, 255); break;
                    case active: glColor3ub(0, 255, 0); break;
                    case crossPassive: glColor3ub(255, 0, 0); break;
                    case crossActive: glColor3ub(255, 255, 0); break;
                    case oPassive: glColor3ub(0, 0, 255); break;
                    case oActive: glColor3ub(0, 255, 255); break;
                }

                drawSquare();
            glPopMatrix();
        }
    }

}

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_OPENGL);

    int loop = true;
    SDL_Event myEvent;
    init();
    while (loop == 1)
    {
        while (SDL_PollEvent(&myEvent))
        {
            switch(myEvent.type)
            {
                case SDL_QUIT: loop = 0; break;
                case SDL_KEYDOWN:
                    if (myEvent.key.keysym.sym == SDLK_RETURN)
                    {
                        loop = false;
                        break;
                    }

                    if (myEvent.key.keysym.sym == SDLK_LEFT && posX > 0)
                    {
                        board[posY][posX] -= 1;
                        posX -= 1;
                        board[posY][posX] += 1;
                    }

                    if (myEvent.key.keysym.sym == SDLK_RIGHT && posX < n - 1)
                    {
                        board[posY][posX] -= 1;
                        posX += 1;
                        board[posY][posX] += 1;
                    }

                    if (myEvent.key.keysym.sym == SDLK_UP && posY > 0)
                    {
                        board[posY][posX] -= 1;
                        posY -= 1;
                        board[posY][posX] += 1;
                    }

                    if (myEvent.key.keysym.sym == SDLK_DOWN && posY < n - 1)
                    {
                        board[posY][posX] -= 1;
                        posY += 1;
                        board[posY][posX] += 1;
                    }

                    if (myEvent.key.keysym.sym == SDLK_SPACE && board[posY][posX] == 1)
                    {
                        if (firstPlayerMove)
                        {
                            board[posY][posX] += 10;
                        }
                        else
                        {
                            board[posY][posX] -= 10;
                        }

                        if (checkForWin() || checkForDraw())
                        {
                            loop = false;
                            break;
                        }

                        firstPlayerMove = !firstPlayerMove;
                    }
            }
        }
        display();
        SDL_GL_SwapBuffers();
    }

    SDL_Quit();
    return 0;
}
