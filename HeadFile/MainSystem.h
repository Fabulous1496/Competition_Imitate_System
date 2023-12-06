#pragma once
#include<iostream>
#include"Competitor.h"
#include<vector>
#include<map>
#include<string>
#include<algorithm>
#include<functional>
#include<numeric>
#include<windows.h>
#include<deque>
#include<fstream>
using namespace std;

class MainSystem
{
public:
	MainSystem();
	~MainSystem();
	void showMenu();
	void exitSystem();
	void Clean();

	//Control the competitors
	map<int, Competitor> index;
	vector<int> round1;
	vector<int> round2;
	vector<int> final;
	int round_counts;
	void createCompetitor();

	//Control the competition
	void start_Competition();
	void Draw();
	void Play();
	void Level_up();

	//Save datas
	void Save();

	//Read history
	bool isEmpty;
	map<int, vector<string>> records;
	void loadRecord();
	void showRecord();
};