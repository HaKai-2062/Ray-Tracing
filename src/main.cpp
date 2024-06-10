#include <iostream>
#include "application.hpp"

int main()
{
	Application& application = Application::CreateInstance("RayTracing", 1280, 720);
	application.MainLoop();
}