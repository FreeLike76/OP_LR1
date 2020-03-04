// OP_LR1
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Team
{
	string name;
	int score;
public:
	string getName()
	{
		return this->name;
	}
	string setName(string a)
	{
		this->name = a;
	}
	int getScore()
	{
		return this->score;
	}
	int setScore(int a)
	{
		this->score = a;
	}
	int addScore(int a)
	{
		this->score += a;
	}
	Team()
	{
		this->name = "Unknown";
		this->score = 0;
	}
};

int main()
{

}