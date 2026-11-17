#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// Abstract Base Class
class GameObject
{
public:
    virtual void draw() = 0;

     virtual void update()
     {
     }

     virtual ~GameObject()
     {
     }
};

// Derived Class
class Car : public GameObject
{
private:
    float x, y;
    float speed;
    bool automatic;

     // Draw a circular wheel
     void drawWheel(float cx, float cy, float radius)
     {
         glColor3f(0.1f, 0.1f, 0.1f);

          glBegin(GL_TRIANGLE_FAN);

          glVertex2f(cx, cy);

          for(int i = 0; i <= 360; i++)
          {
              float angle = i * 3.14159f / 180.0f;

              glVertex2f(
                  cx + radius * cos(angle),
                  cy + radius * sin(angle)
              );
          }

          glEnd();

          // Inner wheel
          glColor3f(0.7f, 0.7f, 0.7f);

          glBegin(GL_TRIANGLE_FAN);

          glVertex2f(cx, cy);

          for(int i = 0; i <= 360; i++)
          {
              float angle = i * 3.14159f / 180.0f;

              glVertex2f(
                  cx + radius * 0.45f * cos(angle),
                  cy + radius * 0.45f * sin(angle)
              );
          }

          glEnd();
     }

public:

     // Constructor
     Car()
     {
         x = 350;
         y = 180;
         speed = 3;
         automatic = false;
     }

     // Draw the car
     void draw() override
     {
         glPushMatrix();

          glTranslatef(x, y, 0);

          // Car body
          glColor3f(1.0f, 0.0f, 0.0f);

glBegin(GL_POLYGON);

         glVertex2f(-100, 0);
         glVertex2f(-90, 35);
         glVertex2f(-60, 50);
         glVertex2f(55, 50);
         glVertex2f(90, 25);
         glVertex2f(100, 0);

    glEnd();

    // Car roof
    glColor3f(0.0f, 0.2f, 0.9f);

    glBegin(GL_POLYGON);

         glVertex2f(-60, 50);
         glVertex2f(-35, 85);
         glVertex2f(35, 85);
         glVertex2f(55, 50);

    glEnd();

    // Left window
    glColor3f(0.6f, 0.9f, 1.0f);

    glBegin(GL_POLYGON);

         glVertex2f(-52, 53);
         glVertex2f(-32, 78);
         glVertex2f(-5, 78);
         glVertex2f(-5, 53);

    glEnd();
    // Right window
     glBegin(GL_POLYGON);

           glVertex2f(0, 53);
           glVertex2f(0, 78);
           glVertex2f(32, 78);
           glVertex2f(48, 53);

     glEnd();

     // Wheels
     drawWheel(-60, 0, 20);
     drawWheel(60, 0, 20);

     glPopMatrix();
}

// Update car position
void update() override
{
    if(automatic)
    {
        x += speed;

           // Move car back when it reaches screen edge
           if(x > 850)
           {
               x = -100;
           }
     }
}

// Move car left
void moveLeft()
{
    x -= 15;

     if(x < -100)
         x = -100;
}

// Move car right
void moveRight()
{
    x += 15;

     if(x > 850)
         x = 850;
}

// Toggle automatic movement
void toggleMovement()
{
    automatic = !automatic;
}

// Reset car
     void reset()
     {
         x = 350;
         y = 180;
         automatic = false;
     }
};

// Create car object
Car car;

// Base class pointer for runtime polymorphism
GameObject *objects[1] = { &car };

// Display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

     // Sky
     glColor3f(0.5f, 0.8f, 1.0f);

     glBegin(GL_POLYGON);

         glVertex2f(0, 200);
         glVertex2f(800, 200);
         glVertex2f(800, 600);
         glVertex2f(0, 600);

     glEnd();

     // Road
     glColor3f(0.25f, 0.25f, 0.25f);

     glBegin(GL_POLYGON);

         glVertex2f(0, 0);
         glVertex2f(800, 0);
         glVertex2f(800, 200);
         glVertex2f(0, 200);

     glEnd();

     // Road divider
     glColor3f(1.0f, 1.0f, 1.0f);

     glLineWidth(4);

     glBegin(GL_LINES);

         for(int i = 0; i < 800; i += 100)
         {
             glVertex2f(i, 100);
             glVertex2f(i + 50, 100);
         }

     glEnd();

     // Draw objects using polymorphism
     for(int i = 0; i < 1; i++)
     {
         objects[i]->draw();
     }

     glutSwapBuffers();
}

// Timer function
void timer(int value)
{
    // Update objects using polymorphism
    for(int i = 0; i < 1; i++)
    {
        objects[i]->update();
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// Keyboard controls
void keyboard(unsigned char key, int mouseX, int mouseY)
{
    switch(key)
    {
        case ' ':
            car.toggleMovement();
            break;

         case 'r':
         case 'R':
             car.reset();
             break;

case 'q':
        case 'Q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

// Special keyboard controls
void specialKeys(int key, int mouseX, int mouseY)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            car.moveLeft();
            break;

        case GLUT_KEY_RIGHT:
            car.moveRight();
            break;
    }

    glutPostRedisplay();
}

// Initialize OpenGL
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Experiment 7 - Moving Car using OOP");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutTimerFunc(16, timer, 0);

    cout << "\n===== MOVING CAR CONTROLS =====\n";
    cout << "LEFT ARROW - Move car left\n";
    cout << "RIGHT ARROW - Move car right\n";
    cout << "SPACE       - Start/Stop automatic movement\n";
    cout << "R           - Reset car position\n";
    cout << "Q           - Exit program\n";

    glutMainLoop();

    return 0;
}
