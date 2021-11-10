#include <iostream>
#include <windows.h>
#include "header.hpp"

int main()
{
	while (1)
	{
		if (GetAsyncKeyState(VK_NUMPAD2))
		{
			readfile();
		}

		if (GetAsyncKeyState(VK_NUMPAD1))
		{
			writefile();
		}
		Sleep(1);
	}
}