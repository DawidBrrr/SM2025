#ifndef SM2025-KOLORY_H_INCLUDED
#define SM2025-KOLORY_H_INCLUDED

#include <SDL2/SDL.h>

struct YUV{
    Uint8 y;
    Uint8 u;
    Uint8 v;
};

struct YIQ{
    Uint8 y;
    Uint8 i;
    Uint8 q;
};

struct YCbCr{
    Uint8 y;
    Uint8 cb;
    Uint8 cr;
};

struct HSL{
    Uint8 h;
    Uint8 s;
    Uint8 l;
};

//Rodzaje palet barw
YUV RGBtoYUV(SDL_Color rgb);
SDL_Color YUVtoRGB(YUV yuv);
YIQ RGBtoYIQ(SDL_Color rgb);
SDL_Color YIQtoRGB(YIQ yiq);
YCbCr RGBtoYCbCr(SDL_Color rgb);
SDL_Color YCbCrtoRGB(YCbCr ycbcr);
HSL RGBtoHSL(SDL_Color rgb);
SDL_Color HSLtoRGB(HSL hsl) ;

//kodowanie 15 i 16bit RGB
void setRGB555(int xx,int yy, Uint8 r, Uint8 g,Uint8 b);
void setRGB555(int xx,int yy,Uint16 rgb555);
void setRGB565(int xx,int yy,Uint8 r,Uint8 g,Uint8 b);
void setRGB565(int xx,int yy,Uint16 rgb565);







#endif // SM2025-KOLORY_H_INCLUDED
