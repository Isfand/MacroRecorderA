#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <chrono>
#include <math.h>
//Could try to store everything into a vector first and then output everything into a file from the vector similar to readfile
void writefile()
{
	std::ofstream writefile;
	writefile.open("macrofile.csv");

	POINT pointer;
	int delay = 1;

	bool kf_LMB{ true };
	bool kf_RMB{ true };
	bool kf_MMB{ true };

	int mouseInput{ 0 };

	while (!GetAsyncKeyState(VK_NUMPAD0))
	{
		if (GetCursorPos(&pointer))
		{
			writefile << delay << "," << pointer.x << "," << pointer.y << "," << mouseInput << "\n";
			//std::cout << delay << " " << pointer.x << " " << pointer.y << " " << mouseInput << "\n";

			Sleep(delay);
			mouseInput = 0;

			if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
			{
				if (kf_LMB == true)
				{
					mouseInput = 0x0002;
					kf_LMB = false;
				}
			}
			else if ((!GetAsyncKeyState(VK_LBUTTON)))
			{
				if (kf_LMB == false)
				{
					mouseInput = 0x0004;
					kf_LMB = true;
				}
			}

			if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0)
			{
				if (kf_RMB == true)
				{
					mouseInput = 0x0008;
					kf_RMB = false;
				}

			}
			else if ((!GetAsyncKeyState(VK_RBUTTON)))
			{
				if (kf_RMB == false)
				{
					mouseInput = 0x0010;
					kf_RMB = true;
				}
			}

			if ((GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0)
			{
				if (kf_MMB == true)
				{
					mouseInput = 0x0020;
					kf_MMB = false;
				}

			}
			else if ((!GetAsyncKeyState(VK_MBUTTON)))
			{
				if (kf_MMB == false)
				{
					mouseInput = 0x0040;
					kf_MMB = true;
				}
			}

		}
	}
	writefile.close();
}