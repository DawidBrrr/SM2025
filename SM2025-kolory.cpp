#include "SM2025-kolory.h"

#include <math.h>

YUV RGBtoYUV(SDL_Color rgb) {
    YUV yuv;
    float R = rgb.r / 255.0f;
    float G = rgb.g / 255.0f;
    float B = rgb.b / 255.0f;

    float Y = 0.299f * R + 0.587f * G + 0.114f * B;
    float U = -0.14713f * R - 0.28886f * G + 0.436f * B;
    float V = 0.615f * R - 0.51499f * G - 0.10001f * B;

    yuv.y = (Uint8)(Y * 255.0f);
    yuv.u = (Uint8)((U + 0.436f) / (2 * 0.436f) * 255.0f);
    yuv.v = (Uint8)((V + 0.615f) / (2 * 0.615f) * 255.0f);

    return yuv;
}

SDL_Color YUVtoRGB(YUV yuv) {
    SDL_Color rgb;
    float Y = yuv.y / 255.0f;
    float U = (yuv.u / 255.0f) * (2 * 0.436f) - 0.436f;
    float V = (yuv.v / 255.0f) * (2 * 0.615f) - 0.615f;

    float R = Y + 1.13983f * V;
    float G = Y - 0.39465f * U - 0.58060f * V;
    float B = Y + 2.03211f * U;

    rgb.r = (Uint8)fminf(fmaxf(R * 255.0f, 0), 255);
    rgb.g = (Uint8)fminf(fmaxf(G * 255.0f, 0), 255);
    rgb.b = (Uint8)fminf(fmaxf(B * 255.0f, 0), 255);
    return rgb;
}

YIQ RGBtoYIQ(SDL_Color rgb){
    YIQ yiq;
    float Y, I, Q;

    Y =  0.29988 * rgb.r + 0.587000 * rgb.g + 0.114000 * rgb.b;
    I =  0.595716 * rgb.r - 0.274453 * rgb.g - 0.321263 * rgb.b;
    Q =  0.211456 * rgb.r - 0.522591 * rgb.g + 0.311135 * rgb.b;

    yiq.y = (Uint8)Y;
    yiq.i = (Uint8)(I + 128);
    yiq.q = (Uint8)(Q + 128);

    return yiq;
}

SDL_Color YIQtoRGB(YIQ yiq){
    SDL_Color rgb;
    float r, g, b;

    r = yiq.y + 0.9563 * (yiq.i - 128) + 0.6210 * (yiq.q - 128);
    g = yiq.y - 0.2721 * (yiq.i - 128) - 0.6474 * (yiq.q - 128);
    b = yiq.y - 1.1070 * (yiq.i - 128) + 1.7046 * (yiq.q - 128);

    rgb.r = (Uint8)fminf(fmaxf(r, 0), 255);
    rgb.g = (Uint8)fminf(fmaxf(g, 0), 255);
    rgb.b = (Uint8)fminf(fmaxf(b, 0), 255);

    return rgb;
}

YCbCr RGBtoYCbCr(SDL_Color rgb) {
    YCbCr ycbcr;
    float R = rgb.r;
    float G = rgb.g;
    float B = rgb.b;

    float Y  =  0.299f * R + 0.587f * G + 0.114f * B;
    float Cb = 128.0f - 0.168736f * R - 0.331264f * G + 0.500000f * B;
    float Cr = 128.0f + 0.500000f * R - 0.418688f * G - 0.081312f * B;

    ycbcr.y  = (Uint8)fminf(fmaxf(Y, 0), 255);
    ycbcr.cb = (Uint8)fminf(fmaxf(Cb, 0), 255);
    ycbcr.cr = (Uint8)fminf(fmaxf(Cr, 0), 255);

    return ycbcr;
}

SDL_Color YCbCrtoRGB(YCbCr ycbcr) {
    SDL_Color rgb;
    float Y  = ycbcr.y;
    float Cb = ycbcr.cb - 128.0f;
    float Cr = ycbcr.cr - 128.0f;

    float R = Y + 1.402f * Cr;
    float G = Y - 0.344136f * Cb - 0.714136f * Cr;
    float B = Y + 1.772f * Cb;

    rgb.r = (Uint8)fminf(fmaxf(R, 0), 255);
    rgb.g = (Uint8)fminf(fmaxf(G, 0), 255);
    rgb.b = (Uint8)fminf(fmaxf(B, 0), 255);
    return rgb;
}

HSL RGBtoHSL(SDL_Color rgb) {
    HSL hsl;
    float r = rgb.r / 255.0f;
    float g = rgb.g / 255.0f;
    float b = rgb.b / 255.0f;

    float max = fmaxf(fmaxf(r, g), b);
    float min = fminf(fminf(r, g), b);
    float h, s, l;
    l = (max + min) / 2.0f;

    if (max == min) {
        h = s = 0; // achromatyczny
    } else {
        float d = max - min;
        s = l > 0.5f ? d / (2.0f - max - min) : d / (max + min);

        if (max == r)
            h = (g - b) / d + (g < b ? 6 : 0);
        else if (max == g)
            h = (b - r) / d + 2;
        else
            h = (r - g) / d + 4;

        h /= 6;
    }

    hsl.h = (Uint8)(h * 255);
    hsl.s = (Uint8)(s * 255);
    hsl.l = (Uint8)(l * 255);
    return hsl;
}

static float colorComp(float t, float p, float q) {
    if (t < 0) t += 1;
    if (t > 1) t -= 1;
    if (t < 1.0f / 6.0f) return p + (q - p) * 6 * t;
    if (t < 1.0f / 2.0f) return q;
    if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6;
    return p;
}

SDL_Color HSLtoRGB(HSL hsl) {
    SDL_Color rgb;
    float h = hsl.h / 255.0f;
    float s = hsl.s / 255.0f;
    float l = hsl.l / 255.0f;

    float r, g, b;

    if (s == 0) {
        r = g = b = l; // szaroœæ
    } else {
        float q = (l < 0.5f) ? (l * (1 + s)) : (l + s - l * s);
        float p = 2 * l - q;

        float tR = h + 1.0f / 3.0f;
        float tG = h;
        float tB = h - 1.0f / 3.0f;

        r = colorComp(tR, p, q);
        g = colorComp(tG, p, q);
        b = colorComp(tB, p, q);
    }

    rgb.r = (Uint8)(r * 255);
    rgb.g = (Uint8)(g * 255);
    rgb.b = (Uint8)(b * 255);
    return rgb;
}


