// ImageProxyImplementation.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

int main()
{
	ProxyImage images[5];
	int i;

	do {
		std::cout << "Press 0 to exit, 1 to 5 to select an image]: ";
		std::cin >> i;
		if (i > 0 && i <= 5)
			images[i - 1].draw();
	} while (i != 0);

	_getch();
	return 0;
}

