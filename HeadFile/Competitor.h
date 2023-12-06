#pragma once
#include<iostream>
#include<string>
using namespace std;

class Competitor
{
public:
	Competitor();
	string m_Name;
	double m_Score[2];
	~Competitor();
};