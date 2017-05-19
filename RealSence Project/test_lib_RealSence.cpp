#include <iostream>
#include <pxcsession.h>




void main()
{
	auto version = PXCSession_Create()->QueryVersion();

	std::cout << version.major << "." << version.minor << std::endl;
	system("pause");
}