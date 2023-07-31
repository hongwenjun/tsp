#include <Windows.h>
#include <oleauto.h>
#include <string.h>
#include "lyvba.h"
#include "utf8.h"

#define MAX_LINE_LENGTH 1024
static int api_count = 0;
BSTR pbs = NULL;

BSTR CharToBSTR(const char* str);
void load_lang_file(const char* filename);
bool init_translations();

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
    if (!(api_count)) {
        init_translations();
        api_count++;
    }

    if (code == 2052) {
        string key = string((char*)english);
        auto it = translations.find(key);
        if (it != translations.end()) {
            return CharToBSTR(it->second.c_str());
        }
    }
    return CharToBSTR((char*)english);
}

BSTR CharToBSTR(const char* str)
{
    if (api_count > 2) SysFreeString(pbs);

    // 获取char*字符串的长度（以字节为单位）
    int len = strlen(str);

    // 分配BSTR字符串的内存（按字节分配）
    BSTR bstr = SysAllocStringByteLen(nullptr, len);

    // 将char*字符串的内容逐字节复制到BSTR字符串中
    memcpy(bstr, str, len);

    pbs =  bstr;

    return bstr;
}

bool init_translations()
{
    if (api_count)
        return true;
    char filename[256] = "";
    get_dll_dir(filename);
    strcat(filename, "\\lang_cn.ini");

    if (IsFileExist(filename)) {
        load_lang_file(filename);
        //    MessageBoxA(NULL, filename, "Language File", MB_OK);
    }
    return true;
}

void load_lang_file(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        // 清空DLL内置字典，再从文件中加载
        translations.erase(translations.begin(), translations.end());

        char line[MAX_LINE_LENGTH];
        char gbk_line[MAX_LINE_LENGTH];
        memset(line, 0, MAX_LINE_LENGTH);
        memset(gbk_line, 0, MAX_LINE_LENGTH);

        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            utf8_to_gb(line, gbk_line, strlen(line));

            char* key = strtok(gbk_line, "=");
            char* value = strtok(NULL, "\n");
            if (key != NULL && value != NULL) {
                translations.insert(std::pair<string, string>(string(key), string(value)));
            }
        }
        fclose(file);
    } else {
        fprintf(stderr, "Failed to open language file: %s\n", filename);
    }
}
