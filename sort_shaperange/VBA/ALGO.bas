Attribute VB_Name = "ALGO"
'// Algorithm ģ��
#If VBA7 Then
'// For CorelDRAW X6-2023  62bit
Private Declare PtrSafe Function SortByItem Lib "C:\TSP\lyvba.dll" (ByRef sr_Array As ShapeProperties, ByVal size As Long, _
                      ByVal Sort_By As SortItem, ByRef ret_Array As Long) As Long
#Else
'// For CorelDRAW X4  32bit
Declare Function sort_byitem Lib "C:\TSP\lyvba32.dll" (ByRef sr_Array As ShapeProperties, ByVal size As Long, _
                      ByVal Sort_By As SortItem, ByRef ret_Array As Long) As Long
#End If

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

Sub ��������_ShapeRange()
  Dim sr As ShapeRange, ssr As ShapeRange
  Dim s As Shape
  Set sr = ActiveSelectionRange
  Set ssr = ShapeRange_To_Sort_Array(sr, stlx)

  Set ssr = ShapeRange_To_Sort_Array(ssr, stby)
  
  '// s ��������
  For Each s In ssr
    s.OrderToFront
  Next s

'  MsgBox "ShapeRange_SortItem:" & stlx & " ö��ֵ"
  TSP.TSP_TO_DRAW_LINE
End Sub

'// ӳ�� ShapeRange �� Array Ȼ����� DLL������
Private Function ShapeRange_To_Sort_Array(ByVal sr As ShapeRange, ByVal Sort_By As SortItem) As ShapeRange
' On Error GoTo ErrorHandler
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

  '// ��VBA�������������1��ʼ, ������ĵ�ַ���ݸ�������ҪArr(1)��ʽ
  '// C/C++ �������� int __stdcall SortByItem(ShapeProperties* sr_Array, int size, SortItem Sort_By, int* ret_Array)
  '// sr_Array�׵�ַ��size ���ȣ� Sort_By ����ʽ, �������� ret_Array
  ret = sort_byitem(sr_Array(1), size, Sort_By, ret_Array(1))
  
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


