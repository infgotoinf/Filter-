#pragma once

#ifndef FILTERS_H
#define FILTERS_H

typedef void (*Filter)(int&, int&, int&);

void deepfried(int& r, int& g, int& b)
{
    (r > 122 ? r = 255 : r = 0);
    (g > 122 ? g = 255 : g = 0);
    (b > 122 ? b = 255 : b = 0);
}

void negative(int& r, int& g, int& b)
{
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
}

Filter chooseFilter()
{
    int choice;
    std::cout << "Choose filter:\n";
    std::cout << "1: deepfried\n";
    std::cout << "2: negative\n";

    do {
        std::cin >> choice;
        switch (choice)
        {
        case  1: return deepfried;
        case  2: return negative;
        default: std::cout << "Invalid choice!" << std::endl;
        }
    } while (1);
}


#endif // !FILTERS.H