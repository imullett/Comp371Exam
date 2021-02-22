/////////////////////////////////////////////////
COMP 371 - Midterm Exam - Winter 2021
/////////////////////////////////////////////////

Ian Mullett - 40156056


/////////////////////////////////////////////////
HOW TO RUN
/////////////////////////////////////////////////

Compile source files with CMakeLists.txt

/////////////////////////////////////////////////
FEATURES
/////////////////////////////////////////////////

These are the current features in the application:

- A GLFW window of 1024x768, with double buffering support to render things in.
- A perspective view for the camera.
- The camera can be moved around in a FPS perspective.
- The camera can tilt and pan.
- The camera can move vertically up and down.
- The camera can zoom in and out.
- A 128x128 square grid that acts as a ground surface, drawn in the X Z plane, centered at the origin.
- A set of 3 lines, 7 grid units in length, in 3 different colors, that represent the axis X Y Z.
- Letter models representing the first six letter of Mullett.


- Each model can be incrementally sized up and down
- Each model can be changed position and orientation
- The world orientation can be rotated around both the X axis and Y axis. It
  can also be reset.
- Different rendering modes can be used to render the models. The modes available are:
  Points, Lines and Triangles.
- The application uses OpenGL 3.3, GLFW 3, GLEW and GLM.
- The models were constructed respecting Hierarchical modeling.
- The application can exit by pressing Escape.

/////////////////////////////////////////////////
CONTROLS
/////////////////////////////////////////////////

Here are the different controls for the application. Note that you need to have focus
on the window for them to work:

---

## CAMERA:

- LEFT SHIFT + I : Move forward
- LEFT SHIFT + K : Move backwards
- LEFT SHIFT + J : Move left
- LEFT SHIFT + L : Move right
- - : Move downwards
- = : Move upwards
- RIGHT MOUSE BUTTON: While held down, mouse movement allows to pan the camera.
- MIDDLE MOUSE BUTTON: While held down, mouse movement allows to tilt the camera.
- LEFT MOUSE BUTTON: While held down, mouse movement allows to zoom in and out.

---

## WORLD:

- LEFT ARROW : Rotates the world anti-clockwise about the positive X-Axis
- RIGHT ARROW : Rotates the world clockwise about the positive X-Axis
- UP ARROW : Rotates the world anti-clockwise about the positive Y-Axis
- DOWN ARROW : Rotates the world clockwise about the positive Y-Axis

---

## MODELS:

- P : Change the draw method to Points.
- L : Change the draw method to Lines.
- T : Change the draw method to Triangles.
- 1 : Selects letter T
- 2 : Selects letter E
- 3 : Selects letter L1
- 4 : Selects letter L2
- 5 : Selects letter U
- 6 : Selects letter M
- LEFT SHIFT + A : Moves the selected model left on the X axis.
- LEFT SHIFT + D: Moves the selected model right on the X axis.
- LEFT SHIFT + W : Moves the selected model up on the Y axis.
- LEFT SHIFT + S : Moves the selected model down on the Y axis.
- A : Rotates the selected model left about the Y axis.
- D : Rotates the selected model right about the Y axis.
- U : Scales the selected model up.
- J : Scales the selected model down.

---

## MISC

- ESCAPE: Exit the application
