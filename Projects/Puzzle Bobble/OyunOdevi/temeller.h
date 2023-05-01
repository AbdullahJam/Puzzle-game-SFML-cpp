#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdlib.h>
#include <time.h>

const sf::Color arkaFon = sf::Color::Black;
constexpr int ekrenGenisligi = 600;
constexpr int ekranBoyu = 800;
const std::string oyunIsmi = "Puzzle Bobble";
constexpr int speed = 1200;

constexpr int kattaTopSayisi = 12;
constexpr int renkSayisi = 5;
constexpr float yariCapi = ekrenGenisligi / kattaTopSayisi / 2;
constexpr int katSayisi = ekranBoyu /(yariCapi *2) ;
constexpr int aktifKatSayisi = katSayisi /2 -1;


