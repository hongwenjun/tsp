#ifndef LYVBA_H_INCLUDED
#define LYVBA_H_INCLUDED
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using std::vector;
using std::sort;
using std::string;
using std::map;

typedef struct ShapeProperties {
    int Item;          // ShapeRange.Item
    int StaticID;      // Shape.StaticID
    double lx, rx;      // s.LeftX  s.RightX  s.BottomY  s.TopY
    double by, ty;
    double cx, cy;      // s.CenterX  s.CenterY s.SizeWidth s.SizeHeight
    double sw, sh;
}SHPS;

enum SortItem {
  stlx,
  strx,
  stby,
  stty,
  stcx,
  stcy,
  stsw,
  stsh,
  area,
  topWt_left
};



// Private Declare PtrSafe Function SortByItem Lib "C:\TSP\lyvba.dll" (ByVal Stored_File As String, ByVal Sort_By As SortItem) As Long
extern "C" __declspec(dllexport)
int __stdcall sort_byitem(ShapeProperties* sr_Array, int size, SortItem Sort_By, int* ret_Array);

//  i18n 是指国际化 Internationalization 的缩写，是一种让软件可以轻松适应不同语言和地区的技术。
extern "C" __declspec(dllexport) BSTR __stdcall i18n(BSTR english, int code);


// 功能 获得当前路径和获得当前路径
char* get_dll_dir(char* szPath);
BOOL IsFileExist(LPCTSTR lpFileName);



#endif // LYVBA_H_INCLUDED
