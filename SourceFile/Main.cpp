#include"MainSystem.h"
#include<iostream>
#include<ctime>

int main()
{
	MainSystem sys;
	int cmd;
	srand(time(NULL));
	while (true)
	{
		sys.showMenu();
		cout << "Please input your choice!" << endl;
		cin >> cmd;
		switch (cmd)
		{
		case 0:
			sys.exitSystem();
			break;
		case 1:
			sys.start_Competition();
			break;
		case 2:
			sys.showRecord();
			break;
		case 3:
			sys.Clean();
			break;
		default:
			break;
		}
		system("cls");
	}
	system("pause");
	return 0;
}