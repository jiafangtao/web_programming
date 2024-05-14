import vtk

pts = vtk.vtkPoints()
#verts = vtk.vtkCellArray()

pid_0 = pts.InsertNextPoint(1.0, 0.0, 0.0)
pid_1 = pts.InsertNextPoint(0.0, 0.0, 0.0)
pid_2 = pts.InsertNextPoint(0.0, 1.0, 0.0)

print(f'point ids: {pid_0}, {pid_1}, {pid_2}')

polydata = vtk.vtkPolyData()
polydata.SetPoints(pts)

#verts.InsertNextCell(1, [pid_0])
#verts.InsertNextCell(1, [pid_1])
#verts.InsertNextCell(1, [pid_2])
#polydata.SetVerts(verts)

lines = vtk.vtkCellArray()

line_0 = vtk.vtkLine()
line_0.GetPointIds().SetId(0, pid_0)
line_0.GetPointIds().SetId(1, pid_1)

line_1 = vtk.vtkLine()
line_1.GetPointIds().SetId(0, pid_1)
line_1.GetPointIds().SetId(1, pid_2)

line_2 = vtk.vtkLine()
line_2.GetPointIds().SetId(0, pid_2)
line_2.GetPointIds().SetId(1, pid_0)

lines.InsertNextCell(line_0)
lines.InsertNextCell(line_1)
lines.InsertNextCell(line_2)

polydata.SetLines(lines)


writer = vtk.vtkPolyDataWriter()
writer.SetFileName("triangleLines.vtk")
writer.SetInputDataObject(polydata)

writer.Write()
print("done writing data to file.")
