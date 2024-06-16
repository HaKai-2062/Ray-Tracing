# Ray-Tracing
Software Ray tracing based on [Ray Tracing by The Cherno](https://www.youtube.com/playlist?list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl).

Initially, [Ray Tracing in One Weekend series](https://raytracing.github.io/) was followed but it was not good enough for real time application . It is a good resource nonetheless and was very helpful for setting up material system without pre-requisite knowledge about the subject matter.

## Key features
 - Three types of materials are supported: Lambertian, Metal and Dielectric.
 - The name for their base/solid color is called as Albedo.
 - Lambertian has most roughness and are non metallic.
 - Metals can have roughnesses that dictate the amount of scatter they produce when a light ray hits the surface.
- Dielectric material can reflect and refract light. They let light pass through them and have concepts like Total Internal Reflection. Typically, a change in medium occurs so a refractive index is needed. FresnelSchlick approximates whether reflection or refraction can occur.
- Another subtype of materials is called Emissivity which means that objects can emit their own light instead of relying on sky color for contribution in lighting the scene.

## Libraries
- [GLFW](https://github.com/glfw/glfw)
- [Glad (gl 3.3, OpenGL, Core profile)](https://glad.dav1d.de/)
- [glm](https://github.com/g-truc/glm)
- [imgui (docking branch)](https://github.com/ocornut/imgui/tree/docking)

## Tools Used
- [CMake](https://cmake.org/)
- [Visual Studio](https://visualstudio.microsoft.com/)

## Building the project
- Open the project directory inside Visual Studio.
- Open the CMakelists.txt file located in the project folder and Ctrl+S. This will clone and build the dependencies.
- In case of CMake related issues, delete 'out' folder and try rebuilding.

## Examples from the project
#### Sun modelled as emissive and green ball and ground as Lambertian materials.
![I1](https://raw.githubusercontent.com/HaKai-2062/Ray-Tracing/main/res/git/Emissive_Lambert.png)

#### Green ball is emissive. Ground is a shiny metal (0.05 roughness) and a dielectric (glass with refractive index 1.5) is modelled
![I2](https://raw.githubusercontent.com/HaKai-2062/Ray-Tracing/main/res/git/Emissive_Metal_Dielectric.png)

#### Cover example from [Ray Tracing in One Weekend series](https://raytracing.github.io/)
![I3](https://raw.githubusercontent.com/HaKai-2062/Ray-Tracing/main/res/git/RTIW.png)
