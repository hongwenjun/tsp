Attribute VB_Name = "ALGO"
'// Algorithm 模块
Private Declare PtrSafe Function SortByItem Lib "C:\TSP\lyvba.dll" (ByVal Stored_File As String, ByVal Sort_By As SortItem) As Long

Type ShapeProperties
  Item As Long                 '// ShapeRange.Item
  StaticID As Long             '// Shape.StaticID
  lx As Double: rx As Double   '// s.LeftX  s.RightX  s.BottomY  s.TopY
  by As Double: ty As Double
  cx As Double: cy As Double   '// s.CenterX  s.CenterY s.SizeWidth s.SizeHeight
  sw As Double: sh As Double
End Type

Enum SortItem
  stlx
  strx
  stby
  stty
  stcx
  stcy
  stsw
  stsh
  Area
End Enum

Sub 测试写文件_Store_ShapeRange()
  Store_ShapeRange
  
  Dim filename As String
  filename = "C:\TSP\Stored.dat"
  ret = SortByItem(filename, cx)
  Debug.Print ret
End Sub


'// 导出节点信息到数据文件
Private Function Store_ShapeRange()
  Open "C:\TSP\Stored.dat" For Binary Access Write As #168

  Dim sp As ShapeProperties
  Dim str As String, size As Long
  Dim s As Shape, sr As ShapeRange
  Set sr = ActiveSelectionRange
  
  '// SR 选择物件总数量
  size = sr.Count
  Put #168, , size
  
  For Each s In sr
    sp.Item = sr.IndexOf(s)
    sp.StaticID = s.StaticID
    sp.lx = s.LeftX: sp.rx = s.RightX
    sp.by = s.BottomY: sp.ty = s.TopY
    sp.cx = s.CenterX: sp.cy = s.CenterY
    sp.sw = s.SizeWidth: sp.sh = s.SizeHeight

    Put #168, , sp
  Next s

  Close #168
End Function

