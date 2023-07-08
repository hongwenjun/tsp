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


extern "C" {

// Private Declare PtrSafe Function SortByItem Lib "C:\TSP\lyvba.dll" (ByVal Stored_File As String, ByVal Sort_By As SortItem) As Long
    int __stdcall SortByItem(char* Stored_File, SortItem Sort_By)
    {
        FILE* fp = fopen(Stored_File, "rb");
        if (fp == NULL) {fputs("File error", stderr); exit(1);}

        int size = 0;
        int ret;
        struct ShapeProperties sp;
        SortItem sby = Sort_By;

        std::vector <struct ShapeProperties> srvec;
        auto it = srvec.begin();

        fseek(fp, 0, SEEK_SET);
        fread(&size, 4, 1, fp);

        FILE* pFile;
        pFile = fopen("C:\\TSP\\myfile.txt", "w");

        fprintf(pFile, "Stored_File: %s  Sort_By: %d  %d\n", Stored_File, sby, size);

        for (auto i = 0 ; i != size; i++) {
            fread(&sp, sizeof(ShapeProperties), 1, fp);
            //   fprintf(pFile, "%d %d \n%lf %lf %lf %lf \n%lf %lf %lf %lf \n",
            //           sp.Item, sp.StaticID, sp.lx, sp.rx, sp.by, sp.ty, sp.cx, sp.cy, sp.sw, sp.sh);
            srvec.push_back(sp);
        }

        // 使用 std::sort 对 vector 进行排序
        std::sort(srvec.begin(), srvec.end(), area_cmp);

        // 遍历 vector 输出排序后的结果
        for (const auto& sh : srvec) {
            fprintf(pFile, "%d  %lf %lf \n", sh.Item, sh.lx, sh.cx);
        }

        fclose(pFile);
        fclose(fp);

        return size;
    }


//  Private Declare PtrSafe Function SayHello Lib "C:\TSP\lyvba.dll" (ByVal name As String) As Long
    void __stdcall SayHello(char* name)
    {
        MessageBoxA(NULL, name, "Greetings", MB_OK);
    }

}
