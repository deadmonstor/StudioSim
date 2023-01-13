#include "ScoreSystem.h"
#include<iostream>
#include<fstream>


ScoreSystem::ScoreSystem()
{

}

void ScoreSystem::SaveScore(std::string Username)
{

	//std::fstream newfile;
	std::fstream file;

	file.open("Score.txt", std::ios::app);
	if (file)
	{
		//std::cout << "File Exists";
		//file.open
		//file.open("Score.txt", std::ios::app);
		file << Username << "-" << currentScore << "\n";
		file.close();

	}
	else
	{
		//file.close();
		std::cout << "File Doesn't Exist";
		file.open("Score.txt", std::ios::out);
		file << Username << "-" << currentScore << "\n";
		file.close();
	}


}

void ScoreSystem::ReadScores()
{
	std::fstream newfile;
	newfile.open("Score.txt", std::ios::in);
	newfile.close();
}
//Sprites\\Zombie\\

