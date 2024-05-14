import vtk

colors = vtk.vtkNamedColors()

tri = vtk.vtkTriangle()
tri.GetPoints().SetPoint(0, 0.0, 0.0, 0.0)
tri.GetPoints().SetPoint(1, 1.0, 0.0, 0.0)
tri.GetPoints().SetPoint(2, 0.0, 1.0, 0.0)
tri.GetPointIds().SetId(0, 0)
tri.GetPointIds().SetId(1, 1)
tri.GetPointIds().SetId(2, 2)

ca = vtk.vtkCellArray()
ca.InsertNextCell(tri)

pd = vtk.vtkPolyData()
# this is for the geometry part
pd.SetPoints(tri.GetPoints())
# this is for the topology part
pd.SetPolys(ca) # add the triangle cell to data set
#pd.SetVerts(ca) # or just add the vertex cells

mapper = vtk.vtkPolyDataMapper()
mapper.SetInputData(pd)

actor = vtk.vtkActor()
actor.GetProperty().SetColor(colors.GetColor3d('PeachPuff'))
actor.SetMapper(mapper)

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
