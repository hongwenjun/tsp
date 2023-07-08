#ifndef LYVBA_H_INCLUDED
#define LYVBA_H_INCLUDED


typedef struct ShapeProperties {
    long Item;          // ShapeRange.Item
    long StaticID;      // Shape.StaticID
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
  area
};

extern "C" __declspec(dllexport)
int __stdcall SortByItem(char* Stored_File, SortItem Sort_By);



#endif // LYVBA_H_INCLUDED
