#include <windows.h>
#include <stdio.h>
#include "lyvba.h"
#include <vector>
#include <algorithm>

// SortItem 排序项目 比较函数
bool lx_cmp(const SHPS& shape1, const SHPS& shape2) {return shape1.lx < shape2.lx;}
bool rx_cmp(const SHPS& shape1, const SHPS& shape2) {return shape1.rx < shape2.rx;}
bool by_cmp(const SHPS& shape1, const SHPS& shape2) {return shape1.by < shape2.by;}
bool ty_cmp(const SHPS& shape1, const SHPS& shape2) {return shape1.ty < shape2.ty;}
bool cx_cmp(const SHPS& shape1, const SHPS& shape2) {return shape1.cx < shape2.cx;}
bool cy_cmp(const SHPS& shape1, const SHPS& shape2) {return shape1.cy < shape2.cy;}
bool sw_cmp(const SHPS& shape1, const SHPS& shape2) {return shape1.sw < shape2.sw;}
bool sh_cmp(const SHPS& shape1, const SHPS& shape2) {return shape1.sh < shape2.sh;}
bool area_cmp(const SHPS& shape1, const SHPS& shape2) {return shape1.sw * shape1.sh < shape2.sw * shape2.sh;}

using std::vector;
using std::sort;
bool srvec_sort_by_item(vector<ShapeProperties>& srvec, SortItem Sort_By);

// Private Declare PtrSafe Function SortByItem Lib "C:\TSP\lyvba.dll" (ByVal Stored_File As String, ByVal Sort_By As SortItem) As Long
extern "C" __declspec(dllexport)
int __stdcall SortByItem(ShapeProperties* sr_Array, int size, SortItem Sort_By, int* ret_Array)
{
    struct ShapeProperties sp;
    vector <ShapeProperties> srvec;
    FILE* pFile;
    pFile = fopen("C:\\TSP\\TSP.txt", "w");
    fprintf(pFile, "%d  %d\n", size, size);

    // vector 容器装载 ShapeProperties* sr_Array
    for (auto i = 0 ; i != size; i++) {
        srvec.push_back(*sr_Array);
        sr_Array++;

    }

    // 排序 按 SortItem 项目
    bool sort_flage = srvec_sort_by_item(srvec, Sort_By);

    // 遍历 vector 输出排序后的结果
    for (const auto& sh : srvec) {
        fprintf(pFile, "%lf %lf \n", sh.cx, sh.cy);
    }

    if (sort_flage) {
        FILE* fp = fopen("R:\\ret.dat", "w+");
        fprintf(fp, "%d\n", size);
        for (const auto& sh : srvec) {
            fprintf(fp, "%d ", sh.Item);
            *ret_Array = sh.Item;
            ret_Array++;
        }
        fclose(fp);
    }

    fclose(pFile);
    return size;
}


//  Private Declare PtrSafe Function SayHello Lib "C:\TSP\lyvba.dll" (ByVal name As String) As Long
void __stdcall SayHello(char* name)
{
    MessageBoxA(NULL, name, "Greetings", MB_OK);
}

bool srvec_sort_by_item(vector <struct ShapeProperties>& srvec, SortItem Sort_By)
{
    switch (Sort_By) {
    case stlx:
        sort(srvec.begin(), srvec.end(), lx_cmp);
        break;
    case strx:
        sort(srvec.begin(), srvec.end(), rx_cmp);
        break;
    case stby:
        sort(srvec.begin(), srvec.end(), by_cmp);
        break;
    case stty:
        sort(srvec.begin(), srvec.end(), ty_cmp);
        break;
    case stcx:
        sort(srvec.begin(), srvec.end(), cx_cmp);
        break;
    case stcy:
        sort(srvec.begin(), srvec.end(), cy_cmp);
        break;
    case stsw:
        sort(srvec.begin(), srvec.end(), sw_cmp);
        break;
    case stsh:
        sort(srvec.begin(), srvec.end(), sh_cmp);
        break;
    case area:
        sort(srvec.begin(), srvec.end(), area_cmp);
        break;
    default:
        break;
    }
    bool ret = true;
    return ret;
}

