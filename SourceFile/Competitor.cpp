#include"Competitor.h"

Competitor::Competitor()
{
	m_Name = "";
	for (int i = 0; i < 2; i++)
	{
		m_Score[i] = 0;
	}
}

Competitor::~Competitor() {}