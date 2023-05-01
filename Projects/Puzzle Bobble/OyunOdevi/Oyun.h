#pragma once
#include "Top.h"

class Oyun
{
public:
	sf::RenderWindow window;
	sf::RectangleShape ok;
	sf::RectangleShape karakterYeri;
	sf::RectangleShape arkaplan;
	sf::RectangleShape altArkaplan;
	sf::RectangleShape okTutucu;
	sf::Clock clock;
	sf::Clock clock1;
	std::vector<Top> toplar;
	std::vector<Top> top ;
	std::vector<Top> siradakiTop;
	std::vector<int> dusecekler;
	std::vector<int> silinecekler;
	float okYonu = 180;
	float dt = clock.getElapsedTime().asSeconds();
	bool topHareketEdiyor = false;
	//bool patliyor = false;	
	bool carpis = false;
	int karakterSayacu = 0; 
	int okTutucuSayacu = 0;

	sf::Sprite sprite;
	sf::Texture karakterKaplama[9];
	sf::Texture okTutucuKaplama[12];
	sf::Texture okKaplama[1];
	sf::Texture toplarKaplama[5];
	sf::Texture arkaPlanKaplama[2];
	sf::Texture patlamaKaplama[6][7];
	Oyun();
	void guncel();
private:
	
	void resimlerAl();
	void ayarlar();
	void toplarOlustur();
	void toplarCiz();
	sf::Color renkBelirle(int i);
	void olaylar();
	void topOlustur();
	void topCiz();
	void topMove();
	void carpismaTesti();
	void dusecekKomsular(int index);
	void dusecekleriSil();
	void tutulmaTesti();
	bool tutulacakKomsuVarMi(int index);
	void patlamaSureci();
	void dusmeSureci();
	void oyunBitisi();
};

