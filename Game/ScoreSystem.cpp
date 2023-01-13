#include "ScoreSystem.h"
#include<iostream>
#include<fstream>
#include<string>

ScoreSystem::ScoreSystem()
{

}

void ScoreSystem::SaveScore()
{

	try
	{
		std::ofstream fw("Game\\", std::ofstream::out);

		if (fw.is_open())
		{
			fw << "This is writing to a file";
			fw.close();
		}
		else std::cout << "Problem with Opening file";
	}
	catch(const char& msg)
	{
		std::cerr << msg << std::endl;
	}
	std::cout << "\nDone";
	std::getchar();

}
//Sprites\\Zombie\\

