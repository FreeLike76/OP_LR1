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
	cout << All[0][1].getName() << endl << All[0][2].getName() << All[0][2].getScore() << endl;;
	cout << All[1][2].getName() << All[1][2].getScore();
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
		return thisfileteams;
	}
}