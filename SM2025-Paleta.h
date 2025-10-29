// funkcje do redukcji kolorów i tworzenia palet
#ifndef SM2025_PALETA_H_INCLUDED
#define SM2025_PALETA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
using namespace std;

#endif // SM2025_PALETA_H_INCLUDED


void narzucona();
void narysujPalete(int px,int py, SDL_Color pal8[]);
void NarzuconaS();
void narysujPaleteS(int px,int py,SDL_Color pal8s[]);

void paletaWykryta();
void czyscPalete();
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);
int dodajKolor(SDL_Color kolor);
int sprawdzKolor(SDL_Color kolor);

