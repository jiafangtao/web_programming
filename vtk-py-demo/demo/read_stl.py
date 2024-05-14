import sys
import vtk


script_name = sys.argv[0]
colors = vtk.vtkNamedColors()
ver = vtk.vtkVersion().GetVTKVersionFull()

reader = vtk.vtkSTLReader()
reader.SetFileName("d:\\temp\\output.stl")

mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(reader.GetOutputPort())

actor = vtk.vtkActor()
actor.GetProperty().SetColor(colors.GetColor3d('PeachPuff'))
actor.SetMapper(mapper)

ren = vtk.vtkRenderer()
ren.SetBackground(colors.GetColor3d('DarkGreen'))
ren.AddActor(actor)

renderWin = vtk.vtkRenderWindow()
renderWin.AddRenderer(ren)
renderWin.SetSize(600, 450)

print(f"window name: {renderWin.GetWindowName()}")
renderWin.SetWindowName(f"Demo - {script_name} (vtk {ver})")

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renderWin)
iren.Initialize()
iren.Start()
