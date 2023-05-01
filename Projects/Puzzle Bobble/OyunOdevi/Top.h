#pragma once
#include "temeller.h"

 class Top : public sf::CircleShape
{
public:
	bool aktif;
	Top(float r,bool aktiv, int index, int kat , int kattadakiIndex);
	std::vector<int> komsular;
	float yon;
	float xYonu = 1;
	int index;
	int kat;
	int kattadakiIndex;
	int renkIndexi;
	int patlamaSayaci = 0;
	int dusmeSayaci = 0;
private:
	void komsularBelirle();
};

