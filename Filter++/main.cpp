//#define __STDC_LIB_EXT1__
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"

#include "interface.h"
namespace fs = std::filesystem;

int main()
{
    std::cout << "Choose an image:\n";
    /*do
    {
        GetKeyState('A');
    } while (1);*/

    // Importing file, it's information
    Image importimg(Interface::openFile(), false);
    importimg.open();
    std::string       type,   width,   height,   RGB;
    importimg.data >> type >> width >> height >> RGB;

    // Choosing a filter
    Filter filter = Interface::chooseFilter();

    // Creating temporary file, loading information
    Image tempimg(fs::current_path().string() + "\\randomname.ppm", true);
    tempimg.smartOpen();
    tempimg.data << type << std::endl
                 << width << ' ' << height << std::endl
                 << RGB << std::endl;

    // Filtering
    Interface::applyFilter(importimg, tempimg, filter);

    // Exporting file
    std::string exportPath = Interface::saveFile(tempimg);
    if (fs::exists(exportPath))
        fs::copy(tempimg.path, exportPath, fs::copy_options::overwrite_existing);
    else
        fs::copy(tempimg.path, exportPath);

    return 0;
}