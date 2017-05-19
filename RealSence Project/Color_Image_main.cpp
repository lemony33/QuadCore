#include <iostream>
#include <pxcsession.h>

#include "RealSenseApp.h"


void main()
{
	try
	{
		RealSenseApp app;
		app.initialize();
		app.run();
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}


