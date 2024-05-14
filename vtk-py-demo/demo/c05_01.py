from vtk import *

canvas = vtkImageCanvasSource2D()
canvas.SetScalarTypeToUnsignedChar()
canvas.SetNumberOfScalarComponents(1)
canvas.SetExtent(0, 100, 0, 100, 0, 0)
canvas.SetDrawColor(0, 255, 0, 0.6)
canvas.FillBox(0, 100, 0, 100)

canvas.SetDrawColor(255, 0, 0, 0)
canvas.FillBox(20, 40, 20, 40)
#canvas.Update()

mapper = vtkImageSliceMapper()
mapper.SetInputConnection(canvas.GetOutputPort())

actor = vtkImageActor()
actor.SetMapper(mapper)

ren = vtkRenderer()
renWin = vtkRenderWindow()
renWin.SetSize(400, 300)
renWin.AddRenderer(ren)

ren.AddActor(actor)

iren = vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

iren.Render()

iren.Initialize()
iren.Start()
