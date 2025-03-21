#pragma once

#ifndef FILTERS_H
#define FILTERS_H

void deepfried(int& r, int& g, int& b)
{
    (r > 122 ? r = 255 : r = 0);
    (g > 122 ? g = 255 : g = 0);
    (b > 122 ? b = 255 : b = 0);
}
#endif // !FILTERS.H