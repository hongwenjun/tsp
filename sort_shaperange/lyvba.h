#ifndef LYVBA_H_INCLUDED
#define LYVBA_H_INCLUDED


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
  area
};


#endif // LYVBA_H_INCLUDED
