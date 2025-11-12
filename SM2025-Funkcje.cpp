// podstawowe funkcje
#include "SM2025-Funkcje.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Paleta.h"
#include "SM2025-MedianCut.h"
#include "SM2025-Pliki.h"
#include "SM2025-kolory.h"

#define SUBW(sw) (((sw) + 1) / 2)
#define SUBH(sh) (((sh) + 1) / 2)

static const int bayer4x4[4][4] = {
    {  6,  14,  8, 16 },
    { 10,  2, 12,  4 },
    {  7, 15,  5,  13},
    { 11,  3, 9,  1 }
};


void Funkcja1() {

    //narzucona();
    //podprobkujYUV_420();
    PokaFilter(1,2,2);

    SDL_UpdateWindowSurface(window);
}

void Funkcja2() {

    //NarzuconaS();
    //podprobkujYIQ_420();
    PokaFilter(2,2,2);

    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {

    //paletaWykryta();
    //podprobkujYCbCr_420();
    PokaFilter(3,2,2);

    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {

    //paletaMedianCut();
    //podprobkujHSL_L_420();
    PokaFilter(1,3,1);

    SDL_UpdateWindowSurface(window);
}

void Funkcja5() {

    //paletaMedianCutBW();
    PokaFilter(4,3,1);

    SDL_UpdateWindowSurface(window);
}

void Funkcja6() {

    testujYUV();

    SDL_UpdateWindowSurface(window);
}

void Funkcja7() {

    testujYIQ();

    SDL_UpdateWindowSurface(window);
}

void Funkcja8() {

    //testujYCbCr();
    testujRGBkonwersje();

    SDL_UpdateWindowSurface(window);
}

void Funkcja9() {

    //testujHSL();
    testujRGBkonwersjeDithering();

    SDL_UpdateWindowSurface(window);
}



void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p1 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2) * bpp;
    Uint8 *p2 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2) * bpp;
    Uint8 *p3 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2+1) * bpp;
    Uint8 *p4 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2+1) * bpp;

    /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p1 = pixel;
            *p2 = pixel;
            *p3 = pixel;
            *p4 = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p1 = pixel;
            *(Uint16 *)p2 = pixel;
            *(Uint16 *)p3 = pixel;
            *(Uint16 *)p4 = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p1[0] = (pixel >> 16) & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = pixel & 0xff;
                p2[0] = (pixel >> 16) & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = pixel & 0xff;
                p3[0] = (pixel >> 16) & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = pixel & 0xff;
                p4[0] = (pixel >> 16) & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = pixel & 0xff;
            } else {
                p1[0] = pixel & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = (pixel >> 16) & 0xff;
                p2[0] = pixel & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = (pixel >> 16) & 0xff;
                p3[0] = pixel & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = (pixel >> 16) & 0xff;
                p4[0] = pixel & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p1 = pixel;
            *(Uint32 *)p2 = pixel;
            *(Uint32 *)p3 = pixel;
            *(Uint32 *)p4 = pixel;
            break;

        }
    }
}

void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc*2) && (y>=0) && (y<wysokosc*2))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p = pixel;
            break;
        }
    }
}

SDL_Color getPixel(int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)screen->pixels ;

        //przesunięcie względem y
        pPosition+=(screen->pitch*y*2) ;

        //przesunięcie względem x
        pPosition+=(screen->format->BytesPerPixel*x*2);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)surface->pixels ;

        //przesunięcie względem y
        pPosition+=(surface->pitch*y) ;

        //przesunięcie względem x
        pPosition+=(surface->format->BytesPerPixel*x);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}


void ladujBMP(char const* nazwa, int x, int y) {
    SDL_Surface* bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Color kolor;
        for (int yy=0; yy<bmp->h; yy++) {
			for (int xx=0; xx<bmp->w; xx++) {
				kolor = getPixelSurface(xx, yy, bmp);
				setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
			}
        }
		SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }

}


void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}
//Kolory
void setYUV(int xx, int yy, float y, float u, float v) {
    YUV yuv;
    yuv.y = (Uint8)y;
    yuv.u = (Uint8)u;
    yuv.v = (Uint8)v;

    SDL_Color rgb = YUVtoRGB(yuv);
    setPixel(xx, yy, rgb.r, rgb.g, rgb.b);
}

YUV getYUV(int xx, int yy) {
    SDL_Color rgb = getPixel(xx, yy);
    return RGBtoYUV(rgb);
}
void setYIQ(int xx, int yy, float y, float i, float q) {
    YIQ yiq;
    yiq.y = (Uint8)y;
    yiq.i = (Uint8)i;
    yiq.q = (Uint8)q;

    SDL_Color rgb = YIQtoRGB(yiq);
    setPixel(xx, yy, rgb.r, rgb.g, rgb.b);
}

YIQ getYIQ(int xx, int yy) {
    SDL_Color rgb = getPixel(xx, yy);
    return RGBtoYIQ(rgb);
}

void setYCbCr(int xx, int yy, float y, float cb, float cr) {
    YCbCr ycbcr;
    ycbcr.y = (Uint8)y;
    ycbcr.cb = (Uint8)cb;
    ycbcr.cr = (Uint8)cr;

    SDL_Color rgb = YCbCrtoRGB(ycbcr);
    setPixel(xx, yy, rgb.r, rgb.g, rgb.b);
}

YCbCr getYCbCr(int xx, int yy) {
    SDL_Color rgb = getPixel(xx, yy);
    return RGBtoYCbCr(rgb);
}

void setHSL(int xx, int yy, float h, float s, float l) {
    HSL hsl;
    hsl.h = (Uint8)h;
    hsl.s = (Uint8)s;
    hsl.l = (Uint8)l;

    SDL_Color rgb = HSLtoRGB(hsl);
    setPixel(xx, yy, rgb.r, rgb.g, rgb.b);
}

HSL getHSL(int xx, int yy) {
    SDL_Color rgb = getPixel(xx, yy);
    return RGBtoHSL(rgb);
}


void testujYUV() {
    SDL_Color kolor;
    YUV yuv;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            yuv = RGBtoYUV(kolor);
            kolor = YUVtoRGB(yuv);
            setPixel(x + szerokosc / 2, y, kolor.r, kolor.g, kolor.b);
        }
    }
    SDL_UpdateWindowSurface(window);
}

void testujYCbCr() {
    SDL_Color kolor;
    YCbCr ycbcr;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            ycbcr = RGBtoYCbCr(kolor);
            kolor = YCbCrtoRGB(ycbcr);
            setPixel(x + szerokosc / 2, y, kolor.r, kolor.g, kolor.b);
        }
    }
    SDL_UpdateWindowSurface(window);
}

void testujYIQ() {
    SDL_Color kolor;
    YIQ yiq;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            yiq = RGBtoYIQ(kolor);
            kolor = YIQtoRGB(yiq);
            setPixel(x + szerokosc / 2, y, kolor.r, kolor.g, kolor.b);
        }
    }
    SDL_UpdateWindowSurface(window);
}

void testujHSL() {
    SDL_Color kolor;
    HSL hsl;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            hsl = RGBtoHSL(kolor);
            kolor = HSLtoRGB(hsl);
            setPixel(x + szerokosc / 2, y, kolor.r, kolor.g, kolor.b);
        }
    }
    SDL_UpdateWindowSurface(window);
}


//Konwersja 15 i 16 bit RGB
void setRGB555(int xx, int yy, Uint8 r, Uint8 g, Uint8 b)
{
    // 5 bitów na każdą składową
    Uint16 rgb555 = ((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3);

    // Rozbijamy z powrotem, aby przekazać do SDL jako 8-bitowe kolory
    Uint8 rr = ((rgb555 >> 10) & 0x1F) << 3;
    Uint8 gg = ((rgb555 >> 5)  & 0x1F) << 3;
    Uint8 bb = (rgb555 & 0x1F) << 3;

    setPixel(xx, yy, rr, gg, bb);
}
void setRGB555(int xx, int yy, Uint16 rgb555)
{
    Uint8 r = ((rgb555 >> 10) & 0x1F) << 3;
    Uint8 g = ((rgb555 >> 5)  & 0x1F) << 3;
    Uint8 b = (rgb555 & 0x1F) << 3;

    setPixel(xx, yy, r, g, b);
}
void setRGB565(int xx, int yy, Uint8 r, Uint8 g, Uint8 b)
{
    // 5 bitów R, 6 bitów G, 5 bitów B
    Uint16 rgb565 = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);

    // Rozbijamy z powrotem na 8-bitowe wartości dla SDL
    Uint8 rr = ((rgb565 >> 11) & 0x1F) << 3;
    Uint8 gg = ((rgb565 >> 5)  & 0x3F) << 2;
    Uint8 bb = (rgb565 & 0x1F) << 3;

    setPixel(xx, yy, rr, gg, bb);
}
void setRGB565(int xx, int yy, Uint16 rgb565)
{
    Uint8 r = ((rgb565 >> 11) & 0x1F) << 3;
    Uint8 g = ((rgb565 >> 5)  & 0x3F) << 2;
    Uint8 b = (rgb565 & 0x1F) << 3;

    setPixel(xx, yy, r, g, b);
}
SDL_Color getRGB555(int xx, int yy)
{
    SDL_Color color = getPixel(xx, yy);  // pobieramy 24-bitowy kolor z ekranu
    SDL_Color quant;

    // Kwantyzacja (5 bitów na każdą składową)
    quant.r = (color.r & 0xF8);  // r >> 3 << 3
    quant.g = (color.g & 0xF8);
    quant.b = (color.b & 0xF8);

    return quant;
}
Uint16 getRGB555_(int xx, int yy)
{
    SDL_Color color = getPixel(xx, yy);

    // Kwantyzacja i składanie w format 15-bitowy
    Uint16 r5 = color.r >> 3;
    Uint16 g5 = color.g >> 3;
    Uint16 b5 = color.b >> 3;

    Uint16 rgb555 = (r5 << 10) | (g5 << 5) | b5;
    return rgb555;
}
SDL_Color getRGB565(int xx, int yy)
{
    SDL_Color color = getPixel(xx, yy);
    SDL_Color quant;

    // Kwantyzacja: 5 bitów R, 6 bitów G, 5 bitów B
    quant.r = (color.r & 0xF8);          // 5 bitów
    quant.g = (color.g & 0xFC);          // 6 bitów
    quant.b = (color.b & 0xF8);          // 5 bitów

    return quant;
}
Uint16 getRGB565_(int xx, int yy)
{
    SDL_Color color = getPixel(xx, yy);

    Uint16 r5 = color.r >> 3;
    Uint16 g6 = color.g >> 2;
    Uint16 b5 = color.b >> 3;

    Uint16 rgb565 = (r5 << 11) | (g6 << 5) | b5;
    return rgb565;
}

SDL_Color getRGB555D(int xx, int yy)
{
    SDL_Color color = getPixel(xx, yy);
    SDL_Color quant;

    // Pozycja w tablicy Bayera
    int threshold = bayer4x4[yy % 4][xx % 4];

    // Kwantyzacja z ditheringiem
    Uint8 r = color.r;
    Uint8 g = color.g;
    Uint8 b = color.b;

    // Dodajemy perturbację według tablicy Bayera
    r = (Uint8)SDL_clamp(r + threshold * 255 / 16 / 16, 0, 255);
    g = (Uint8)SDL_clamp(g + threshold * 255 / 16 / 16, 0, 255);
    b = (Uint8)SDL_clamp(b + threshold * 255 / 16 / 16, 0, 255);

    // Kwantyzacja (5 bitów na każdą składową)
    quant.r = (r & 0xF8);
    quant.g = (g & 0xF8);
    quant.b = (b & 0xF8);

    return quant;
}

Uint16 getRGB555D_(int xx, int yy)
{
    SDL_Color color = getPixel(xx, yy);

    int threshold = bayer4x4[yy % 4][xx % 4];

    Uint8 r = (Uint8)SDL_clamp(color.r + threshold * 255 / 16 / 16, 0, 255);
    Uint8 g = (Uint8)SDL_clamp(color.g + threshold * 255 / 16 / 16, 0, 255);
    Uint8 b = (Uint8)SDL_clamp(color.b + threshold * 255 / 16 / 16, 0, 255);

    Uint16 r5 = r >> 3;
    Uint16 g5 = g >> 3;
    Uint16 b5 = b >> 3;

    Uint16 rgb555 = (r5 << 10) | (g5 << 5) | b5;
    return rgb555;
}

SDL_Color getRGB565D(int xx, int yy)
{
    SDL_Color color = getPixel(xx, yy);
    SDL_Color quant;

    int threshold = bayer4x4[yy % 4][xx % 4];

    Uint8 r = (Uint8)SDL_clamp(color.r + threshold * 255 / 16 / 16, 0, 255);
    Uint8 g = (Uint8)SDL_clamp(color.g + threshold * 255 / 16 / 16, 0, 255);
    Uint8 b = (Uint8)SDL_clamp(color.b + threshold * 255 / 16 / 16, 0, 255);

    // Kwantyzacja do RGB565 (5R, 6G, 5B)
    quant.r = (r & 0xF8);
    quant.g = (g & 0xFC);
    quant.b = (b & 0xF8);

    return quant;
}

Uint16 getRGB565D_(int xx, int yy)
{
    SDL_Color color = getPixel(xx, yy);

    int threshold = bayer4x4[yy % 4][xx % 4];

    Uint8 r = (Uint8)SDL_clamp(color.r + threshold * 255 / 16 / 16, 0, 255);
    Uint8 g = (Uint8)SDL_clamp(color.g + threshold * 255 / 16 / 16, 0, 255);
    Uint8 b = (Uint8)SDL_clamp(color.b + threshold * 255 / 16 / 16, 0, 255);

    Uint16 r5 = r >> 3;
    Uint16 g6 = g >> 2;
    Uint16 b5 = b >> 3;

    Uint16 rgb565 = (r5 << 11) | (g6 << 5) | b5;
    return rgb565;
}

void testujRGBkonwersje()
{
    SDL_Color kolor;
    Uint16 kolor_quant;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor_quant = getRGB555_(x, y);
            setRGB555(x + szerokosc / 2, y + wysokosc / 2, kolor_quant);
        }
    }
    SDL_UpdateWindowSurface(window);

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor_quant = getRGB565_(x, y);
            setRGB565(x + szerokosc / 2, y, kolor_quant);
        }
    }

    SDL_UpdateWindowSurface(window);
}
void testujRGBkonwersjeDithering()
{
    SDL_Color kolor;
    Uint16 kolor_quant;
    int halfW = szerokosc / 2;
    int halfH = wysokosc / 2;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor_quant = getRGB555D_(x, y);
            setRGB555(x + szerokosc / 2, y, kolor_quant);
        }
    }
    SDL_UpdateWindowSurface(window);

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor_quant = getRGB565D_(x, y);
            setRGB565(x + szerokosc / 2, y + wysokosc / 2, kolor_quant);
        }
    }

    SDL_UpdateWindowSurface(window);
}


//Probkowanie
void podprobkujYUV_420()
{
    int sw2 = SUBW(szerokosc);
    int sh2 = SUBH(wysokosc);


    float *U = (float*)malloc(sw2 * sh2 * sizeof(float));
    float *V = (float*)malloc(sw2 * sh2 * sizeof(float));
    if (!U || !V)
    {
        free(U);
        free(V);
        return;
    }


    for (int by = 0; by < sh2; ++by)
    {
        for (int bx = 0; bx < sw2; ++bx)
        {
            int x0 = bx * 2;
            int y0 = by * 2;
            float sumU = 0.0f, sumV = 0.0f;
            int count = 0;
            for (int yy = 0; yy < 2; ++yy)
            {
                for (int xx = 0; xx < 2; ++xx)
                {
                    int x = x0 + xx;
                    int y = y0 + yy;
                    if (x < szerokosc && y < wysokosc)
                    {
                        YUV yuv = getYUV(x, y);
                        sumU += (float)yuv.u;
                        sumV += (float)yuv.v;
                        ++count;
                    }
                }
            }
            int idx = by * sw2 + bx;
            U[idx] = sumU / (count ? count : 1);
            V[idx] = sumV / (count ? count : 1);
        }
    }


    for (int y = 0; y < wysokosc; ++y)
    {
        for (int x = 0; x < szerokosc; ++x)
        {
            YUV yuv = getYUV(x, y);
            int bx = x / 2;
            int by = y / 2;
            int idx = by * sw2 + bx;
            YUV out;
            out.y = yuv.y;
            out.u = (Uint8)SDL_clamp((int)(U[idx] + 0.5f), 0, 255);
            out.v = (Uint8)SDL_clamp((int)(V[idx] + 0.5f), 0, 255);
            SDL_Color rgb = YUVtoRGB(out);
            setPixel(x + szerokosc / 2, y, rgb.r, rgb.g, rgb.b);
        }
    }


    SDL_UpdateWindowSurface(window);
    free(U);
    free(V);
}

void podprobkujYCbCr_420()
{
    int sw2 = SUBW(szerokosc);
    int sh2 = SUBH(wysokosc);


    float *Cb = (float*)malloc(sw2 * sh2 * sizeof(float));
    float *Cr = (float*)malloc(sw2 * sh2 * sizeof(float));
    if (!Cb || !Cr)
    {
        free(Cb);
        free(Cr);
        return;
    }


    for (int by = 0; by < sh2; ++by)
    {
        for (int bx = 0; bx < sw2; ++bx)
        {
            int x0 = bx * 2;
            int y0 = by * 2;
            float sumCb = 0.0f, sumCr = 0.0f;
            int count = 0;
            for (int yy = 0; yy < 2; ++yy)
            {
                for (int xx = 0; xx < 2; ++xx)
                {
                    int x = x0 + xx;
                    int y = y0 + yy;
                    if (x < szerokosc && y < wysokosc)
                    {
                        YCbCr ycbcr = getYCbCr(x, y);
                        sumCb += (float)ycbcr.cb;
                        sumCr += (float)ycbcr.cr;
                        ++count;
                    }
                }
            }
            int idx = by * sw2 + bx;
            Cb[idx] = sumCb / (count ? count : 1);
            Cr[idx] = sumCr / (count ? count : 1);
        }
    }


    for (int y = 0; y < wysokosc; ++y)
    {
        for (int x = 0; x < szerokosc; ++x)
        {
            YCbCr ycbcr = getYCbCr(x, y);
            int bx = x / 2;
            int by = y / 2;
            int idx = by * sw2 + bx;
            YCbCr out;
            out.y = ycbcr.y;
            out.cb = (Uint8)SDL_clamp((int)(Cb[idx] + 0.5f), 0, 255);
            out.cr = (Uint8)SDL_clamp((int)(Cr[idx] + 0.5f), 0, 255);
            SDL_Color rgb = YCbCrtoRGB(out);
            setPixel(x + szerokosc / 2, y, rgb.r, rgb.g, rgb.b);
        }
    }


    SDL_UpdateWindowSurface(window);
    free(Cb);
    free(Cr);
}

void podprobkujYIQ_420()
{
    int sw2 = SUBW(szerokosc);
    int sh2 = SUBH(wysokosc);


    float *I = (float*)malloc(sw2 * sh2 * sizeof(float));
    float *Q = (float*)malloc(sw2 * sh2 * sizeof(float));
    if (!I || !Q)
    {
        free(I);
        free(Q);
        return;
    }


    for (int by = 0; by < sh2; ++by)
    {
        for (int bx = 0; bx < sw2; ++bx)
        {
            int x0 = bx * 2;
            int y0 = by * 2;
            float sumI = 0.0f, sumQ = 0.0f;
            int count = 0;
            for (int yy = 0; yy < 2; ++yy)
            {
                for (int xx = 0; xx < 2; ++xx)
                {
                    int x = x0 + xx;
                    int y = y0 + yy;
                    if (x < szerokosc && y < wysokosc)
                    {
                        YIQ yiq = getYIQ(x, y);
                        sumI += (float)yiq.i;
                        sumQ += (float)yiq.q;
                        ++count;
                    }
                }
            }
            int idx = by * sw2 + bx;
            I[idx] = sumI / (count ? count : 1);
            Q[idx] = sumQ / (count ? count : 1);
        }
    }


    for (int y = 0; y < wysokosc; ++y)
    {
        for (int x = 0; x < szerokosc; ++x)
        {
            YIQ yiq = getYIQ(x, y);
            int bx = x / 2;
            int by = y / 2;
            int idx = by * sw2 + bx;
            YIQ out;
            out.y = yiq.y;
            out.i = (Uint8)SDL_clamp((int)(I[idx] + 0.5f), 0, 255);
            out.q = (Uint8)SDL_clamp((int)(Q[idx] + 0.5f), 0, 255);
            SDL_Color rgb = YIQtoRGB(out);
            setPixel(x + szerokosc / 2, y, rgb.r, rgb.g, rgb.b);
        }
    }


    SDL_UpdateWindowSurface(window);
    free(I);
    free(Q);
}

void podprobkujHSL_L_420()
{
    int sw2 = SUBW(szerokosc);
    int sh2 = SUBH(wysokosc);


    float *L = (float*)malloc(sw2 * sh2 * sizeof(float));
    if (!L)
    {
        return;
    }


    for (int by = 0; by < sh2; ++by)
    {
        for (int bx = 0; bx < sw2; ++bx)
        {
            int x0 = bx * 2;
            int y0 = by * 2;
            float sumL = 0.0f;
            int count = 0;
            for (int yy = 0; yy < 2; ++yy)
            {
                for (int xx = 0; xx < 2; ++xx)
                {
                    int x = x0 + xx;
                    int y = y0 + yy;
                    if (x < szerokosc && y < wysokosc)
                    {
                        HSL hsl = getHSL(x, y);
                        sumL += (float)hsl.l;
                        ++count;
                    }
                }
            }
            int idx = by * sw2 + bx;
            L[idx] = sumL / (count ? count : 1);
        }
    }


    for (int y = 0; y < wysokosc; ++y)
    {
        for (int x = 0; x < szerokosc; ++x)
        {
            HSL hsl = getHSL(x, y);
            int bx = x / 2;
            int by = y / 2;
            int idx = by * sw2 + bx;
            HSL out;
            out.h = hsl.h;
            out.s = hsl.s;
            out.l = (Uint8)SDL_clamp((int)(L[idx] + 0.5f), 0, 255);
            SDL_Color rgb = HSLtoRGB(out);
            setPixel(x + szerokosc / 2, y, rgb.r, rgb.g, rgb.b);
        }
    }


    SDL_UpdateWindowSurface(window);
    free(L);
}

//Filtry predykcyjne typ1,2,3,4

//Filtry predykcyjne

// func - 1 , 2 , 3 ,4
// bpp dla 888 - 3 dla 555 i 565 - 2
// color type 888 - 1, 565 - 2, 555 - 3,
void PokaFilter(int func,int bpp,int color_type){
    // Szerokość i wysokość połowy obrazu
    int width = szerokosc / 2;
    int height = wysokosc / 2;
    //int bpp = 2; // 16-bit RGB565 = 2 bajty na piksel
    int data_size = width * height * bpp;

    uint8_t *raw = (uint8_t*)malloc(data_size);
    uint8_t *filtered = (uint8_t*)malloc(data_size);
    uint8_t *restored = (uint8_t*)malloc(data_size);

    if (!raw || !filtered)
    {
        printf("Błąd: brak pamięci!\n");
        return;
    }

    // Pobiera z prawego górnego rogu
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            switch (color_type)
        {
            case 1: { // 24-bit 888
                SDL_Color kolor = getPixel(x + width, y);
                raw[(y * width + x) * 3 + 0] = kolor.r;
                raw[(y * width + x) * 3 + 1] = kolor.g;
                raw[(y * width + x) * 3 + 2] = kolor.b;
                break;
            }

            case 2: { // 16-bit 565
                Uint16 c = getRGB565D_(x + width, y);
                memcpy(raw + (y * width + x) * 2, &c, 2);
                break;
            }

            case 3: { // 16-bit 555
                Uint16 c = getRGB555D_(x + width, y);
                memcpy(raw + (y * width + x) * 2, &c, 2);
                break;
            }

            default:
                printf("Error: Podano bledny color_type (1=888, 2=565, 3=555)\n");
        }
        }
    }

    switch(func){
        case 1:
            KodF1Sub(raw, filtered, width, height, bpp);
            break;
        case 2:
            KodF2Up(raw, filtered, width, height, bpp);
            break;
        case 3:
            KodF3AVG(raw, filtered, width, height, bpp);
            break;
        case 4:
            KodF4Paeth(raw, filtered, width, height, bpp);
            break;
        default:
            printf("Error: podano bledny kod funkcj - mozliwe(1,2,3,4)\n");

    }

    // przefiltrowany obraz w PRAWYM DOLNYM rogu
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            // rysuj w prawej dolnej części
            switch(color_type){
                case 1:{
                    Uint8 R = filtered[(y * width + x) * 3 + 0];
                    Uint8 G = filtered[(y * width + x) * 3 + 1];
                    Uint8 B = filtered[(y * width + x) * 3 + 2];
                    setPixel(x + width, y + height, R, G, B);
                    break;
                }
                case 2:{
                    Uint16 kolor_filtered;
                    memcpy(&kolor_filtered, filtered + (y * width + x) * 2, 2);
                    setRGB565(x + width, y + height, kolor_filtered);
                    break;
                }
                case 3:{
                    Uint16 kolor_filtered;
                    memcpy(&kolor_filtered, filtered + (y * width + x) * 2, 2);
                    setRGB555(x + width, y + height, kolor_filtered);
                    break;
                }
                default:
                    printf("Error: Podano bledny color_type - mozliwe(1,2,3)");


            }
        }
    }

    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);

    switch(func){
        case 1:
            DekodF1Sub(filtered, restored, width, height, bpp);
            break;
        case 2:
            DekodF2Up(filtered, restored, width, height, bpp);
            break;
        case 3:
            DekodF3AVG(filtered, restored, width, height, bpp);
            break;
        case 4:
            DekodF4Paeth(filtered, restored, width, height, bpp);
            break;
        default:
            printf("Error: podano bledny kod funkcji - mozliwe(1,2,3,4)\n");
            return;
    }

    //Rysuj odfiltrowany spowrotem
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            switch(color_type) {
            case 1: { // 24-bit RGB888
                Uint8 R = restored[(y * width + x) * 3 + 0];
                Uint8 G = restored[(y * width + x) * 3 + 1];
                Uint8 B = restored[(y * width + x) * 3 + 2];
                setPixel(x + width, y + height, R, G, B);
                break;
            }
            case 2: { // 16-bit RGB565
                Uint16 kolor_restored;
                memcpy(&kolor_restored, restored + (y * width + x) * 2, 2);
                setRGB565(x + width, y + height, kolor_restored);
                break;
            }
            case 3: { // 16-bit RGB555
                Uint16 kolor_restored;
                memcpy(&kolor_restored, restored + (y * width + x) * 2, 2);
                setRGB555(x + width, y + height, kolor_restored);
                break;
            }
            default:
                printf("Error: Podano bledny color_type - mozliwe(1,2,3)");
        }
        }
    }

    SDL_UpdateWindowSurface(window);

    // Sprzątanie
    free(raw);
    free(filtered);
    free(restored);

}
void KodF1Sub(const uint8_t *raw, uint8_t *out, int width, int height, int bpp)
{
    int stride = width * bpp;
    for (int y = 0; y < height; ++y)
    {
        const uint8_t *row = raw + y * stride;
        uint8_t *orow = out + y * stride;
        for (int x = 0; x < stride; ++x)
        {
            if (x >= bpp) orow[x] = (uint8_t)(row[x] - row[x - bpp]);
            else orow[x] = row[x]; // pierwszy pixel w linii - left = 0
        }
    }
}

void DekodF1Sub(const uint8_t *in, uint8_t *out, int width, int height, int bpp)
{
    int stride = width * bpp;
    for (int y = 0; y < height; ++y)
    {
        const uint8_t *irow = in + y * stride;
        uint8_t *row = out + y * stride;
        for (int x = 0; x < stride; ++x)
        {
            if (x >= bpp) row[x] = (uint8_t)(irow[x] + row[x - bpp]);
            else row[x] = irow[x];
        }
    }
}

void KodF2Up(const uint8_t *raw, uint8_t *out, int width, int height, int bpp)
{
    int stride = width * bpp;
    /* pierwszy wiersz - prior = 0 */
    memcpy(out, raw, stride);
    for (int y = 1; y < height; ++y)
    {
        const uint8_t *row = raw + y * stride;
        const uint8_t *prior = raw + (y - 1) * stride;
        uint8_t *orow = out + y * stride;
        for (int x = 0; x < stride; ++x) orow[x] = (uint8_t)(row[x] - prior[x]);
    }
}


void DekodF2Up(const uint8_t *in, uint8_t *out, int width, int height, int bpp)
{
    int stride = width * bpp;
    /* pierwszy wiersz */
    memcpy(out, in, stride);
    for (int y = 1; y < height; ++y)
    {
        const uint8_t *irow = in + y * stride;
        const uint8_t *prior = out + (y - 1) * stride;
        uint8_t *row = out + y * stride;
        for (int x = 0; x < stride; ++x) row[x] = (uint8_t)(irow[x] + prior[x]);
    }
}

void KodF3AVG(const uint8_t *raw, uint8_t *out, int width, int height, int bpp)
{
    int stride = width * bpp;
    for (int y = 0; y < height; ++y)
    {
        const uint8_t *row = raw + y * stride;
        const uint8_t *prior = (y > 0) ? (raw + (y - 1) * stride) : NULL;
        uint8_t *orow = out + y * stride;
        for (int x = 0; x < stride; ++x)
        {
            int left = (x >= bpp) ? row[x - bpp] : 0;
            int up = (prior) ? prior[x] : 0;
            int avg = (left + up) >> 1; /* floor((left+up)/2) */
            orow[x] = (uint8_t)(row[x] - avg);
        }
    }
}


void DekodF3AVG(const uint8_t *in, uint8_t *out, int width, int height, int bpp)
{
    int stride = width * bpp;
    for (int y = 0; y < height; ++y)
    {
        const uint8_t *irow = in + y * stride;
        const uint8_t *prior = (y > 0) ? (out + (y - 1) * stride) : NULL;
        uint8_t *row = out + y * stride;
        for (int x = 0; x < stride; ++x)
        {
            int left = (x >= bpp) ? row[x - bpp] : 0;
            int up = (prior) ? prior[x] : 0;
            int avg = (left + up) >> 1;
            row[x] = (uint8_t)(irow[x] + avg);
        }
    }
}

static inline int paeth_predictor(int a, int b, int c)
{
    int p = a + b - c;
    int pa = abs(p - a);
    int pb = abs(p - b);
    int pc = abs(p - c);
    if (pa <= pb && pa <= pc) return a;
    if (pb <= pc) return b;
    return c;
}


void KodF4Paeth(const uint8_t *raw, uint8_t *out, int width, int height, int bpp)
{
    int stride = width * bpp;
    for (int y = 0; y < height; ++y)
    {
        const uint8_t *row = raw + y * stride;
        const uint8_t *prior = (y > 0) ? (raw + (y - 1) * stride) : NULL;
        uint8_t *orow = out + y * stride;
        for (int x = 0; x < stride; ++x)
        {
            int left = (x >= bpp) ? row[x - bpp] : 0;
            int up = (prior) ? prior[x] : 0;
            int up_left = (prior && x >= bpp) ? prior[x - bpp] : 0;
            int p = paeth_predictor(left, up, up_left);
            orow[x] = (uint8_t)(row[x] - p);
        }
    }
}


void DekodF4Paeth(const uint8_t *in, uint8_t *out, int width, int height, int bpp)
{
    int stride = width * bpp;
    for (int y = 0; y < height; ++y)
    {
        const uint8_t *irow = in + y * stride;
        const uint8_t *prior = (y > 0) ? (out + (y - 1) * stride) : NULL;
        uint8_t *row = out + y * stride;
        for (int x = 0; x < stride; ++x)
        {
            int left = (x >= bpp) ? row[x - bpp] : 0;
            int up = (prior) ? prior[x] : 0;
            int up_left = (prior && x >= bpp) ? prior[x - bpp] : 0;
            int p = paeth_predictor(left, up, up_left);
            row[x] = (uint8_t)(irow[x] + p);
        }
    }
}

