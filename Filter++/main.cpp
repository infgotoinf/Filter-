#include <windows.h>
#include <iostream>
#include <cstdlib>
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
    std::string path;
    std::fstream data;

    Image(std::string path)
        : path(path)
    {}
    Image()
    {
        FILE* f;
        tmpfile_s(&f);
        data = std::fstream(f);
    }
    ~Image() {
        data.close();
    }

    void open() {
        data.open(path, std::ios::in);
    }
    void create() {
        data.open(path, std::ios::out);
    }
    void smartOpen() {
        if (fs::exists(path)) fs::remove(path);
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
    // Importing file
    Image importimg(openFile());
    importimg.open();
    std::string type, width, height, RGB;
    importimg.data >> type >> width >> height >> RGB;

    char name1[L_tmpnam_s];
    tmpnam_s(name1, L_tmpnam_s);

    auto filter = chooseFilter();

    Image tempimg(std::string(name1) + "\b\b.ppm");
    tempimg.create();
    std::cout << tempimg.path;
    /*Image tempimg(saveFile());
    tempimg.smartOpen();*/
    tempimg.data << type << std::endl
                      << width << ' ' << height << std::endl
                      << RGB << std::endl;

    std::string red = "", green = "", blue = "";
    int         r   = 0,  g     = 0,  b    = 0;
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
    // Exporting file
    fs::copy(tempimg.path, saveFile());

    return 0;
}