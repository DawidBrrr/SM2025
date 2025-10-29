// metody do algorytmu kwantyzacji (MedianCut)
#include "SM2025-MedianCut.h"
#include "SM2025-Zmienne.h"
#include "SM2025-Funkcje.h"
#include "SM2025-Paleta.h"

using namespace std;

void paletaMedianCutBW()
{
    ileKubelkow = 0;
    ileKolorow = 0;
    czyscPalete();
    SDL_Color kolor;
    Uint8 szary = 0;
    int numer = 0;
    int indeks = 0;

    for (int y = 0; y < wysokosc / 2; y++)
    {
        for (int x = 0; x < szerokosc / 2; x++)
        {
            kolor = getPixel(x, y);
            szary = static_cast<Uint8>(0.299 * kolor.r + 0.587 * kolor.g + 0.114 * kolor.b);
            obrazekS[numer] = szary;
            setPixel(x + szerokosc / 2, y, szary, szary, szary);
            numer++;
        }
    }
    MedianCutBW(0, numer - 1, 8); // Iteracje ustawione na 8

    for (int y = 0; y < wysokosc / 2; y++)
    {
        for (int x = 0; x < szerokosc / 2; x++)
        {
            szary = getPixel(x + szerokosc / 2, y).r;
            indeks = znajdzSasiadaBW(szary);
            setPixel(x + szerokosc / 2, y + wysokosc / 2, paleta8s[indeks].r, paleta8s[indeks].g, paleta8s[indeks].b);
        }
    }
    narysujPalete3b(0, 310, paleta8s);
    SDL_UpdateWindowSurface(window);
}

void narysujPalete3b(int px, int py, SDL_Color pal3b[])
{
    int x, y;
    for (int k=0; k<256; k++)
    {
        y = k/16;
        x = k%16;

        for(int xx=0; xx<10; xx++)
        {
            for(int yy=0; yy<10; yy++)
            {
                setPixel(x*10+xx+px, y*10+yy+py, pal3b[k].r, pal3b[k].g, pal3b[k].b);
            }
        }
    }
}

void MedianCutBW(int start, int koniec, int iteracja)
{
    for(int i=0; i<iteracja; i++) cout<<" ";
        cout<<"start: "<<start<<", koniec: "<<koniec<<", iteracja:"<<iteracja<<endl;
        if(iteracja > 0)
        {
            //najpierw sortujemy kubelek
            sortujKubelekBW(start, koniec);
            for(int i=0; i<iteracja; i++) cout<<" ";
            cout<<"Dzielimy kubelek na poziomie "<<iteracja<<endl;

            //wyznaczamy srodek podzialu
            int srodek = (start + koniec+1) /2;

            //i dzielimy kubelek na mniejsze
            MedianCutBW(start, srodek-1, iteracja-1);
            MedianCutBW(srodek, koniec, iteracja-1);

        }
        else
        {
        int sumaBW = 0;
        for (int p = start; p<=koniec; p++)
        {
            sumaBW += obrazekS[p];
        }
        Uint8 noweBW = (sumaBW / (koniec+1 - start));
        SDL_Color nowyKolor = {noweBW, noweBW, noweBW};
        paleta8s[ileKubelkow] = nowyKolor;

        cout<<"Kubelek "<<ileKubelkow<<": ";
        cout<<"(s:"<<start<<", k:"<<koniec<<", e:"<<(koniec+1 - start)<<")";
        cout<<endl;
        cout<<"Kolor "<<ileKubelkow<<": ("<<(int)nowyKolor.r<<", ";
        cout<<(int)nowyKolor.g<<","<<(int)nowyKolor.b<<")"<<endl;
        ileKubelkow++;
    }
}

void sortujKubelekBW(int start, int koniec)
{
    int minimum;
    for(int p = start; p <= koniec; p++)
    {
        minimum = p;
        for(int i = p; i <= koniec; i++)
        {
            if(obrazekS[i] < obrazekS[minimum])
                minimum = i;
        }
        swap(obrazekS[p], obrazekS[minimum]);
    }
}

int znajdzSasiadaBW(Uint8 wartosc)
{
    int minimum = 999999;
    int indexMinimum = 0;
    int odleglosc = 0;

    for (int i = 0; i < 256; i++) // Poprawiona liczba iteracji
    {
        odleglosc = abs(wartosc - paleta8s[i].r);
        if (odleglosc < minimum)
        {
            minimum = odleglosc;
            indexMinimum = i; // Poprawa b³êdu indeksowania
        }
    }
    return indexMinimum;
}


void paletaMedianCut()
{
    ileKubelkow = 0;
    ileKolorow = 0;
    czyscPalete();
    SDL_Color kolor;
    int numer = 0;
    int indeks = 0;

    for (int y=0; y<wysokosc/2; y++)
    {
        for (int x=0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x, y);
            obrazekK[numer] = {kolor.r, kolor.g, kolor.b};
            setPixel(x + szerokosc/2, y, obrazekK[numer].r, obrazekK[numer].g, obrazekK[numer].b);
            numer++;
        }
    }
    MedianCut(0, numer-1, 8);

    for(int y = 0; y < wysokosc/2; y++){
        for(int x = 0; x< szerokosc/2; x++){
            kolor = getPixel(x, y);
            indeks = znajdzSasiada(kolor);
            setPixel(x + szerokosc/2, y + wysokosc/2,
                     paleta8k[indeks].r,paleta8k[indeks].g,paleta8k[indeks].b);
        }
    }
    narysujPalete(0,210,paleta8k);
    SDL_UpdateWindowSurface(window);


}

void MedianCut(int start, int koniec, int iteracja)
{
    for(int i=0; i<iteracja; i++) cout<<" ";
    cout<<"start: "<<start<<", koniec: "<<koniec<<", iteracja:"<<iteracja<<endl;
    if(iteracja > 0)
    {
        Uint8 sortowanie=najwiekszaRoznica(start, koniec);
        switch(sortowanie)
        {
            case 1: cout<<"sortujemy wedlug R"<<endl;
                    break;
            case 2: cout<<"sortujemy wedlug G"<<endl;
                    break;
            case 3: cout<<"sortujemy wedlug B"<<endl;
                    break;

        }
        sortujKubelek(start, koniec, sortowanie);
        for(int i=0; i<iteracja; i++) cout<<" ";
        cout<<"Dzielimy kubelek na poziomie "<<iteracja<<endl;

        //wyznaczamy srodek podzialu
        int srodek = (start + koniec+1) /2;

        //i dzielimy kubelek na mniejsze
        MedianCut(start, srodek-1, iteracja-1);
        MedianCut(srodek, koniec, iteracja-1);
    }
    else{
        //budujemy paletê uœredniaj¹c wartoœci z okreœlonego kube³ka
        int sumaR = 0, sumaG = 0, sumaB = 0;
        for(int p=start; p<=koniec; p++){
            sumaR += obrazekK[p].r; // sumujemy wartoœci R z danego kube³ka
            sumaG += obrazekK[p].g; // sumujemy wartoœci G z danego kube³ka
            sumaB += obrazekK[p].b; // sumujemy wartoœci B z danego kube³ka
        }
        int sredniaR = sumaR / (koniec+1 - start); // wyliczamy œredni¹ R
        int sredniaG = sumaG / (koniec+1 - start); // wyliczamy œredni¹ G
        int sredniaB = sumaB / (koniec+1 - start); // wyliczamy œredni¹ B

        SDL_Color nowyKolor = {sredniaR, sredniaG , sredniaB};
        paleta8k[ileKubelkow]=nowyKolor; // i dodajemy kolore do naszej palety

        cout <<"Kubelek "<<ileKubelkow<<": ";
        cout <<"s:"<<start<<",k"<<koniec<<", e:"<<(koniec+1 - start)<<")";
        cout<<endl;
        cout<<"Kolor "<<ileKubelkow<<": ("<<(int)nowyKolor.r<<",";
        cout<<(int)nowyKolor.g<<","<<(int)nowyKolor.b<<")"<<endl;
        ileKubelkow++;
    }

}

int znajdzSasiada(SDL_Color kolor){
    int minimum = 999999;
    int indexMinimum = 0;

    SDL_Color kolorPaleta;
    float odleglosc;

    for(int i = 0; i < 256; i++){
        kolorPaleta = paleta8k[i];
        odleglosc = sqrt((kolor.r - kolorPaleta.r)*(kolor.r - kolorPaleta.r) +
                         (kolor.g - kolorPaleta.g)*(kolor.g - kolorPaleta.g) +
                         (kolor.b - kolorPaleta.b)*(kolor.b - kolorPaleta.b));
        if(odleglosc < minimum){
            minimum = odleglosc;
            indexMinimum = i;
        }
    }
    return indexMinimum;


}

Uint8 najwiekszaRoznica(int start, int koniec)
{
    int minR=start, minG=start, minB=start;
    int maxR=start, maxG=start, maxB=start;

    Uint8 roznica = 0;

    for(int i=start; i<=koniec; i++)
    {
        if(obrazekK[i].b < obrazekK[minB].b) minB=i;
        if(obrazekK[i].g < obrazekK[minG].g) minG=i;
        if(obrazekK[i].r < obrazekK[minR].r) minR=i;
        if(obrazekK[i].b > obrazekK[maxB].b) maxB=i;
        if(obrazekK[i].g > obrazekK[maxG].g) maxG=i;
        if(obrazekK[i].r > obrazekK[maxR].r) maxR=i;
    }
    int roznicaR = obrazekK[maxR].r-obrazekK[minR].r;
    int roznicaG = obrazekK[maxG].g-obrazekK[minG].g;
    int roznicaB = obrazekK[maxB].b-obrazekK[minB].b;
    cout<<"roznice: (R:"<<roznicaR<<", G:"<<roznicaG<<", B:"<<roznicaB<<")\n";
    int roznicaM = max(max(roznicaR, roznicaG), roznicaB);

    if(roznicaM==roznicaR)
        roznica = 1;
    else if (roznicaM == roznicaG)
        roznica = 2;
    else roznica = 3;
    return roznica;
}

void sortujKubelek(int start, int koniec, Uint8 sortowanie)
{
    int minimum;
    for(int p = start; p<=koniec; p++)
    {
        minimum = p;
        for(int i = p; i <= koniec; i++)
        {
            switch(sortowanie)
            {
            case 1:
                if (obrazekK[i].r<obrazekK[minimum].r) minimum = i;
                break;
            case 2:
                if (obrazekK[i].g<obrazekK[minimum].g) minimum = i;
                break;
            case 3:
                if (obrazekK[i].b<obrazekK[minimum].b) minimum = i;
                break;

            }
        }
        swap(obrazekK[p], obrazekK[minimum]);
    }
}


