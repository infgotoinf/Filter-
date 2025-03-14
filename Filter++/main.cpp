#include <iostream>
#include <fstream>

using std::ifstream, std::ofstream, std::fstream;

std::string const folder = "ppms\\";

struct Image
{
    std::string name;
    bool exists;
    fstream data;

    Image(std::string name)
        : name(name), data(name + ".ppm")
    { }

    ~Image() {
        data.close();
    }
};

struct Pixel
{
    unsigned char r = 0, g = 0, b = 0;
};


int main()
{
    Image imgImport(folder + "bird2");

    std::string type, width, height, RGB;
    imgImport.data >> type >> width >> height >> RGB;

    Image imgExport("1");
    imgExport.data << type << '\n'
                << width << ' ' << height << '\n'
                << RGB << '\n';


    std::string red = "", green = "", blue = "";
    int r = 0, g = 0, b = 0;
    while (!imgImport.data.eof())
    {
        imgImport.data >> red >> green >> blue;
        
        std::stringstream _red(red);
    }
    return 0;
}