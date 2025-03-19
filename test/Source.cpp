#include <windows.h>
#include <iostream>

//#include <stdio.h>
//
//int main()
//{
//    OPENFILENAME ofn = { sizeof(OPENFILENAME) };
//
//    WCHAR szFile[_MAX_PATH] = L"name";
//    const WCHAR szExt[] = L"ext\0"; // extra '\0' for lpstrFilter
//
//    ofn.hwndOwner = GetConsoleWindow();
//    ofn.lpstrFile = szFile; // <--------------------- initial file name
//    ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
//    ofn.lpstrFilter = ofn.lpstrDefExt = szExt;
//    ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
//
//    if (GetSaveFileName(&ofn))
//    {
//        printf("save-as  '%s'\n", ofn.lpstrFile);
//        printf("filename '%s'\n", ofn.lpstrFile + ofn.nFileOffset);
//    }
//}

int main()
{
	OPENFILENAME ofn = { sizeof(OPENFILENAME) };

	WCHAR szFile[_MAX_PATH];
	ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize		= sizeof(ofn);
    ofn.hwndOwner		= GetConsoleWindow();
    ofn.lpstrFile		= szFile;
    ofn.lpstrFile[0]	= '\0';
    ofn.nMaxFile		= sizeof(szFile);
    ofn.lpstrFilter		=
        L"Image (*.png;*.bmp;*.jpg;*.ppm)\0*.png;*.bmp;*.jpg;*.ppm\0\
		PNG (*.png)\0*.png\0\
		BMP (*.bmp)\0*.bmp\0\
		JPG (*.jpg)\0*.jpg\0\
		PPM (*.ppm)\0*.ppm\0\0";
    ofn.nFilterIndex	= 1;
    ofn.lpstrFileTitle	= NULL;
    ofn.nMaxFileTitle	= 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags			= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		std::wcout << szFile << std::endl;
	}
	else
	{
		std::cout << "File was not opened";
	}

	return 0;
}