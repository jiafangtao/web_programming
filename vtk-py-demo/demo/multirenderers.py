# multiple-renderers

from vtk import *


cylinder = vtkCylinderSource()
cylinderMapper = vtkPolyDataMapper()
cylinderMapper.SetInputConnection(cylinder.GetOutputPort())

cone = vtkConeSource()
cone.SetRadius(1.5)
cone.SetCenter(-20, 0, 0)
coneMapper = vtkPolyDataMapper()
coneMapper.SetInputConnection(cone.GetOutputPort())
 
#vtkActor
cylinderActor = vtkActor()
cylinderActor.SetMapper(cylinderMapper)

coneActor = vtkActor()
coneActor.SetMapper(coneMapper)

#coneActor->GetProperty()->SetColor(colors->GetColor3d("Bisque").GetData())

colors = vtkNamedColors()
c = colors.GetColor3d("Bisque")
coneActor.GetProperty().SetColor(c.GetRed(), c.GetGreen(), c.GetBlue())
coneActor.GetProperty().SetOpacity(0.8)

# vtkRenderer
ren1 = vtkRenderer()
ren1.AddActor(cylinderActor)

ren2 = vtkRenderer()
ren2.AddActor(coneActor)

renWin = vtkRenderWindow()
renWin.SetSize(600, 480)
renWin.SetWindowName("demo - multiple renderers")
renWin.SetNumberOfLayers(2)


renWin.AddRenderer(ren1)
ren1.SetViewport(0, 0, 0.5, 0.5)
ren1.SetBackground(1, 0, 0)
ren1.SetLayer(0)

renWin.AddRenderer(ren2)
ren2.SetViewport(0.5, 0.5, 1.0, 1.0)
#ren2.SetInteractive(False)
ren2.SetLayer(1)

print(f"Layer: {ren1.GetLayer()}, {ren2.GetLayer()}")

# vtkRenderWindowInteractor 
iren = vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

renWin.Render()
iren.Start()
