//#define __STDC_LIB_EXT1__
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"

#include "interface.h"
namespace fs = std::filesystem;

int main()
{
    beginning:
    int choice;
    do {
        std::cout << "1: Import image \n";
        std::cin >> choice;
        system("cls");
    } while (choice != 1);

    Filter filter;

    // Importing file, it's information
    std::string importingPath = Interface::openFile();
    if (importingPath == "☺")
    {
        system("cls");
        std::cout << "You didn't choose an image\n";
        goto beginning;
    }
    Image importimg(importingPath, false);
    importimg.open();

    // Creating temporary file, loading information
    Image tempimg(fs::current_path().string() + "\\randomname.ppm", true);

    std::string type, width, height, RGB;
    int counter = 1;

    do {
        std::cout << "1: Import image\n";
        std::cout << "2: Add filter\n";
        std::cout << "3: Export image" << std::endl;
        std::cin >> choice;

        switch (choice)
        {
        case 1: // Import image
            // Importing file, it's information
            importingPath = Interface::openFile();
            if (importingPath == "☺")
            {
                system("cls");
                std::cout << "You didn't choose an image\n";
                break;
            }
            importimg.data.close();
            importimg(importingPath, false);
            importimg.open();

            // Creating temporary file, loading information
            tempimg(fs::current_path().string() + "\\randomname.ppm", true);

            counter = 1;
            system("cls");
            std::cout << "New image imported\n";
            break;
        case 2: // Add filter
            // Choosing a filter
            filter = chooseFilter();

            // Filtering
            if (counter > 1)
            {
                importimg.data.close();
                importimg(tempimg.path, true);
                importimg.open();
                tempimg.data.close();
                tempimg(fs::current_path().string() + "\\randomname" + std::to_string(counter) + ".ppm", true);
            }
            importimg.data >> type >> width >> height >> RGB;

            tempimg.smartCreate();
            tempimg.data << type << std::endl
                         << width << ' ' << height << std::endl
                         << RGB << std::endl;
            Interface::applyFilter(importimg, tempimg, filter);

            system("cls");
            std::cout << "Filter was added\n";
            counter++;
            break;
        case 3: //Export image
            // Exporting file
            std::string exportPath = Interface::saveFile(tempimg);
            if (exportPath == "☺") {
                system("cls");
                std::cout << "You didn't choose a path\n";
                break;
            }
            else if (fs::exists(exportPath))
                fs::copy(tempimg.path, exportPath, fs::copy_options::overwrite_existing);
            else
                fs::copy(tempimg.path, exportPath);

            return 0;
        }
    } while (1);

    return 0;
}