// podstawowe funkcje
#ifndef SM2025_FUNKCJE_H_INCLUDED
#define SM2025_FUNKCJE_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
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

void podprobkujYUV_420();
void podprobkujYCbCr_420();
void podprobkujYIQ_420();
void podprobkujHSL_L_420();

//Filtry predykcyjne

void PokaFilter(int func,int bpp,int color_type);
void KodF1Sub(const uint8_t *raw, uint8_t *out, int width, int height, int bpp);
void DekodF1Sub(const uint8_t *in, uint8_t *out, int width, int height, int bpp);
void KodF2Up(const uint8_t *raw, uint8_t *out, int width, int height, int bpp);
void DekodF2Up(const uint8_t *in, uint8_t *out, int width, int height, int bpp);
void KodF3AVG(const uint8_t *raw, uint8_t *out, int width, int height, int bpp);
void DekodF3AVG(const uint8_t *in, uint8_t *out, int width, int height, int bpp);
static inline int paeth_predictor(int a, int b, int c);
void KodF4Paeth(const uint8_t *raw, uint8_t *out, int width, int height, int bpp);
void DekodF4Paeth(const uint8_t *in, uint8_t *out, int width, int height, int bpp);






#endif // SM2025_FUNKCJE_H_INCLUDED
