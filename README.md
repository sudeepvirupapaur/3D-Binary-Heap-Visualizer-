# 3D-Binary-Heap-Visualizer-

The provided code is a C++ program using OpenGL and GLUT to visualize binary heaps in 3D. It renders two types of heaps: a max-heap and a min-heap, using spheres to represent the nodes and lines to represent the edges between them.

Key Components:
Heap Data: Two vectors, maxHeapArray and minHeapArray, hold the values for the max-heap and min-heap respectively.

Camera Rotation: The angleX, angleY, and angleZ variables control the rotation of the 3D view around the X, Y, and Z axes. Flags (rotateX, rotateY, rotateZ) determine which axis is currently being rotated.

Drawing Functions:

drawText(): Renders text at specified 3D coordinates.
drawNode(): Draws a sphere representing a heap node and its value.
drawEdge(): Draws lines connecting nodes to their children.
drawHeap(): Recursively draws the nodes and edges of a heap.
Display Function:

Sets up the view and projections, applies rotations, and draws both heaps with labels.
Timers:

rotationTimer(): Updates the rotation angles to create a smooth rotating effect, triggered every 16 milliseconds.
iterationTimer(): Advances the display of heap nodes step-by-step every 800 milliseconds.
Input Handling:

keyboard(): Exits the application when the ESC key is pressed.
mouse(): Starts rotation along different axes based on mouse button clicks.
Initialization:
The initGL() function sets up OpenGL settings, including background color and depth testing.
Overall, this code provides a dynamic and interactive 3D visualization of binary heaps, allowing users to view and rotate the heaps to understand their structure better.
