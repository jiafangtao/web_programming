from vtk import (
    vtkCylinderSource, 
    vtkConeSource, 
    vtkPolyDataMapper,  
    vtkJPEGWriter,
    vtkWindowToImageFilter,
    vtkRenderWindowInteractor,
    vtkRenderer,
    vtkRenderWindow,
    vtkActor
)

ren = vtkRenderer()
renWin = vtkRenderWindow()

renWin.AddRenderer(ren)
iren = vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

cylinder = vtkCylinderSource()
print(f"cylinder center: {cylinder.GetCenter()}")

cylinderMapper = vtkPolyDataMapper()
cylinderMapper.SetInputConnection(cylinder.GetOutputPort())

cone = vtkConeSource()
cone.SetRadius(1.5)
print(f"cone center: {cone.GetCenter()}")

cone.SetCenter(-2, 0, 0)
print(f"cone center: {cone.GetCenter()}")

coneMapper = vtkPolyDataMapper()
coneMapper.SetInputConnection(cone.GetOutputPort())

actor = vtkActor()
actor.SetMapper(cylinderMapper)

ren.AddActor(actor)
renWin.Render()

filter = vtkWindowToImageFilter() 
filter.SetInput(renWin)

filter.Update()

writer = vtkJPEGWriter()
writer.AddInputConnection(filter.GetOutputPort())

writer.SetFileName("result.jpeg")
writer.Write()

iren.Initialize()
iren.Start()

print("done writing to jpeg file.")
