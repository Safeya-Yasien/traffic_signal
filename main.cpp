#include <Windows.h>
#include <GL/glut.h>
#include <iostream>
#include <unistd.h>
#include <math.h>
# define PI 3.14159265358979323846

int state = 0; // 0: Red, 1: Yellow, 2: Green
float redColor = 1.0, yellowColor = 1.0, greenColor = 1.0;


void init();
void sky();
void drawSun();
void drawTree();
void road();
void Sound();
void drawCircle(int x, int y, float radius);
void drawTrafficSignal();
void update(int value);
void keyboard(unsigned char key, int x, int y);





int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Traffic Signal");

    init();
    glutDisplayFunc(drawTrafficSignal);
    glutTimerFunc(20, update, 0); // Start the timer to change colors every 20 milliseconds
    Sound();

    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}


void drawCircle(int x, int y, float radius) {
    int i;
    int triangleAmount = 10; // Adjust resolution
    GLfloat twicePi = 2.0f * 3.1416;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void sky() {
    glBegin(GL_QUADS);
    glVertex2f(0.0, 600.0);   // Top-left
    glVertex2f(800.0, 600.0); // Top-right
    glVertex2f(800.0, 400.0); // Bottom-right
    glVertex2f(0.0, 400.0);   // Bottom-left
    glEnd();
}

void drawSun() {
    // You can adjust the position and size of the sun as needed
    drawCircle(700, 500, 50);
}

void drawTree() {
      glColor3f(0.5, 0.35, 0.05); // Brown color for the trunk
      glBegin(GL_POLYGON);
      glVertex2i(670, 100);
      glVertex2i(730, 100);
      glVertex2i(730, 250);
      glVertex2i(670, 250);
      glEnd();

      glColor3f(0.0, 0.5, 0.0); // Green color for the leaves
      glBegin(GL_POLYGON);
      glVertex2i(770, 250);
      glVertex2i(630, 250);
      glVertex2i(700, 400);
      glEnd();
}

void road()
{

    glBegin(GL_QUADS);
    glVertex2f(0.0, 200.0);   // Top-left
    glVertex2f(800.0, 200.0); // Top-right
    glVertex2f(800.0, 0.0);   // Bottom-right
    glVertex2f(0.0, 0.0);     // Bottom-left
    glEnd();

    glColor3f(1.0, 1.0, 1.0); // White color for the lines
    glLineWidth(5.0);        // Set the line width
    glBegin(GL_LINES);
        glVertex2i(0, 50);   // First line
        glVertex2i(800, 50);
        glVertex2i(0, 100);   // Second line
        glVertex2i(800, 100);
    glEnd();
}

void drawTrafficSignal() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw sky
    glColor3ub(148, 208, 242);
    sky();

    glColor3f(1.0, 1.0, .5); // Yellow color for the sun
    drawSun();


//    glColor3f(0.5, 0.5, 0.5);  // Gray color for the road
    glColor3ub(52,52,52);
    road();

    drawTree();

        // Draw pole
//    glColor3f(0.2, 0.2, 0.2);
    glColor3ub(95,95,95);
    glBegin(GL_POLYGON);
    glVertex2i(75, 50);  // Adjusted x-coordinate
    glVertex2i(85, 50);  // Adjusted x-coordinate
    glVertex2i(85, 410); // Adjusted x-coordinate
    glVertex2i(75, 410); // Adjusted x-coordinate
    glEnd();

    // Draw red light
    glColor3f(redColor, 0.0, 0.0);
    drawCircle(80, 380, 30);  // Adjusted x-coordinate

    // Draw yellow light
    glColor3f(redColor, yellowColor, 0.0);
    drawCircle(80, 280, 30);  // Adjusted x-coordinate

    // Draw green light
    glColor3f(0.0, greenColor, 0.0);
    drawCircle(80, 180, 30);  // Adjusted x-coordinate

    glutSwapBuffers();
}

void update(int value) {
      const float colorChangeRate = 0.01;

      redColor -= colorChangeRate;
      if (redColor <= 0.0) {
            redColor = 1.0;
      }

      yellowColor -= colorChangeRate;
      if (yellowColor <= 0.2) {
            yellowColor = 1.0;
      }

      greenColor -= colorChangeRate;
      if (greenColor <= 0.4) {
            greenColor = 1.0;
      }


      glutPostRedisplay();
      glutTimerFunc(20, update, 0); // Change colors every 20 milliseconds
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) // ASCII code for the ESC key
        exit(0);
}


void Sound()
{
      PlaySound("train.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}

