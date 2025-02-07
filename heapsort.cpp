#include <GL/glut.h>
#include <vector>
#include <string>

// initialising  heap arrays for max-heap
std::vector<int> maxHeapArray = { 40, 30, 28, 10, 15, 25, 35, 5, 8, 12, 7, 5, 2, 1 };


// initialising  heap arrays for min-heap
std::vector<int> minHeapArray = { 1, 2, 5, 5, 7, 8, 10, 12, 15, 25, 28, 30, 35, 40 };

// Camera rotation
float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;

// Rotation states
bool rotateX = false, rotateY = false, rotateZ = false;

// Current insertion step for max-heap and min-heap
int currentMaxStep = 0;
int currentMinStep = 0;

// to draw text eg:3D HEAP VISUALIZER,MIN HEAP,MAX HEAP
 
void drawText(float x, float y, float z, const char* text) {
    glRasterPos3f(x, y, z);

    while(*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text++);
    }
}
// to draw a sphere representing a node
void drawNode(float x, float y, float z, int value, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(r, g, b);
    glutSolidSphere(0.025, 20, 20); 
    glColor3f(1, 1, 1);
// Adjusted text position
    drawText(-0.01f, 0.03f, 0.0f, std::to_string(value).c_str());  
    glPopMatrix();
}

// to draw a edge lines
void drawEdge(float x1, float y1, float z1, float x2, float y2, float z2) {
    glBegin(GL_LINES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glEnd();
}

// Recursive function to draw the binary heap
void drawHeap(const std::vector<int>& heapArray, int index, int maxStep, float x, float y, float z, float xOffset, float yOffset, float rOffset, float gOffset, float bOffset) {
    if (index >= heapArray.size() || index > maxStep) return;

    // Draw the current node
    float r = (index + 1) * rOffset;
    float g = gOffset;
    float b = 1.0f - (index + 1) * bOffset;
    drawNode(x, y, z, heapArray[index], r, g, b);

    // Calculate positions for left and right children
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    float childY = y - yOffset;
    float leftChildX = x - xOffset;
    float rightChildX = x + xOffset;

    // Draw edges and recursively draw children
    if (leftChild < heapArray.size() && leftChild <= maxStep) {
        drawEdge(x, y, z, leftChildX, childY, z);
        drawHeap(heapArray, leftChild, maxStep, leftChildX, childY, z, xOffset / 2, yOffset, rOffset, gOffset, bOffset);
    }
    if (rightChild < heapArray.size() && rightChild <= maxStep) {
        drawEdge(x, y, z, rightChildX, childY, z);
        drawHeap(heapArray, rightChild, maxStep, rightChildX, childY, z, xOffset / 2, yOffset, rOffset, gOffset, bOffset);
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);

   
    drawText(-0.3f, 0.95f, 0.0f, "3D HEAP VISUALIZER");
    drawText(-0.8f, 0.75f, 0.0f, "Max Heap");
    drawText(0.4f, 0.75f, 0.0f, "Min Heap");

    //max heap on the left
    drawHeap(maxHeapArray, 0, currentMaxStep, -0.5f, 0.6f, 0.0f, 0.2f, 0.1f, 0.1f, 0.5f, 0.1f);

    //min heap on the right
    drawHeap(minHeapArray, 0, currentMinStep, 0.5f, 0.6f, 0.0f, 0.2f, 0.1f, 0.05f, 0.5f, 0.05f);

    glutSwapBuffers();
}

// to handle rotations
void rotationTimer(int value) {
    if (rotateX) {
        angleX += 0.2f;
        if (angleX > 360.0f) {
            angleX -= 360.0f;
        }
    }
    if (rotateY) {
        angleY += 0.2f;
        if (angleY > 360.0f) {
            angleY -= 360.0f;
        }
    }
    if (rotateZ) {
        angleZ += 0.2f; 
        if (angleZ > 360.0f) {
            angleZ -= 360.0f;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, rotationTimer, 0); //smoother motion
}

// Timer function for GLUT to handle heap insertion steps
void iterationTimer(int value) {
    if (currentMaxStep < maxHeapArray.size() - 1) {
        currentMaxStep++;
    }
    if (currentMinStep < minHeapArray.size() - 1) {
        currentMinStep++;
    }
    glutPostRedisplay();
    glutTimerFunc(800, iterationTimer, 0); 
}


void keyboard(unsigned char key, int x, int y) {
    if (key == 1) 
        exit(0);
}
//rotation
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        rotateX = rotateY = rotateZ = false;
        switch (button) {
        case GLUT_LEFT_BUTTON:
            rotateY = true;
            break;
        case GLUT_MIDDLE_BUTTON:
            rotateX = true;
            break;
        case GLUT_RIGHT_BUTTON:
            rotateZ = true;
            break;
        }
    }
}


void initGL() {
    glClearColor(0.5, 0.5, 0, 1); 
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
} 


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Binary Heap Visualization");
    initGL();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(16, rotationTimer, 0); 
    glutTimerFunc(800, iterationTimer, 0); 
    glutMainLoop();
    return 0;
}