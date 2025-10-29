// funkcje do redukcji kolorów i tworzenia palet
#include "SM2025-Paleta.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Funkcje.h"

// Narzuocona Kolorowa 8bit
void narzucona() {
    int index = 0;
    for (int r = 0; r < 8; r++) {
        for (int g = 0; g < 8; g++) {
            for (int b = 0; b < 4; b++) {
                paleta8k[index].r = (Uint8)(r * 255 / 7);
                paleta8k[index].g = (Uint8)(g * 255 / 7);
                paleta8k[index].b = (Uint8)(b * 255 / 3);
                index++;
            }
        }
    }
    SDL_Color kolor;
    int R, G, B;
    int nowyR, nowyG, nowyB;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = round(R * 7.0 / 255.0);
            nowyG = round(G * 7.0 / 255.0);
            nowyB = round(B * 3.0 / 255.0);

            R = (int)(nowyR * 255.0 / 7.0);
            G = (int)(nowyG * 255.0 / 7.0);
            B = (int)(nowyB * 255.0 / 3.0);

            setPixel(x + szerokosc / 2, y + wysokosc / 2, R, G, B);
        }
    }

    narysujPalete(0, 260, paleta8k);
}

//Funkcja rysująca palete 8bit Narzucona
void narysujPalete(int px,int py, SDL_Color pal8[]){
    int x,y;
    for( int k=0;k<256;k++){
        y = k/16; // wiersz
        x = k%16; // kolumna

        for(int xx=0;xx<10;xx++){
            for(int yy=0;yy<10;yy++){
                setPixel(px + x * 10 + xx, py + y * 10 + yy, pal8[k].r, pal8[k].g, pal8[k].b);
            }
        }

    }
}
// tworzy palete narzucona szara
void NarzuconaS() {
    for (int k = 0; k < 256; k++) {
        paleta8s[k].r = k;
        paleta8s[k].g = k;
        paleta8s[k].b = k;
    }
    SDL_Color kolor;
    int R, G, B;
    double K;
    int idx;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            K = 0.299 * R + 0.587 * G + 0.114 * B;
            idx = (int)(K + 0.5);
            if (idx < 0) idx = 0;
            if (idx > 255) idx = 255;

            setPixel(x + szerokosc / 2, y + wysokosc / 2,
                     paleta8s[idx].r, paleta8s[idx].g, paleta8s[idx].b);
        }
    }

    narysujPaleteS(0, 260, paleta8s);

    SDL_UpdateWindowSurface(window);
}

//Rysuje palete narzucona w skali szarosc
void narysujPaleteS(int px, int py, SDL_Color pal8S[]) {
    int x, y;
    for (int k = 0; k < 256; k++) {
        y = k / 16;
        x = k % 16;

        for (int xx = 0; xx < 10; xx++) {
            for (int yy = 0; yy < 10; yy++) {
                setPixel(px + x * 10 + xx, py + y * 10 + yy,
                         pal8S[k].r, pal8S[k].g, pal8S[k].b);
            }
        }
    }
}

//Paleta wykryta
void paletaWykryta()
{
    czyscPalete();
    int indexKoloru;
    SDL_Color kolor;

    for(int y=0; y<wysokosc/2; y++)
    {
        for(int x=0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x,y);
            indexKoloru = sprawdzKolor(kolor);
        }
    }
    std::cout << "ile kolorow: " << ileKolorow << std::endl;
    if(ileKolorow <= 256)
    {
        std::cout << "Paleta spelnia ograniczenia 8-bit / piksel" << std::endl;
        narysujPalete(0,210,paleta8);
    }
    else
        std::cout << "Paleta przekracze ograniczenia 8-bit / piksel" << std::endl;
}

//Funkcja pomocnicza do czyszczenia palety
void czyscPalete()
{
    for(int k =0; k<ileKolorow; k++)
    {
        paleta8[k] = {0,0,0};
    }
    ileKolorow = 0;
    for(int k=0; k<256; k++)
    {
        paleta8s[k] = {0, 0, 0};
        paleta8k[k] = {0, 0, 0};
    }
}


bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2)
{
    if(kolor1.r != kolor2.r)
        return false;
    if(kolor1.g != kolor2.g)
        return false;
    if(kolor1.b != kolor2.b)
        return false;

    return true;
}

int dodajKolor(SDL_Color kolor)
{
    int aktualnyKolor = ileKolorow;
    paleta8[aktualnyKolor] = kolor;
    if(ileKolorow < 256)
    {
        //std::cout << aktualnyKolor<< ":[";
        //std::cout << (int)kolor.r <<","<<(int)kolor.g << "," << (int)kolor.b;
        //std::cout << "]" << std::endl;
    }
    ileKolorow++;
    return aktualnyKolor;
}



int sprawdzKolor(SDL_Color kolor){
    if(ileKolorow > 0)
    {
        for(int k =0; k<ileKolorow; k++)
        {
            if(porownajKolory(kolor, paleta8[k]))
            {
                return k;
            }
        }
    }
    return dodajKolor(kolor);
}





