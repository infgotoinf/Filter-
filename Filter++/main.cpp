#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ios>

// Folder with all images
std::string const folder = "ppms\\";

struct Image
{
    std::string imageName;
    std::fstream imageData;

    Image(std::string imageName)
        : imageName(imageName)
    {}
    ~Image() {
        imageData.close();
    }

    void open()
    {
        imageData.open(imageName + ".ppm", std::ios::in);
    }

    void create()
    {
        imageData.open(imageName + ".ppm", std::ios::out);
    }
};

struct Interface
{


};

void deepfried(int& r, int& g, int& b)
{
    (r > 122 ? r = 255 : r = 0);
    (g > 122 ? g = 255 : g = 0);
    (b > 122 ? b = 255 : b = 0);
}

std::string chooseFile()
{
    OPENFILENAME ofn = { sizeof(OPENFILENAME) };

    WCHAR szFile[_MAX_PATH];
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize     = sizeof(ofn);
    ofn.hwndOwner       = GetConsoleWindow();
    ofn.lpstrFile       = szFile;
    ofn.lpstrFile[0]    = '\0';
    ofn.nMaxFile        = sizeof(szFile);
    ofn.lpstrFilter     =
        L"Image (*.png;*.bmp;*.jpg;*.ppm)\0*.png;*.bmp;*.jpg;*.ppm\0\
		PNG (*.png)\0*.png\0\
		BMP (*.bmp)\0*.bmp\0\
		JPG (*.jpg)\0*.jpg\0\
		PPM (*.ppm)\0*.ppm\0\0";
    ofn.nFilterIndex    = 1;
    ofn.lpstrFileTitle  = NULL;
    ofn.nMaxFileTitle   = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags           = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn))
    {
        WideCharToMultiByte(CP_ACP, 0, szFile, -1, ch, 260, NULL, NULL);
        return szFile;
    }
    else
    {
        std::cout << "File was not opened";
    }
}

int main()
{
    std::string imageName;
    std::cout << "Enter image name: ";
    std::cin >> imageName; // bird2 for example
    Image Import(folder + imageName);
    Import.open();

    std::string type, width, height, RGB;
    Import.imageData >> type >> width >> height >> RGB;

    Image Export("1");
    Export.create();
    Export.imageData << type << std::endl
                     << width << ' ' << height << std::endl
                     << RGB << std::endl;

    std::string red = "", green = "", blue = "";
    int     r   = 0,  g     = 0,  b    = 0;
    while (Import.imageData >> red >> green >> blue)
    {
        std::stringstream _red(red);
        std::stringstream _green(green);
        std::stringstream _blue(blue);

        _red >> r;
        _green >> g;
        _blue >> b;

        //function

        deepfried(r, g, b);

        Export.imageData << r << " " << g << " " << b << std::endl;
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