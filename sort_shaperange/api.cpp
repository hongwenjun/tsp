#include <Windows.h>
#include "lyvba.h"

// 检查一个文件是否存在
BOOL IsFileExist(LPCTSTR lpFileName)
{
    WIN32_FIND_DATA fd = {0};
    HANDLE hFind = FindFirstFile(lpFileName, &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        FindClose(hFind);
    }
    return ((hFind != INVALID_HANDLE_VALUE) && !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}


// 功能 获得当前路径
char* get_dll_dir(char* szPath)
{
    HMODULE hModule = GetModuleHandle("lyvba.dll");

    char* ret = szPath;
    if (hModule != NULL) {

        GetModuleFileName(hModule, szPath, MAX_PATH); // 得到当前执行文件的文件名（包含路径）
        *(strrchr(szPath, '\\')) = '\0';    // 删除文件名，只留下目录
    }
    return ret;
}
