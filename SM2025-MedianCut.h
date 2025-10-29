// metody do algorytmu kwantyzacji (MedianCut)
#ifndef SM2025_MEDIANCUT_H_INCLUDED
#define SM2025_MEDIANCUT_H_INCLUDED

#include <SDL2/SDL.h>
#include <iostream>

#endif // SM2025_MEDIANCUT_H_INCLUDED



void paletaMedianCutBW();
void MedianCutBW(int start, int koniec, int iteracja);
void sortujKubelekBW(int start, int koniec);
int znajdzSasiadaBW(Uint8 wartosc);
int znajdzSasiada(SDL_Color kolor);
void narysujPalete3b(int px, int py, SDL_Color pal3b[]);
void paletaMedianCut();
void MedianCut(int start, int koniec, int iteracja);
Uint8 najwiekszaRoznica(int start, int koniec);
void sortujKubelek(int start, int koniec, Uint8 sortowanie);

