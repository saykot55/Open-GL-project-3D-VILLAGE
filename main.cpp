#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

GLfloat cloudRotation = 0.0f; // Initial rotation angle for clouds
GLfloat cloudScale = 1.0f;    // Initial scale factor for clouds
GLfloat cloudTranslation = 0.0f; // Initial translation for clouds
GLfloat verticalScale = 1.0f; // Initial vertical scale factor
float bx = 50;
float sailRotation = 0.0f; // Initial rotation angle for boat sail

void sun(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy) {
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void init(void) {
    glClearColor(0.0, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void clouds() {
    glPushMatrix();
    glTranslatef(cloudTranslation, 0, 0); // Apply translation to the clouds
    glScalef(cloudScale, verticalScale, 1.0f); // Apply scaling to the clouds

    // 1st cloud
    glPushMatrix();
    glTranslatef(460, 460, 0);
    glRotatef(cloudRotation, 0, 0, 1);
    glColor3ub(255, 255, 255);
    sun(20, 30, 0, 0);
    sun(15, 20, -15, 0);
    sun(15, 20, 15, 0);
    glPopMatrix();

    // 2nd cloud
    glPushMatrix();
    glTranslatef(390, 420, 0);
    glRotatef(-cloudRotation, 0, 0, 1);
    sun(20, 30, 0, 0);
    sun(15, 20, 15, 0);
    sun(15, 20, -15, 0);
    glPopMatrix();

    glPopMatrix();
}

void boat() {
    glPushMatrix();
    glTranslatef(bx, 0, 0);

    // Boat body
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(325, 220);
    glVertex2d(400, 220);
    glVertex2d(425, 250);
    glVertex2d(300, 250);
    glEnd();

    // Boat deck
    glColor3ub(205, 133, 63);
    glBegin(GL_POLYGON);
    glVertex2d(325, 250);
    glVertex2d(400, 250);
    glVertex2d(390, 280);
    glVertex2d(335, 280);
    glEnd();

    // Boat cabin
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2d(360, 280);
    glVertex2d(370, 280);
    glVertex2d(370, 310);
    glVertex2d(360, 310);
    glEnd();

    // Sail of the boat
    glTranslatef(360, 310, 0); // Move to the center of the sail
    glRotatef(sailRotation, 0, 1, 0); // Rotate around y-axis
    glTranslatef(-360, -310, 0); // Move back to the original position
    glColor3ub(128, 0, 128);
    glBegin(GL_POLYGON);
    glVertex2d(335, 290);
    glVertex2d(390, 290);
    glVertex2d(390, 375);
    glVertex2d(335, 375);
    glEnd();

    glPopMatrix();

    bx -= 0.12; // Move boat to the left
    if (bx < -450) // If boat is out of view, reset its position
        bx = 85;

    sailRotation += 0.05f; // Increase sail rotation angle
    if (sailRotation > 360.0f) // Reset rotation angle if exceeds 360 degrees
        sailRotation -= 360.0f;

    glutPostRedisplay();
}



void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Ground Color
    glColor3ub(0, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 300);
    glVertex2d(0, 300);
    glEnd();

    // River
    glColor3ub(100, 149, 237);
    glBegin(GL_POLYGON);
    glVertex2d(300, 300);
    glVertex2d(250, 150);
    glVertex2d(400, 150);
    glVertex2d(450, 300);
    glEnd();

    glColor3ub(100, 149, 237);
    glBegin(GL_POLYGON);
    glVertex2d(300, 150);
    glVertex2d(250, 0);
    glVertex2d(400, 0);
    glVertex2d(450, 150);
    glEnd();

    glColor3ub(100, 149, 237);
    glBegin(GL_POLYGON);
    glVertex2d(-40, 200);
    glVertex2d(0, 300);
    glVertex2d(500, 300);
    glVertex2d(500, 200);
    glEnd();

    // Hills
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2d(-40, 300);
    glVertex2d(200, 300);
    glVertex2d(100, 450);
    glEnd();

    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2d(150, 300);
    glVertex2d(350, 300);
    glVertex2d(250, 450);
    glEnd();

    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2d(300, 300);
    glVertex2d(520, 300);
    glVertex2d(400, 450);
    glEnd();

    // Boat design function call
    boat();

    // House Tree
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2d(50, 150);
    glVertex2d(70, 150);
    glVertex2d(70, 300);
    glVertex2d(50, 300);
    glEnd();

    // Tree leaf
    glColor3ub(0, 128, 0);
    sun(30, 40, 35, 320);
    sun(30, 40, 85, 320);
    sun(25, 30, 45, 370);
    sun(30, 30, 70, 370);
    sun(25, 30, 55, 400);

    // 1ST House (3D)
    glColor3ub(210, 105, 30);
    glBegin(GL_QUADS);
    // Front face
    glVertex3d(100, 220, 0);
    glVertex3d(200, 220, 0);
    glVertex3d(175, 270, 0);
    glVertex3d(130, 270, 0);

    // Back face
    glVertex3d(100, 220, -50);
    glVertex3d(200, 220, -50);
    glVertex3d(175, 270, -50);
    glVertex3d(130, 270, -50);

    // Left face
    glVertex3d(100, 220, 0);
    glVertex3d(100, 220, -50);
    glVertex3d(130, 270, -50);
    glVertex3d(130, 270, 0);

    // Right face
    glVertex3d(200, 220, 0);
    glVertex3d(200, 220, -50);
    glVertex3d(175, 270, -50);
    glVertex3d(175, 270, 0);

    // Top face
    glVertex3d(100, 220, 0);
    glVertex3d(200, 220, 0);
    glVertex3d(175, 270, 0);
    glVertex3d(130, 270, 0);

    // Bottom face
    glVertex3d(100, 220, -50);
    glVertex3d(200, 220, -50);
    glVertex3d(175, 270, -50);
    glVertex3d(130, 270, -50);
    glEnd();

    // Roof triangle
    glColor3ub(244, 164, 96);
    glBegin(GL_TRIANGLES);
    glVertex3d(100, 270, 0);
    glVertex3d(200, 220, 0);
    glVertex3d(130, 270, 0);
    glEnd();

    // Door
    glColor3ub(160, 82, 45);
    glBegin(GL_QUADS);
    glVertex3d(140, 220, 0);
    glVertex3d(165, 220, 0);
    glVertex3d(165, 250, 0);
    glVertex3d(140, 250, 0);
    glEnd();

    // Window
    glColor3ub(160, 82, 45);
    glBegin(GL_QUADS);
    glVertex3d(110, 240, 0);
    glVertex3d(120, 240, 0);
    glVertex3d(120, 250, 0);
    glVertex3d(110, 250, 0);
    glEnd();

    //LEAVES AND Grass
    glColor3ub(210, 105, 30);
    glBegin(GL_POLYGON);
    glVertex2d(100, 220);
    glVertex2d(200, 220);
    glVertex2d(175, 270);
    glVertex2d(130, 270);
    glEnd();
    glColor3ub(244, 164, 96);
    glBegin(GL_POLYGON);
    glVertex2d(100, 170);
    glVertex2d(185, 170);
    glVertex2d(185, 220);
    glVertex2d(100, 220);
    glEnd();
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2d(100, 170);
    glVertex2d(190, 170);
    glVertex2d(190, 160);
    glVertex2d(100, 160);
    glEnd();
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2d(140, 170);
    glVertex2d(165, 170);
    glVertex2d(165, 200);
    glVertex2d(140, 200);
    glEnd();
    //---
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2d(0, 220);
    glVertex2d(135, 220);
    glVertex2d(110, 270);
    glVertex2d(25, 270);
    glEnd();
    glColor3ub(255, 222, 173);
    glBegin(GL_POLYGON);
    glVertex2d(10, 220);
    glVertex2d(50, 220);
    glVertex2d(25, 255);
    glEnd();
    glColor3ub(255, 222, 173);
    glBegin(GL_POLYGON);
    glVertex2d(10, 150);
    glVertex2d(50, 150);
    glVertex2d(50, 220);
    glVertex2d(10, 220);
    glEnd();
    glColor3ub(222, 184, 135);
    glBegin(GL_POLYGON);
    glVertex2d(50, 150);
    glVertex2d(125, 150);
    glVertex2d(125, 220);
    glVertex2d(50, 220);
    glEnd();
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2d(10, 150);
    glVertex2d(125, 150);
    glVertex2d(125, 140);
    glVertex2d(10, 140);
    glEnd();
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2d(75, 150);
    glVertex2d(95, 150);
    glVertex2d(95, 195);
    glVertex2d(75, 195);
    glEnd();
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2d(20, 200);
    glVertex2d(35, 200);
    glVertex2d(35, 175);
    glVertex2d(20, 175);
    glEnd();

    // 2ND HOUSE 3D
    // Top face
    glColor3ub(160, 82, 45);
    glBegin(GL_QUADS);
    glVertex3d(0, 270, 0);
    glVertex3d(135, 270, 0);
    glVertex3d(135, 270, -50);
    glVertex3d(0, 270, -50);
    glEnd();

    // House door
    glColor3ub(160, 82, 45);
    glBegin(GL_QUADS);
    // Front face
    glVertex3d(50, 220, 0);
    glVertex3d(85, 220, 0);
    glVertex3d(85, 250, 0);
    glVertex3d(50, 250, 0);

    // Back face
    glVertex3d(50, 220, -10);
    glVertex3d(85, 220, -10);
    glVertex3d(85, 250, -10);
    glVertex3d(50, 250, -10);

    // Right face
    glVertex3d(85, 220, 0);
    glVertex3d(85, 220, -10);
    glVertex3d(85, 250, -10);
    glVertex3d(85, 250, 0);

    // Left face
    glVertex3d(50, 220, 0);
    glVertex3d(50, 220, -10);
    glVertex3d(50, 250, -10);
    glVertex3d(50, 250, 0);

    // Top face
    glVertex3d(50, 250, 0);
    glVertex3d(85, 250, 0);
    glVertex3d(85, 250, -10);
    glVertex3d(50, 250, -10);
    glEnd();

    // Window
    glColor3ub(160, 82, 45);
    glBegin(GL_QUADS);
    // Back face
    glVertex3d(10, 240, -10);
    glVertex3d(30, 240, -10);
    glVertex3d(30, 260, -10);
    glVertex3d(10, 260, -10);

    // Right face
    glVertex3d(30, 240, 0);
    glVertex3d(30, 240, -10);
    glVertex3d(30, 260, -10);
    glVertex3d(30, 260, 0);

    // Left face
    glVertex3d(10, 240, 0);
    glVertex3d(10, 240, -10);
    glVertex3d(10, 260, -10);
    glVertex3d(10, 260, 0);
    glEnd();

    // Sun design
    glColor3ub(255, 215, 0);
    sun(25, 30, 175, 450);

    // Clouds function
    clouds();

    glFlush();
    glutSwapBuffers();
}

// Function to handle keyboard input for cloud rotation, scaling, and translation
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'r':
            cloudRotation += 5.0f; // Increase rotation angle by 5 degrees
            break;
        case 'l':
            cloudRotation -= 5.0f; // Decrease rotation angle by 5 degrees
            break;
        case 's':
            cloudScale += 0.1f;    // Increase scale factor by 0.1
            break;
        case 'd':
            cloudScale -= 0.1f;    // Decrease scale factor by 0.1
            break;
        case 't':
            cloudTranslation -= 5.0f; // Move clouds to the left by 5 units
            break;
        case 'y':
            cloudTranslation += 5.0f; // Move clouds to the right by 5 units
            break;
        case 'u':
            verticalScale += 0.1f; // Increase vertical scale factor by 0.1
            break;
        case 'i':
            verticalScale -= 0.1f; // Decrease vertical scale factor by 0.1
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

// Function to update the rotation of the boat sail
void update(int value) {
    sailRotation += 2.0f; // Increment the sail rotation angle
    if (sailRotation > 45.0f) // Limit the rotation angle
        sailRotation = -45.0f;
    glutPostRedisplay();
    glutTimerFunc(100, update, 0); // Recall the function after 100 milliseconds
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Village Scenery");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(25, update, 0); // Call update function every 25 milliseconds
    glutMainLoop();
    return 0;
}
