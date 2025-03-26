#pragma once

#ifndef FILTERS_H
#define FILTERS_H

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

Filter chooseFilter()
{
    int choice;
    std::cout << "Choose filter:\n";
    std::cout << "1: deepfried\n";
    std::cout << "2: negative\n";
    std::cout << "3: grayscale\n";

    do {
        std::cin >> choice;
        switch (choice)
        {
        case  1: return deepfried;
        case  2: return negative;
        case  3: return grayscale;
        default: std::cout << "Invalid choice!" << std::endl;
        }
    } while (1);
}


#endif // !FILTERS.H