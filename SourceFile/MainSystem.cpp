#include"MainSystem.h"

MainSystem::MainSystem()
{
	round_counts = 1;
	index.clear();
	round1.clear();
	round2.clear();
	final.clear();
	records.clear();
	this->createCompetitor();
	this->loadRecord();
}

MainSystem::~MainSystem(){}

void MainSystem::showMenu()
{
	cout << "-----------------------------------" << endl;
	cout << "-----------------------------------" << endl;
	cout << "----Welcome to the competition!----" << endl;
	cout << "-----1.Start a new competition-----" << endl;
	cout << "-------2. Search the history-------" << endl;
	cout << "---------3. Clean all data---------" << endl;
	cout << "--------------0. Exit--------------" << endl;
	cout << "-----------------------------------" << endl;
	cout << "-----------------------------------" << endl;
	cout << endl;
}

void MainSystem::exitSystem()
{
	cout << "See you next time!" << endl;
	system("pause");
	exit(0);
}

void MainSystem::createCompetitor()
{
	string name_suffix = "ABCDEFGHIJKL";
	for (int i = 0; i <name_suffix.size(); i++)
	{
		Competitor cpt;
		string name = "Competitor ";
		name += name_suffix[i];
		cpt.m_Name = name;
		this->round1.push_back(i + 100001);
		this->index.insert(make_pair(i + 100001, cpt));
	}
}

void MainSystem::start_Competition()
{
	//Round 1
	//Draw,Game,showResult
	this->Draw();
	this->Play();
	this->Level_up();
	this->round_counts+=1;
	//Round 2
	//Draw,Game,showResult
	this->Draw();
	this->Play();
	this->Level_up();
	//Save datas
	this->Save();
	//Reset competition
	round_counts = 1;
	index.clear();
	round1.clear();
	round2.clear();
	final.clear();
	records.clear();
	this->createCompetitor();
	this->loadRecord();

	cout << "The Competition is Over!" << endl;
	system("pause");
	system("cls");
}

void MainSystem::Draw()
{
	Sleep(1000);
	cout << "Round " << this->round_counts << " " << endl
		<< "Players are drawing......" << endl;
	Sleep(2000);
	cout << "The Results: " << endl;
	if (this->round_counts == 1)
	{
		random_shuffle(round1.begin(), round1.end());
		for (vector<int>::iterator it = round1.begin(); it != round1.end(); it++)
		{
			cout << *it << endl;
		}
		cout << endl;
	}
	else
	{
		random_shuffle(round2.begin(), round2.end());
		for (vector<int>::iterator it = round2.begin(); it != round2.end(); it++)
		{
			cout << *it << endl;
		}
		cout << endl;
	}
	cout << "----------------------------------" << endl;
	system("pause");
}

void MainSystem::Play()
{
	//Set Groups
	multimap<double, int, greater<double>> groupScore;
	int num = 0;

	cout << "Round " << this->round_counts << " ......" << endl;
	Sleep(1500);
	cout << "Fight!" << endl;
	Sleep(1500);
	vector<int> temp;
	switch (this->round_counts)
	{
	case 1:
		temp = this->round1;
		break;
	case 2:
		temp = this->round2;
		break;
	default:
		break;
	}

	//Set Scores
	for (vector<int>::iterator it = temp.begin(); it != temp.end(); it++)
	{
		num++;
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back(), d.pop_front();
		double avg = accumulate(d.begin(), d.end(), 0.0f)/(double)d.size();
		this->index[*it].m_Score[this->round_counts-1] = avg;
		//(this for test)cout << "Player ID: " << *it << "\tPlayer Name: " << index[*it].m_Name << "\tScore: " << avg << endl;
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "Group" << num / 6 << " 's rank:" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "Player ID: " << it->second 
					<< "\tPlayer Name: " << this->index[it->second].m_Name 
					<< "\tScore: " << this->index[it->second].m_Score[this->round_counts-1] 
					<< endl;
			}
			cout << endl;
			//Get the 1st,2nd and 3rd of each group,or show the final results
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++)
			{
				if (this->round_counts == 1)
				{
					this->round2.push_back(it->second);
				}
				else
				{
					this->final.push_back(it->second);
				}
			}
			groupScore.clear();
		}
	}
	cout << endl;
	cout << "Round" << this->round_counts << " is OVER!" << endl;
	cout << "----------------------------------" << endl;
	system("pause");
}

void MainSystem::Level_up()
{
	vector<int> temp;
	if (this->round_counts == 1)
	{
		cout << "These Competitors can advance into Round 2 :" << endl;
		temp = round2;
	}
	else
	{
		cout << "The Winners Are: " << endl;
		temp = final;
	}
	for (vector<int>::iterator it = temp.begin(); it != temp.end(); it++)
	{
		cout << "Player ID: " << *it
			<< "\tPlayer Name: " << this->index[*it].m_Name
			<< "\tScore: " << this->index[*it].m_Score[this->round_counts - 1]
			<< endl;
	}
	system("pause");
	system("cls");
	this->showMenu();
}

void MainSystem::Save()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = final.begin(); it != final.end(); it++)
	{
		ofs << *it << "," << index[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	this->isEmpty = false;
}

void MainSystem::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		isEmpty = true;
		ifs.close();
		cout << "No Records!" << endl;
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		isEmpty = true;
		ifs.close();
		cout << "No Records!" << endl;
		return;
	}
	isEmpty = false;
	ifs.putback(ch);

	string data;
	int ani = 1;
	while (ifs >> data)
	{
		//use ',' to find and seperate each data
		vector<string>v;
		int pos = -1;
		int start = 0;
		while (1)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->records.insert(make_pair(ani, v));
		ani++;
	}
	ifs.close();
}

void MainSystem::showRecord()
{
	for (map<int,vector<string>>::iterator it=records.begin();it!=records.end();it++)
	{
		cout <<it->first << "   " << "ID:" << it->second[0] << "  "
			<< " Score: " << it->second[1] << endl;
		cout << it->first << "   " << "ID:" << it->second[2] << "  "
			<< " Score: " << it->second[3] << endl;
		cout << it->first << "   " << "ID:" << it->second[4] << "  "
			<< " Score: " << it->second[5] << endl;
		cout << "----------------------------------" << endl;
	}
	system("pause");
	system("cls");
}

void MainSystem::Clean()
{
	cout << "Are you sure?" << endl;
	cout << "press 1 to continue or 2 to return" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		round_counts = 1;
		index.clear();
		round1.clear();
		round2.clear();
		final.clear();
		records.clear();
		this->createCompetitor();
		this->loadRecord();
		cout << "Complete!" << endl;
	}
	system("pause");
	system("cls");
}