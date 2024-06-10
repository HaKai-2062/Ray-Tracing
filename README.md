# Ray-Tracing
Software Ray tracing based on [Ray Tracing in One Weekend series](https://raytracing.github.io/)

## Libraries
- [GLFW](https://github.com/glfw/glfw)
- [Glad (gl 3.3, OpenGL, Core profile)](https://glad.dav1d.de/)
- [imgui (docking branch)](https://github.com/ocornut/imgui/tree/docking)

## Tools Used
- [CMake](https://cmake.org/)
- [Visual Studio](https://visualstudio.microsoft.com/)

## Building the project
Delete 'out' folder and 'GLFW', 'imgui-docking' from 'vendor' if they exist. Ctrl+S to run the CMakelists.txt file located in the project folder. This will clone the repositories and try to build. In case of GLFW errors, simply re run the CMakelists.txt file.
