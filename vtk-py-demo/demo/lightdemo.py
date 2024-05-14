import vtk


light = vtk.vtkLight()
print(f'Light - pos: {light.GetPosition()}')
print(f'      - focal: {light.GetFocalPoint()}')

light2 = vtk.vtkLight()
light2.SetColor(0, 0.6, 0.6)
#light2.SetFocalPoint()
light2.SetPosition(10, 10, -100)
light2.SetAmbientColor(1, 0, 0)


source = vtk.vtkSphereSource()
source.SetRadius(0.1)

mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(source.GetOutputPort())

actor = vtk.vtkActor()
actor.SetMapper(mapper)

ren = vtk.vtkRenderer()
ren.AddLight(light)
ren.AddLight(light2)

ren.AddActor(actor)

renderWin = vtk.vtkRenderWindow()
renderWin.AddRenderer(ren)

renderWin.SetSize(600, 450)

camera = ren.GetActiveCamera()
pos = camera.GetPosition()
print(f'camera - pos: {pos}')

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renderWin)

iren.Initialize()
iren.Start()
