// podstawowe funkcje
#ifndef SM2025_FUNKCJE_H_INCLUDED
#define SM2025_FUNKCJE_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();
void Funkcja6();
void Funkcja7();
void Funkcja8();
void Funkcja9();

void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel(int x, int y);
void czyscEkran(Uint8 R, Uint8 G, Uint8 B);
void ladujBMP(char const* nazwa, int x, int y);

//palety
void testujYUV();
void testujYIQ();
void testujYCbCr();
void testujHSL();

//Konwersja 15 i 16 bit RGB
void setRGB555(int xx,int yy, Uint8 r, Uint8 g,Uint8 b);
void setRGB555(int xx,int yy,Uint16 rgb555);
void setRGB565(int xx,int yy,Uint8 r,Uint8 g,Uint8 b);
void setRGB565(int xx,int yy,Uint16 rgb565);

SDL_Color getRGB555(int xx,int yy);
Uint16 getRGB555_(int xx,int yy);
SDL_Color getRGB565(int xx,int yy);
Uint16 getRGB565_(int xx,int yy);

SDL_Color getRGB555D(int xx,int yy);
Uint16 getRGB555D_(int xx,int yy);
SDL_Color getRGB565D(int xx,int yy);
Uint16 getRGB565D_(int xx,int yy);

void testujRGBkonwersje();
void testujRGBkonwersjeDithering();


#endif // SM2025_FUNKCJE_H_INCLUDED
