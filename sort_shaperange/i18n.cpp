#include <Windows.h>
#include <oleauto.h>

#include "lyvba.h"
#include <string.h>

BSTR CharToBSTR(const char* str);

map<string, string> translations = {
    {"Batch Dimension Nodes", "批量标注节点"},
    {"Shift Range", "Shift 范围标注"},
    {"Uniform", "统一尺寸"},
    {"Nodes", "节点优化"},
    {"Ctrl Expand", "Ctrl 功能扩展"},
    {"Preset Property", "预设属性"},
};

//  i18n 是指国际化（Internationalization）的缩写，是一种让软件可以轻松适应不同语言和地区的技术。
//  在代码编程中，i18n主要是指将程序中的文本和界面元素进行本地化处理，
//  使得程序可以适应不同的语言和地区，并且在用户界面上显示正确的本地化文本和格式。

extern "C" __declspec(dllexport) BSTR __stdcall i18n(BSTR english, int code)
{
    if (code == 2052) {
        string key = string((char*)english);
        auto it = translations.find(key);
        if (it != translations.end()) {
            return CharToBSTR(it->second.c_str());
        }
    }
    return english;
}

BSTR CharToBSTR(const char* str)
{
    // 获取char*字符串的长度（以字节为单位）
    int len = strlen(str);

    // 分配BSTR字符串的内存（按字节分配）
    BSTR bstr = SysAllocStringByteLen(nullptr, len);

    // 将char*字符串的内容逐字节复制到BSTR字符串中
    memcpy(bstr, str, len);

    return bstr;
}
