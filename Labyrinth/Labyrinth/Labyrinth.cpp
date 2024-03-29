#include "pch.h"
#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

int LeeAlg(pair <int, int> start, pair <int, int> finish, int** maze, deque <pair <int, int>> *path, int height, int width)
{
	int shiftX[4] = { 1, 0, -1, 0 };
	int shiftY[4] = { 0, 1, 0, -1 };
	int distance, x, y, direction;
	int minLen;
	bool stop;

	if (maze[start.first - 1][start.second - 1] == -1 || maze[finish.first - 1][finish.second - 1] == -1) 
		return -1;

	distance = 0;
	maze[start.first - 1][start.second - 1] = 0;

	do 
	{
		stop = true;

		for (y = 0; y < height; ++y)
			for (x = 0; x < width; ++x)
				if (maze[y][x] == distance)
				{
					for (direction = 0; direction < 4; ++direction)
					{
						int iy = y + shiftY[direction];
						int	ix = x + shiftX[direction];

						if (iy >= 0 && iy < height && ix >= 0 && ix < width && maze[iy][ix] == -2)
						{
							stop = false;
							maze[iy][ix] = distance + 1;
						}
					}
				}
		distance++;

	} while (!stop && maze[finish.first - 1][finish.second - 1] == -2);

	if (maze[finish.first - 1][finish.second - 1] == -2)
		return -1;

	minLen = maze[finish.first - 1][finish.second - 1];
	x = finish.second - 1;
	y = finish.first - 1;
	distance = minLen;

	while (distance > 0)
	{
		path->push_front(make_pair(y + 1, x + 1));
		distance--;

		for (direction = 0; direction < 4; ++direction)
		{
			int iy = y + shiftY[direction];
			int	ix = x + shiftX[direction];

			if (iy >= 0 && iy < height && ix >= 0 && ix < width && maze[iy][ix] == distance)
			{
				x = x + shiftX[direction];
				y = y + shiftY[direction];
				break;
			}
		}
	}

	path->push_front(start);

	return minLen;
}

int main()
{
	ifstream fin;
	fin.open("maze.in");
	ofstream fout; 
	fout.open("maze.out");

	int height;
	int width;
	pair <int, int> start;
	pair <int, int> finish;

	fin >> height >> width;
	fin >> start.first >> start.second;
	fin >> finish.first >> finish.second;

	int** maze = new int*[height];
	for (int i = 0; i < height; ++i)
		maze[i] = new int[width];

	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
		{
			int cond;
			fin >> cond;
			if (cond == 0)
				maze[i][j] = -1;
			else
				maze[i][j] = -2;
		}

	deque <pair <int, int>> *path = new deque <pair <int, int>>;

	int len;

	len = LeeAlg(start, finish, maze, path, height, width);

	fout << len;

	if (len != -1)
	{
		fout << "\n";
		for (pair <int, int> room : *path)
			fout << room.first << " " << room.second << "\n";
	}

	for (int i = 0; i < height; ++i)
		delete[] maze[i];
	delete[] maze;

	delete path;

	fin.close();
	fout.close();

	return 0;
}