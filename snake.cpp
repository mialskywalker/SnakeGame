#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>

const int width = 20, height = 20;
int gridSize = 25;
int dirX = 1, dirY = 0;
int snakeX[100], snakeY[100], snakeLength = 5;
int fruitX, fruitY;
char scoreText[20];

void drawSquare(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x * gridSize, y * gridSize);
    glVertex2f((x + 1) * gridSize, y * gridSize);
    glVertex2f((x + 1) * gridSize, (y + 1) * gridSize);
    glVertex2f(x * gridSize, (y + 1) * gridSize);
    glEnd();
}

void drawGrid() {
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            drawSquare(x, y, 0.1f, 0.1f, 0.1f);
}

void drawSnake() {
    for (int i = 0; i < snakeLength; i++)
        drawSquare(snakeX[i], snakeY[i], 0.0f, 1.0f, 0.0f);
}

void drawFruit() {
    drawSquare(fruitX, fruitY, 1.0f, 0.0f, 0.0f);
}

void drawText(const char* text, int x, int y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(x, y);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawSnake();
    drawFruit();
    sprintf(scoreText, "Score: %d", snakeLength - 5);
    drawText(scoreText, 10, 20);
    glutSwapBuffers();
}

void timer(int = 0) {
    for (int i = snakeLength -1; i > 0; i--){
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }
    
    snakeX[0] += dirX;
    snakeY[0] += dirY;

    if (snakeX[0] >= width || snakeX[0] < 0 || snakeY[0] >= height || snakeY[0] < 0)
        exit(0);

    for (int i = 1; i < snakeLength; i++)
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
            exit(0);

    if (snakeX[0] == fruitX && snakeY[0] == fruitY){
        snakeLength++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }

    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

void keyboard(int key, int, int) {
    switch(key) {
        case GLUT_KEY_UP: if (dirY != 1) { dirX = 0; dirY = -1; } break;
        case GLUT_KEY_DOWN: if (dirY != -1) { dirX = 0; dirY = 1; } break;
        case GLUT_KEY_LEFT: if (dirX != 1) { dirX = -1; dirY = 0; } break;
        case GLUT_KEY_RIGHT: if (dirX != -1) { dirX = 1; dirY = 0; } break;
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width * gridSize, height * gridSize, 0);
    srand(time(0));
    fruitX = rand() % width;
    fruitY = rand() % height;

    for (int i = 0; i < snakeLength; i++){
        snakeX[i] = width / 2 - i;
        snakeY[i] = height / 2;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width * gridSize, height * gridSize);
    glutCreateWindow("Snake Game");

    init();

    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutTimerFunc(100, timer, 0);

    glutMainLoop();
    return 0;
}
