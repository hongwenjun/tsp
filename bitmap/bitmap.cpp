#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <string>

int  GetFilePath(HWND hWnd, char* szFile);
char* GetAppDir(char* szPath);

int main(int argc, char* argv[])
{
    const char* filename;
    char* fbuf = new char[1024];
    GetFilePath(0, fbuf);
    filename = fbuf;
    fputs(filename, stderr);

    char* szPath = new char[1024];
    GetAppDir(szPath);

    std::string Bitmap_PY = std::string(szPath) + "\\BITMAP.py " + filename ;
//  system(Bitmap_PY.c_str());
    ShellExecute(0, "", "pythonw", Bitmap_PY.c_str(), "", SW_HIDE);

    return 0;
}

int   GetFilePath(HWND hWnd, char* szFile)
{

    OPENFILENAME ofn;       // common dialog box structure
    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = szFile;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 260; // 本来sizeof(szFile);
    ofn.lpstrFilter = "点阵图文件(*.png;*.tif;*.jpg)\0*.png;*.tif;*.jpg\0\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box.
    GetOpenFileName(&ofn);
    return   lstrlen(szFile);
}

// 功能 获得当前路径
char* GetAppDir(char* szPath)
{
    char* ret = szPath;
    GetModuleFileName(NULL, szPath, MAX_PATH); // 得到当前执行文件的文件名（包含路径）
    *(strrchr(szPath, '\\')) = '\0';    // 删除文件名，只留下目录
    return ret;
}
