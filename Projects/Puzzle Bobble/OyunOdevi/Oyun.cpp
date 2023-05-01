#include "Oyun.h"
#include <Windows.h>

Oyun::Oyun()
{
	window.create(sf::VideoMode(ekrenGenisligi, ekranBoyu), oyunIsmi);
	window.setFramerateLimit(60);
	resimlerAl();
	toplarOlustur();
	topOlustur();
	ayarlar();
	tutulmaTesti();
}



void Oyun::guncel()
{
	while (window.isOpen())
	{
		
		window.clear(arkaFon);

		window.draw(arkaplan);
		window.draw(altArkaplan);
		window.draw(okTutucu);
		window.draw(karakterYeri);
		window.draw(ok);
		olaylar();
		window.display();
		dt = clock.restart().asSeconds();
		
	}
}



void Oyun::resimlerAl()
{
	sf::Image resim = sf::Image();
	resim.loadFromFile("resimler/puzzle.png");
	resim.createMaskFromColor(sf::Color(147, 187, 236));
	if (!karakterKaplama[0].loadFromImage(resim , sf::IntRect(202, 2012, 28, 31))) { throw "error"; }
	for (int i = 0; i < 8; i++) {
		if (!karakterKaplama[i + 1].loadFromImage(resim, sf::IntRect(33 * i + 3, 2045, 28, 31))) { throw "error"; }
	}
	for (int i = 0; i < 12; i++) {
		if (!okTutucuKaplama[i].loadFromImage(resim, sf::IntRect(65 * i + 1, 1805, 63, 39 ))) { throw "error"; }
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			if (!patlamaKaplama[i][j].loadFromImage(resim, sf::IntRect(33 * j + 171, i * 33 + 1846, 31, 31))) { throw "error"; }
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			if (!patlamaKaplama[i+3][j].loadFromImage(resim, sf::IntRect(33 * j + 725, i * 33 + 1846, 31, 31))) { throw "error"; }
		}
	}
	if (!okKaplama[0].loadFromImage(resim, sf::IntRect(22, 1545, 21, 55))) { throw "error"; }
	if (!toplarKaplama[0].loadFromImage(resim, sf::IntRect(1, 1854, 16, 16))) { throw "error"; }
	if (!toplarKaplama[1].loadFromImage(resim, sf::IntRect(1, 1887, 16, 16))) { throw "error"; }
	if (!toplarKaplama[2].loadFromImage(resim, sf::IntRect(1, 1920, 16, 16))) { throw "error"; }
	if (!toplarKaplama[3].loadFromImage(resim, sf::IntRect(555, 1854, 16, 16))) { throw "error"; }
	if (!toplarKaplama[4].loadFromImage(resim, sf::IntRect(555, 1887, 16, 16))) { throw "error"; }
	if (!toplarKaplama[5].loadFromImage(resim, sf::IntRect(555, 1920, 15, 15))) { throw "error"; }
	if (!arkaPlanKaplama[0].loadFromImage(resim, sf::IntRect(1, 1086, 319, 223))) { throw "error"; }
	if (!arkaPlanKaplama[1].loadFromImage(resim, sf::IntRect(643, 1229, 223, 63))) { throw "error"; }

}

// ok olusturur ve ayarlari ayarlar
void Oyun::ayarlar()
{
	ok = sf::RectangleShape(sf::Vector2f(40.f, 120.f)); 
	
	ok.setPosition((ekrenGenisligi / 2) +3 , ekranBoyu -60);
	ok.setOrigin(20.f, 70.f);
	ok.setScale(1, -1);
	ok.rotate(okYonu);
	
	//ok.setFillColor(sf::Color::Black);
	ok.setTexture(&okKaplama[0]);
	karakterYeri = sf::RectangleShape(sf::Vector2f(70.f, 70.f));
	karakterYeri.setPosition(340, 720);
	karakterYeri.setFillColor(sf::Color::White);
	arkaplan = sf::RectangleShape(sf::Vector2f(ekrenGenisligi, ekranBoyu - 100));
	arkaplan.setTexture(&arkaPlanKaplama[0]);
	altArkaplan = sf::RectangleShape(sf::Vector2f(ekrenGenisligi,100 ));
	altArkaplan.setPosition(0, 700);
	altArkaplan.setFillColor(sf::Color::White);
	altArkaplan.setTexture(&arkaPlanKaplama[1]);
	okTutucu = sf::RectangleShape(sf::Vector2f(150, 80));
	okTutucu.setPosition(225, 710);
	
}

// olaylara bakar
void Oyun::olaylar()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && okYonu > 100)
	{
		okYonu -= 2.5f;	
		okTutucuSayacu++;
		if (karakterSayacu % 8 == 0)
		{
			karakterSayacu = 0;
		}
		if (okTutucuSayacu % 12 == 0)
		{
			okTutucuSayacu = 0;
		}
		karakterSayacu++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && okYonu < 260)
	{
		okYonu += 2.5f;
		okTutucuSayacu--;
		if (karakterSayacu == 0)
		{
			karakterSayacu = 9;
		}
		if (okTutucuSayacu == -1)
		{
			okTutucuSayacu = 11;
		}
		karakterSayacu--;
	}
	else
	{
		karakterSayacu = 0;
	}
	ok.setRotation(okYonu);
	karakterYeri.setTexture(&karakterKaplama[karakterSayacu]);
	okTutucu.setTexture(&okTutucuKaplama[okTutucuSayacu]);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !topHareketEdiyor)
	{
		topHareketEdiyor = true;
		top.push_back(siradakiTop[0]);
		siradakiTop.pop_back();
		topOlustur();
		top[0].yon = okYonu;
	}
	if (topHareketEdiyor == true)
	{
		topMove();
	}
	toplarCiz();
	topCiz();
	patlamaSureci();
	dusmeSureci();
	oyunBitisi();

}


// ilk basta rastgele top olusturmak
void Oyun::toplarOlustur()
{
	srand(time(NULL));
	for (int kat = 0; kat < katSayisi; kat++)
	{
		if (kat % 2 == 0)
		{
			for (int i = 0; i < kattaTopSayisi; i++)
			{
				Top top(yariCapi, true, i + ((kattaTopSayisi * kat) - (kat / 2)), kat, i);
				top.setPosition(yariCapi * i * 2, kat * 1.75 * yariCapi);
				top.renkIndexi = (rand() % (renkSayisi + 1)) - 1;	
				//top.setFillColor(renkBelirle(rand() % (renkSayisi + 1)));
				//top.setTexture(&toplarKaplama[rand() % (renkSayisi + 1)]);
				if (top.renkIndexi == -1 || kat > aktifKatSayisi)
				{
					top.aktif = false;
				}
				else {
					top.setTexture(&toplarKaplama[top.renkIndexi]);
				}
				toplar.push_back(top);
			}
		}
		else {
			for (int i = 0; i < kattaTopSayisi - 1; i++)
			{
				Top top(yariCapi, true, i + ((kattaTopSayisi *kat) - ((kat-1)/2)), kat , i);
				top.setPosition((yariCapi * i * 2) + yariCapi, kat * 1.75 * yariCapi);
				top.renkIndexi = (rand() % (renkSayisi + 1)) - 1;
				//top.setFillColor(renkBelirle(rand() % (renkSayisi + 1)));
				//top.setTexture(&toplarKaplama[rand() % (renkSayisi + 1)]);
				if (top.renkIndexi == -1 || kat > aktifKatSayisi)
				{
					top.aktif = false;
				}
				else {
					top.setTexture(&toplarKaplama[top.renkIndexi]);
				}
				toplar.push_back(top);
			}
		}

	}
}


// olusturdugu toplar cizer
void Oyun::toplarCiz()
{
	for (Top top : toplar)
	{
		//std::cout << top.index << std::endl;
		if(top.aktif) window.draw(top);
	}
}

// rastgele top renki belirlenir
sf::Color Oyun::renkBelirle(int i)
{
	switch (i)
	{
	case 0:
		return arkaFon;
	case 1:
		return sf::Color::Red;
	case 2:
		return sf::Color::Blue;
	case 3:
		return sf::Color::Green;
	case 4:
		return sf::Color::Yellow;
	case 5:
		return sf::Color::Magenta;
	default:
		return arkaFon;
	}
}


//vurulucak top olusturur
void Oyun::topOlustur()
{
	Top daire(yariCapi, true, -1, 50, 50);
	daire.renkIndexi = (rand() % (renkSayisi )) ;
	daire.setTexture(&toplarKaplama[daire.renkIndexi]);
	//daire.setFillColor(renkBelirle(rand() % (renkSayisi)+1));
	daire.setPosition((ekrenGenisligi / 2) - yariCapi, ekranBoyu - (yariCapi) - 50);
	siradakiTop.push_back(daire);
}

// vurulacak top cizelir
void Oyun::topCiz()
{
	for (Top top : siradakiTop)
	{
		window.draw(top);
	}
	for (Top top : top)
	{
		window.draw(top);
	}
}

// vurulacak top hareket etterir
void Oyun::topMove()
{
	if (top[0].getPosition().x < 0 || top[0].getPosition().x >= ekrenGenisligi - yariCapi*2 ) {
		top[0].xYonu *= -1;
	}
	if (top.size() > 0) {
		top[0].move((-sin(top[0].yon * 3.14159 / 180) * top[0].xYonu)*(dt* speed), (cos(top[0].yon * 3.14159 / 180))* (dt * speed));
	}
	carpismaTesti();
	if (carpis)
	{
		top.pop_back();
		topHareketEdiyor = false;
		carpis = false;
	}
}

// vurulacak topu hareket ederken carpisma testi yapilir
void Oyun::carpismaTesti()
{
	for (Top top1 : toplar)
	{
		float x1 = top1.getPosition().x;
		float y1 = top1.getPosition().y;
		float x2 = top[0].getPosition().x;
		float y2 = top[0].getPosition().y;
		float eskiMesafe = yariCapi * 2 + 1;
		float mesafe;
		int index = -1 ;
		if ((sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)) <= yariCapi * 2 && top1.aktif && !carpis)||(top[0].getPosition().y < 0 && !carpis))
		{
			carpis = true;
			for (Top top2 : toplar) {
				if (!top2.aktif) {
					mesafe = sqrt(pow((top2.getPosition().x - x2), 2) + pow((top2.getPosition().y - y2), 2));
					if (mesafe < eskiMesafe) {
						index = top2.index;
						eskiMesafe = mesafe;	
					}
				}
			}
			if (index == -1) {
				window.close();
				std::cout << std::endl << std::endl << std::endl << "     OYUNU KAYPETTINIZ  " << std::endl << std::endl << std::endl;
			}
			else {
				toplar[index].aktif = true;
				toplar[index].setTexture(&toplarKaplama[top[0].renkIndexi]);
				toplar[index].renkIndexi = top[0].renkIndexi;
				//toplar[index].setFillColor(top[0].getFillColor());

				dusecekKomsular(index);
				dusecekleriSil();
				tutulmaTesti();

			}
			if (carpis) break;
		}
		
	}
}

// carpismada benzer renkler belirlemek
void Oyun::dusecekKomsular(int index)
{
	for (int komsu : toplar[index].komsular) {
		if ( komsu >=0 && toplar[komsu].renkIndexi == toplar[index].renkIndexi && toplar[komsu].aktif) {
			if (std::find(dusecekler.begin(), dusecekler.end(), komsu) != dusecekler.end()) {
			}
			else {
				dusecekler.push_back(komsu);
				dusecekKomsular(komsu);
			}
		}
	}
}

// carpismadan sonra benzer renkleri silme
void Oyun::dusecekleriSil()
{
	if (dusecekler.size() >= 3) {
		for (int komsu : dusecekler) {
			//toplar[komsu].aktif = false;
			//toplar[komsu].renkIndexi = -1;
			toplar[komsu].patlamaSayaci = 1;
		}
	}
	dusecekler.clear();
}

// butun toplarda gez
void Oyun::tutulmaTesti()
{
	for (Top top1 : toplar) {
		if (top1.aktif) {		
			if (tutulacakKomsuVarMi(top1.index)) {
				silinecekler.clear();
			}
			else {
				for (int index : silinecekler) {
					//toplar[index].aktif = false;
					//toplar[index].renkIndexi = -1;
					toplar[index].dusmeSayaci = 1;
				}
				silinecekler.clear();
			}
		}
	}
}

// topun komsulardan indexi -1 bir komsu bulursa bu top dusmeyecek demek
bool Oyun::tutulacakKomsuVarMi(int index)
{
	if (std::find(toplar[index].komsular.begin(), toplar[index].komsular.end(), -2) != toplar[index].komsular.end()) {
		return true;
	}
	else {
		bool varmi = std::find(silinecekler.begin(), silinecekler.end(), index) != silinecekler.end();
		if (!varmi) {
			silinecekler.push_back(index);		
			for (int komsu : toplar[index].komsular) {		
				if (komsu >= 0 && toplar[komsu].aktif) {
					if (tutulacakKomsuVarMi(komsu)) {
						//std::cout << index << " ";
						return true;
					
					}		
				}
			}
		}
	}
	return false;
}

// patlama animasyonlari
void Oyun::patlamaSureci()
{
	for (Top &top1 : toplar) {
		if (top1.patlamaSayaci >= 7) {
			top1.patlamaSayaci = 0;
			top1.aktif = false;
			top1.renkIndexi = -1;
			tutulmaTesti();
		}
		else if (top1.patlamaSayaci >= 1) {
			top1.setTexture(&patlamaKaplama[top1.renkIndexi][top1.patlamaSayaci-1]);
			top1.patlamaSayaci++;
		}

	}
}

// dusme animasyonlari
void Oyun::dusmeSureci()
{
	for (Top& top1 : toplar) {
		if (top1.dusmeSayaci >= 6) {
			top1.dusmeSayaci = 0;
			top1.aktif = false;
			top1.renkIndexi = -1;
			top1.setPosition(top1.getPosition().x, top1.getPosition().y - 25);
			top1.setFillColor(sf::Color(top1.getFillColor().r, top1.getFillColor().g, top1.getFillColor().b, 255 ));
		}
		else if (top1.dusmeSayaci >= 1) {
			top1.setPosition(top1.getPosition().x, top1.getPosition().y + 5);
			top1.setFillColor(sf::Color(top1.getFillColor().r , top1.getFillColor().g , top1.getFillColor().b , 255 - (top1.dusmeSayaci * (250/6)) ));
			top1.dusmeSayaci++;
		}

	}
}

// sahnede hic bir top kalmamis ise
void Oyun::oyunBitisi()
{
	bool bittiMi = true;
	for (Top top1 : toplar) {
		if (top1.aktif) {
			bittiMi = false;
			break;
		}
	}
	if (bittiMi) {
		window.close();
		std::cout << std::endl << std::endl << std::endl << "     OYUNU KAZANDINIZ  " << std::endl << std::endl << std::endl;
	}
}

