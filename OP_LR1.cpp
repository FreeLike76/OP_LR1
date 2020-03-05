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
	for (int i = 1; i < filenum; i++)
	{
		combineTeam(All[0], All[i], sizes, 0, i);
	}
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

void combineTeam(Team*& Main,Team* Second,int*sizes,int index1,int index2)
{
	int newsize = sizes[index1] + sizes[index2];
	Team* Newmain = new Team[newsize];
	for (int i = 0; i < sizes[index1]; i++)
	{
		Newmain[i].setName(Main[i].getName());
		Newmain[i].setScore(Main[i].getScore());
	}
	for (int i = sizes[index1]; i < newsize; i++)
	{
		Newmain[i].setName(Second[i].getName());
		Newmain[i].setScore(Second[i].getScore());
	}
	sizes[index1] = newsize;
	delete[]Main;
	Main = Newmain;
}