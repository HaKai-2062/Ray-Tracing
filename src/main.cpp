#include <iostream>
#include "application.hpp"

int main()
{
	Application& application = Application::GetInstance();
	application.MainLoop();
}