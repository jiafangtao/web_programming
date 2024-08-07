import vtk
from vtk import (
    vtkActor,
    vtkLineSource,
    vtkNamedColors,
    vtkPoints,
    vtkPolyDataMapper,
)

def main():

    colors = vtkNamedColors()

    lines = vtkLineSource()
    # Create two points, P0 and P1
    p0 = [1.0, 0.0, 0.0]
    p1 = [5.0, 0.0, 0.0]
    p2 = [5.0, 5.0, 0.0]
    p3 = [10.0, 5.0, 0.0]

    lines.SetResolution(11)
    #lines.SetPoint1(p0)
    #lines.SetPoint2(p1)
    
    # draw a broken line with 4 points
    pts = vtk.vtkPoints()
    pts.InsertNextPoint(p0)
    pts.InsertNextPoint(p1)
    pts.InsertNextPoint(p2)
    pts.InsertNextPoint(p3)
    lines.SetPoints(pts)
    
    lines.Update()
    mapper = vtkPolyDataMapper()
    mapper.SetInputConnection(lines.GetOutputPort())

    actor = vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetLineWidth(2)
    actor.GetProperty().SetColor(colors.GetColor3d("Banana"))
    
    ren = vtk.vtkRenderer()
    
    ren.SetBackground(colors.GetColor3d('DarkGreen'))
    ren.AddActor(actor)

    renderWin = vtk.vtkRenderWindow()
    renderWin.AddRenderer(ren)
    renderWin.SetSize(600, 450)

    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renderWin)
    iren.Initialize()
    iren.Start()

######################
main()
