Attribute VB_Name = "ALGO"
'// Algorithm 模块
Private Declare PtrSafe Function SortByItem Lib "C:\TSP\lyvba.dll" (ByRef sr_Array As ShapeProperties, ByVal size As Long, _
                      ByVal Sort_By As SortItem, ByRef ret_Array As Long) As Long

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

Sub 测试排序_ShapeRange()
  API.BeginOpt
  Dim sr As ShapeRange, ssr As ShapeRange
  Dim s As Shape
  Set sr = ActiveSelectionRange
  Set ssr = ShapeRange_To_Sort_Array(sr, stty)
  For Each s In ssr
    s.OrderToFront
  Next s

  API.EndOpt
  MsgBox "ShapeRange_SortItem:" & stty & " 枚举值"
  TSP.TSP_TO_DRAW_LINE
End Sub

'// 映射 ShapeRange 到 Array 然后调用 DLL库排序
Private Function ShapeRange_To_Sort_Array(ByVal sr As ShapeRange, ByVal Sort_By As SortItem) As ShapeRange
On Error GoTo ErrorHandler
  Dim sp As ShapeProperties
  Dim size As Long, ret As Long
  Dim s As Shape
  size = sr.Count
  
  Dim sr_Array() As ShapeProperties
  Dim ret_Array() As Long
  ReDim ret_Array(1 To size)
  ReDim sr_Array(1 To size)
  
  For Each s In sr
    sp.Item = sr.IndexOf(s)
    sp.StaticID = s.StaticID
    sp.lx = s.LeftX: sp.rx = s.RightX
    sp.by = s.BottomY: sp.ty = s.TopY
    sp.cx = s.CenterX: sp.cy = s.CenterY
    sp.sw = s.SizeWidth: sp.sh = s.SizeHeight
    sr_Array(sp.Item) = sp
  Next s

  '// 在VBA中数组的索引从1开始, 将数组的地址传递给函数需要Arr(1)方式
  '// C/C++ 函数定义 int __stdcall SortByItem(ShapeProperties* sr_Array, int size, SortItem Sort_By, int* ret_Array)
  '// sr_Array首地址，size 长度， Sort_By 排序方式, 返回数组 ret_Array
  ret = SortByItem(sr_Array(1), size, Sort_By, ret_Array(1))
  
  Debug.Print ret, size
  If ret = size Then
    Dim srcp As New ShapeRange, i As Integer
    For i = 1 To size
      srcp.Add sr(ret_Array(i))
      Debug.Print i
    Next i
    
    Set ShapeRange_To_Sort_Array = srcp
  End If
  
ErrorHandler:

End Function


'// 导出ShapeRange信息到数据文件: 初始的版本
Private Function Store_ShapeRange()
  Open "C:\TSP\Stored.dat" For Binary Access Write As #168

  ActiveDocument.Unit = cdrMillimeter
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


