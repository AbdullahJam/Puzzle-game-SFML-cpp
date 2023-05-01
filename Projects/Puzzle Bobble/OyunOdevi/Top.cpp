#include "Top.h"

Top::Top(float r,bool aktif , int index , int kat , int kattadakiIndex) : CircleShape(r)
{
	this->aktif = aktif;
	this->index = index;
	this->kat = kat;
	this->kattadakiIndex = kattadakiIndex;
	this->yon = 0;
	komsularBelirle();
}

void Top::komsularBelirle()
{
	int ustSolKomsu;
	int ustSagKomsu;
	int solKomsu;
	int sagKomsu;
	int altSolKomsu;
	int altSagKomsu;
	if (index != -1) {
		// sag ve sol komsular
		if (kattadakiIndex == 0) {
			solKomsu = -1;
		}
		else {
			solKomsu = index - 1;  
		}
		if ((kat % 2 == 0 && kattadakiIndex == kattaTopSayisi - 1) || (kat % 2 == 1 && kattadakiIndex == (kattaTopSayisi - 2))) {
			sagKomsu = -1;
		}
		else {
			sagKomsu = index + 1;
		}
		// ust sag ve sol komsular
		if (kat == 0) {
			ustSagKomsu = -2;
			ustSolKomsu = -2;
		}
		else if (kat % 2 == 0 && kattadakiIndex == 0) {
			ustSolKomsu = -1;
			ustSagKomsu = index - kattaTopSayisi + 1;
		}
		else if (kat % 2 == 0 && kattadakiIndex == (kattaTopSayisi -1)) {
			ustSagKomsu = -1;
			ustSolKomsu = index - kattaTopSayisi;
		}
		else {
			ustSagKomsu = index - kattaTopSayisi + 1;
			ustSolKomsu = index - kattaTopSayisi;
		}
		// alt sag ve sol komsular
		if (kat == (katSayisi -1)) {
			altSagKomsu = -1;
			altSolKomsu = -1;
		}
		else if (kat % 2 == 0 && kattadakiIndex == 0) {
			altSolKomsu = -1;
			altSagKomsu = index + kattaTopSayisi;
		}
		else if (kat % 2 == 0 && kattadakiIndex == (kattaTopSayisi -1)) {
			altSagKomsu = -1;
			altSolKomsu = index + kattaTopSayisi - 1;
		}
		else {
			altSagKomsu = index + kattaTopSayisi;
			altSolKomsu = index + kattaTopSayisi - 1;
		}
		/*if (ustSagKomsu != -1) komsular.push_back(ustSagKomsu);
		if (sagKomsu != -1)    komsular.push_back(sagKomsu);
		if (altSagKomsu != -1) komsular.push_back(altSagKomsu);
		if (ustSolKomsu != -1) komsular.push_back(ustSolKomsu);
		if (solKomsu != -1)    komsular.push_back(solKomsu);
		if (altSolKomsu != -1) komsular.push_back(altSolKomsu);	*/	

		komsular.push_back(ustSagKomsu);
		komsular.push_back(sagKomsu);
		komsular.push_back(altSagKomsu);
		komsular.push_back(ustSolKomsu);
		komsular.push_back(solKomsu);
		komsular.push_back(altSolKomsu);

	}
}

