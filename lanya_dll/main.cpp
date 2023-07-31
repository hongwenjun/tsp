#include <windows.h>
#include <stdio.h>
#include "lyvba.h"

bool srvec_sort_by_item(vector<ShapeProperties>& srvec, SortItem Sort_By);

extern "C" __declspec(dllexport)
int __stdcall sort_byitem(ShapeProperties* sr_Array, int size, SortItem Sort_By, int* ret_Array)
{
    vector <ShapeProperties> srvec;
    // vector 容器装载 ShapeProperties* sr_Array
    for (auto i = 0 ; i != size; i++) {
        srvec.push_back(*sr_Array);
        sr_Array++;
    }

    // 排序 按 SortItem 项目
    bool sort_flage = srvec_sort_by_item(srvec, Sort_By);
    if (sort_flage) {
        for (auto it = srvec.begin(); it != srvec.end(); it++) {
            *ret_Array = it->Item;
            ret_Array++;
        }
    }
    return size;
}

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
bool topWt_left_cmp(const SHPS& shape1, const SHPS& shape2) {return shape1.ty*100 - shape1.lx > shape2.ty*100  - shape2.lx;}

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
    case topWt_left:
        sort(srvec.begin(), srvec.end(), topWt_left_cmp);
        break;
    default:
        break;
    }
    bool ret = true;
    return ret;
}

