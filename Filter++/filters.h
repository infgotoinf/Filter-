#pragma once

#ifndef FILTERS_H
#define FILTERS_H

#include <random>

std::random_device dev;
std::mt19937 rnd(dev());
std::uniform_int_distribution<unsigned> unsdist(0, 255);
std::uniform_int_distribution<unsigned> rnddist(1, 10);

struct Pixel
{
    int r; int b; int g;
    Pixel(const int const &r = 0, const int const &b = 0, const int const &g = 0)
        : r(r), b(b), g(g)
    { }
};

typedef void (*Filter)(Pixel&);

void deepfried(Pixel& p)
{
    (p.r > 122 ? p.r = 255 : p.r = 0);
    (p.g > 122 ? p.g = 255 : p.g = 0);
    (p.b > 122 ? p.b = 255 : p.b = 0);
}

void negative(Pixel& p)
{
    p.r = 255 - p.r;
    p.g = 255 - p.g;
    p.b = 255 - p.b;
}

void grayscale(Pixel& p)
{
    p.r = 0.299f * p.r + 0.587f * p.g + 0.114f * p.b;
    p.g = p.r; p.b = p.g;
}

void chanelSwap(Pixel& p)
{
    std::swap(p.r, p.g);
    std::swap(p.r, p.b);
}

void noise(Pixel& p)
{
    p.r = unsdist(rnd);
    p.g = unsdist(rnd);
    p.b = unsdist(rnd);
}

void lostControl(Pixel& p)
{
    p.r = (p.r % 2 == 0 ? unsdist(rnd) : p.r);
    p.g = (p.g % 2 == 0 ? unsdist(rnd) : p.g);
    p.b = (p.b % 2 == 0 ? unsdist(rnd) : p.b);
}

void _5bit(Pixel& p)
{
    if (p.r > p.g && p.r > p.b) {
        p.r = 255; p.g =   0; p.b =   0; }
    else if (p.g > p.r && p.g > p.b) {
        p.r =   0; p.g = 255; p.b =   0; }
    else if (p.b > p.r && p.b > p.g) {
        p.r =   0; p.g =   0; p.b = 255; }
    else if (p.b + p.r + p.g > 377) {
        p.r = 255; p.g = 255; p.b = 255; }
    else {
        p.r = 0; p.g = 0; p.b = 0; }
}

void compress(Pixel& p)
{
    p.r -= p.r % 51;
    p.g -= p.g % 51;
    p.b -= p.b % 51;
}

void experement(Pixel& p)
{
    p.r = (p.r * p.r) % 255;
    p.g = (p.g * p.g) % 255;
    p.b = (p.b * p.b) % 255;
}

void random(Pixel& p)
{
    switch (rnddist(rnd))
    {
    case  1: return deepfried(p);
    case  2: return negative(p);
    case  3: return grayscale(p);
    case  4: return chanelSwap(p);
    case  5: return noise(p);
    case  6: return lostControl(p);
    case  7: return _5bit(p);
    case  8: return compress(p);
    case  9: return experement(p);
    }
}


Filter chooseFilter()
{
    int choice;
    std::cout << "Choose filter:\n";
    std::cout << " 1: deepfried\n";
    std::cout << " 2: negative\n";
    std::cout << " 3: grayscale\n";
    std::cout << " 4: chanelSwap\n";
    std::cout << " 5: noise\n";
    std::cout << " 6: lostControl\n";
    std::cout << " 7: _5bit\n";
    std::cout << " 8: compress\n";
    std::cout << " 9: experement\n";
    std::cout << "10: random\n";

    do {
        std::cin >> choice;
        switch (choice)
        {
        case  1: return deepfried;
        case  2: return negative;
        case  3: return grayscale;
        case  4: return chanelSwap;
        case  5: return noise;
        case  6: return lostControl;
        case  7: return _5bit;
        case  8: return compress;
        case  9: return experement;
        case 10: return random;
        default: std::cout << "Invalid choice!" << std::endl;
        }
    } while (1);
}


#endif // !FILTERS.H