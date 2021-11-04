#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
namespace ryan
{
	shader loadShader(const char* vertPath, const char* fragPath)
	{
		string line;
		ifstream vCode(vertPath);
		string vCodeS;
		ifstream fCode(fragPath);
		string fCodeS;
		cout << "\nLoading vertex shader" << vertPath << "\n";
		if (vCode.is_open())
		{
			while (getline(vCode, line))
			{
				cout << line << "\n";
				vCodeS.append(line + "\n");
			}
		}

		cout << "\nLoading fragment shader " << fragPath << "\n";
		if (fCode.is_open())
		{
			while (getline(fCode, line))
			{
				cout << line << "\n";
				fCodeS.append(line + "\n");
			}
		}

		return makeShader(vCodeS.c_str(),fCodeS.c_str());
	}
}