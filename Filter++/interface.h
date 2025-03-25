#pragma once

#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <Windows.h>
#include <sstream>
#include "image.h"
#include "filters.h"


struct Interface
{
    static std::string openFile()
    {
        OPENFILENAMEA ofn = { sizeof(OPENFILENAMEA) };

        char szFile[_MAX_PATH];
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = GetConsoleWindow();
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter =
            "Image (*.png;*.bmp;*.jpg;*.ppm)\0*.png;*.bmp;*.jpg;*.ppm\0\
    	PNG (*.png)\0*.png\0\
    	BMP (*.bmp)\0*.bmp\0\
    	JPG (*.jpg)\0*.jpg\0\
    	PPM (*.ppm)\0*.ppm\0\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileNameA(&ofn))
            return szFile;
        else
            return "☺";
    }

    static std::string saveFile(Image& image)
    {
        OPENFILENAMEA ofn = { sizeof(OPENFILENAMEA) };

        char szFile[_MAX_PATH];
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = GetConsoleWindow();
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter =
            "PPM (*.ppm)\0*.ppm\0\
        PNG (*.png)\0*.png\0\
    	JPG (*.jpg)\0*.jpg\0\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        ofn.lpstrDefExt = "";

        do {
            if (GetSaveFileNameA(&ofn))
            {
                if (fs::path(szFile).extension() == ".ppm")
                    return szFile;
                else
                {
                    std::cout << "This extension does not supported";
                }
                /*int width, height, channels;
                unsigned char* img = stbi_load(image.path.filename().string().c_str(), &width, &height, &channels, 0);
                stbi_write_png((image.path.stem().string() + ".png").c_str(), width, height, channels, img, width * channels);*/
            }
            else
                return "☺";
        } while (1);
    }

    static void applyFilter(Image& importimg, Image& tempimg, const Filter& const filter)
    {
        std::string       type, width, height, RGB;
        importimg.data >> type >> width >> height >> RGB;

        tempimg.smartCreate();
        tempimg.data << type << std::endl
            << width << ' ' << height << std::endl
            << RGB << std::endl;
        
        std::string red = "", green = "", blue = "";
        int         r = 0, g = 0, b = 0;
        while (importimg.data >> red >> green >> blue)
        {
            std::stringstream _red(red);
            std::stringstream _green(green);
            std::stringstream _blue(blue);

            _red >> r;
            _green >> g;
            _blue >> b;

            filter(r, g, b);

            tempimg.data << r << " " << g << " " << b << std::endl;
        }
    }
};

#endif INTERFACE_H