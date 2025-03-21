#include <windows.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <ios>
#include "stb_image.h"
#include "stb_image_write.h"
#include "filters.h"
namespace fs = std::filesystem; 

struct Image
{
    std::string imagePath;
    std::fstream imageData;

    Image(std::string imagePath)
        : imagePath(imagePath)
    {}
    Image()
    {
        FILE* f;
        tmpfile_s(&f);
        imageData = std::fstream(f);
    }
    ~Image() {
        imageData.close();
    }

    void open() {
        imageData.open(imagePath, std::ios::in);
    }
    void create() {
        imageData.open(imagePath, std::ios::out);
    }
    void smartOpen() {
        if (fs::exists(imagePath)) fs::remove(imagePath);
        create();
    }
};

struct Interface
{

};

std::string openFile()
{
    OPENFILENAMEA ofn = { sizeof(OPENFILENAMEA) };

    char szFile[_MAX_PATH];
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize     = sizeof(ofn);
    ofn.hwndOwner       = GetConsoleWindow();
    ofn.lpstrFile       = szFile;
    ofn.lpstrFile[0]    = '\0';
    ofn.nMaxFile        = sizeof(szFile);
    ofn.lpstrFilter     =
        "Image (*.png;*.bmp;*.jpg;*.ppm)\0*.png;*.bmp;*.jpg;*.ppm\0\
		PNG (*.png)\0*.png\0\
		BMP (*.bmp)\0*.bmp\0\
		JPG (*.jpg)\0*.jpg\0\
		PPM (*.ppm)\0*.ppm\0\0";
    ofn.nFilterIndex    = 1;
    ofn.lpstrFileTitle  = NULL;
    ofn.nMaxFileTitle   = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags           = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
        return szFile;
    else
        std::cout << "File was not opened";
}

std::string saveFile()
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
        "PNG (*.png)\0*.png\0\
		JPG (*.jpg)\0*.jpg\0\
		PPM (*.ppm)\0*.ppm\0\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    ofn.lpstrDefExt = "";

    if (GetSaveFileNameA(&ofn))
        return szFile;
    else
        std::cout << "File was not opened";
}

void (*chooseFilter())(int&, int&, int&)
{
    int choice;
    std::cout << "Choose filter:\n";
    std::cout << "1: deepfried\n";

    do {
        std::cin >> choice;
        switch (choice)
        {
        case  1: return deepfried;
        default: std::cout << "Invalid choice!" << std::endl;
        }
    } while (1);
}

int main()
{
    Image Import(openFile());
    Import.open();
    std::string type, width, height, RGB;
    Import.imageData >> type >> width >> height >> RGB;

    auto filter = chooseFilter();

    Image tempimg;

    /*Image tempimg(saveFile());
    tempimg.smartOpen();*/
    tempimg.imageData << type << std::endl
                      << width << ' ' << height << std::endl
                      << RGB << std::endl;

    std::string red = "", green = "", blue = "";
    int         r   = 0,  g     = 0,  b    = 0;
    while (Import.imageData >> red >> green >> blue)
    {
        std::stringstream _red(red);
        std::stringstream _green(green);
        std::stringstream _blue(blue);

        _red >> r;
        _green >> g;
        _blue >> b;

        filter(r, g, b);

        tempimg.imageData << r << " " << g << " " << b << std::endl;
    }

    //Image New("abc2");
    //New.create();

    //int image_width = 2;
    //int image_height = 2;

    //// Render

    //New.imageData << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    //for (int j = 0; j < image_height; j++) {
    //    for (int i = 0; i < image_width; i++) {
    //        auto r = float(i) / (image_width - 1);
    //        auto g = float(j) / (image_height - 1);
    //        auto b = 0.0;

    //        int ir = int(255.999 * r);
    //        int ig = int(255.999 * g);
    //        int ib = int(255.999 * b);

    //        New.imageData << ir << ' ' << ig << ' ' << ib << std::endl;
    //    }
    //}
    return 0;
}