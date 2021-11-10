#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <chrono>
#include <math.h>
#include <vector>
#include "header.hpp"

using namespace std::chrono_literals;

void input();
std::vector<int> iWrite{};

void writefile()
{
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
			iWrite.push_back(delay);
			iWrite.push_back(pointer.x);
			iWrite.push_back(pointer.y);
			iWrite.push_back(mouseInput);

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
	input();
}

void input()
{
	std::ofstream writefile;
	writefile.open("macrofile.csv");

	int k = 0; // +4
	int j = 4; // +4

	for (int veclen = (iWrite.size() / 4) - 1; veclen >= 0; veclen--, k += 4, j += 4)
	{
		for (int i{ k }, l{ 0 }; i < j; i++, l++)
		{
			if (l == 0)
				writefile << iWrite.at(i) << ',';
			if (l == 1)
				writefile << iWrite.at(i) << ',';
			if (l == 2)
				writefile << iWrite.at(i) << ',';
			if (l == 3)
				writefile << iWrite.at(i) << '\n';

			//if (GetAsyncKeyState(VK_NUMPAD0))
			//	goto escape;

		}
		//k += 4
		//j += 4
	}
	//escape:
	iWrite.clear(); //Removes output Duplication
	writefile.close();
}