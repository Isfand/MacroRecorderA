#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <chrono>
#include <math.h>
#include <vector>
#include <thread>
#include "header.hpp"

using namespace std::chrono_literals;

//Function Prototype
void output();

//global vector
std::vector<int>iRead{};

void mouse_move(int x, int y)
{
	INPUT    Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = (x * (65535.0f / (double(GetSystemMetrics(SM_CXSCREEN)) - 1)));
	Input.mi.dy = (y * (65535.0f / (double(GetSystemMetrics(SM_CYSCREEN)) - 1)));
	SendInput(1, &Input, sizeof(INPUT));
}

void readfile()
{
	INPUT    Input = { 0 };
	ZeroMemory(&Input, sizeof(INPUT));

	int delay{}, xPos{}, yPos{}, mouseInput;

	std::string line;
	std::string d{}, x{}, y{}, mi{};
	std::ifstream readfile("macrofile.csv");

	while (getline(readfile, line))
	{
		std::stringstream ss(line);

		getline(ss, d, ',');
		getline(ss, x, ',');
		getline(ss, y, ',');
		getline(ss, mi,',');

		delay	   = stoi(d);
		xPos       = stoi(x);
		yPos       = stoi(y);
		mouseInput = stoi(mi);

		iRead.push_back(delay);
		iRead.push_back(xPos);
		iRead.push_back(yPos);
		iRead.push_back(mouseInput);
	}
	readfile.close();
	output();
}

void output()
{
	INPUT    Input = { 0 };
	ZeroMemory(&Input, sizeof(INPUT));

		int k = 0; // +4
		int j = 4; // +4

		for (int veclen = (iRead.size() / 4) - 1; veclen >= 0; veclen--, k += 4, j += 4)
		{
			for (int i{ k }, l{ 0 }; i < j; i++, l++)
			{
				// try using threads for each
				if (l == 0)
					Sleep(iRead.at(i));
				if (l == 1)
					mouse_move(iRead.at(i), iRead.at(i + 1));
				//if (l == 2)
				//	std::cout << iStore.at(i) << ',';
				if (l == 3)
					if (!iRead.at(i) == 0)
					{
						Input.mi.dwFlags = iRead.at(i);
						SendInput(1, &Input, sizeof(INPUT));
					}

				if (GetAsyncKeyState(VK_NUMPAD0))
					goto escape;

			}
			//k += 4
			//j += 4
		}
		escape:
		iRead.clear(); //Removes output Duplication
}