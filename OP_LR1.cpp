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
	void setName(string a)
	{
		this->name = a;
	}
	int getScore()
	{
		return this->score;
	}
	void setScore(int a)
	{
		this->score = a;
	}
	void addScore(int a)
	{
		this->score += a;
	}
	Team()
	{
		this->name = "Unknown";
		this->score = 0;
	}
};

Team* readfile(string path, int* sizes, int iter);
void combineTeam(Team* Main, Team** All, int* sizes, int filenum);
void sortTeams(Team* Main, int size);

int main()
{
	string path;
	cout << "Enter number of files: ";
	int filenum;
	cin >> filenum;
	int* sizes = new int[filenum];
	Team** All = new Team * [filenum];
	for (int i = 0; i < filenum; i++)
	{
		cout << "Enter the name of " << i + 1 << " file: ";
		cin >> path;
		All[i] = readfile(path,sizes,i);
	}
	int allteams=0;
	for (int i = 0; i < filenum; i++)
	{
		allteams += sizes[i];
	}
	Team* Main = new Team[allteams];
	combineTeam(Main, All, sizes, filenum);
	delete[] sizes;
	for (int i = 0; i < filenum; i++)
	{
		delete[] All[i];
	}
	delete[] All;
	sortTeams(Main, allteams);
}

Team* readfile(string path,int* sizes,int iter)
{
	ifstream file;
	file.open(path);
	if (!file.is_open())
		cout << "Cannot open file!";
	else
	{
		char ch;
		int a, b,size;
		file >> size;
		file.get(ch);
		sizes[iter] = size;
		Team* thisfileteams = new Team[size];
		for (int i = 0; i < size; i++)
		{
			file.get(ch);
			string fullname;
			while (ch != ',')
			{
				fullname = fullname + ch;
				file.get(ch);
			}
			thisfileteams[i].setName(fullname);
			while (ch != '\n'&&!file.eof())
			{
				file >> a;
				file.get(ch);
				file >> b;
				if (a > b)
					thisfileteams[i].addScore(3);
				else if (a == b)
					thisfileteams[i].addScore(1);
				file.get(ch);
			}

		}
		file.close();
		return thisfileteams;
	}
	return nullptr;
}

void combineTeam(Team* Main,Team** All,int*sizes,int filenum)
{
	int where=0;
	for (int i = 0; i < filenum; i++)
	{
		for (int j = 0; j <sizes[i]; j++)
		{
			Main[j+where].setName(All[i][j].getName());
			Main[j+where].setScore(All[i][j].getScore());
		}
		where += sizes[i];
	}
}

void sortTeams(Team* Main,int size)
{
	bool didChange;
	Team temp;
	do
	{
		didChange = false;
		for (int i = 1; i < size; i++)
		{
			if(Main[i-1].getScore()<Main[i].getScore())
			{
				didChange = true;
				temp.setName(Main[i - 1].getName());
				temp.setScore(Main[i - 1].getScore());
				Main[i - 1].setName(Main[i].getName());
				Main[i - 1].setScore(Main[i].getScore());
				Main[i].setName(temp.getName());
				Main[i].setScore(temp.getScore());
			}
		}
	} while (didChange);
}