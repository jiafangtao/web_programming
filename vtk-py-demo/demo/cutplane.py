import sys
import vtk


def main():
	script_name = sys.argv[0]
	ver = vtk.vtkVersion().GetVTKVersionFull()

	colors = vtk.vtkNamedColors()
	
	data = vtk.vtkUnstructuredGrid()

	points = vtk.vtkPoints()
	id1 = points.InsertNextPoint(6, 6, 10)
	id2 = points.InsertNextPoint(10, 10, 0)
	id3 = points.InsertNextPoint(0, 8, 0)
	id4 = points.InsertNextPoint(8, 0, 0)

	data.SetPoints(points)

	ids = vtk.vtkIdList()
	ids.InsertNextId(id1)
	ids.InsertNextId(id2)
	ids.InsertNextId(id3)
	ids.InsertNextId(id4)

	print("Ids of points are prepared")

	tet = vtk.vtkTetra()
	tet.GetPointIds().SetId(0, id1)
	tet.GetPointIds().SetId(1, id2)
	tet.GetPointIds().SetId(2, id3)
	tet.GetPointIds().SetId(3, id4)

	ary = vtk.vtkCellArray()
	ary.InsertNextCell(tet)

	data.SetCells(vtk.VTK_TETRA, ary)

	#filter = vtk.vtkGeometryFilter()
	filter = vtk.vtkDataSetSurfaceFilter()
	filter.SetInputData(data)
	filter.Update()

	mapper = vtk.vtkDataSetMapper()
	mapper.SetInputConnection(filter.GetOutputPort())

	actor = vtk.vtkActor()
	actor.GetProperty().SetColor(colors.GetColor3d('Yellow'))
	#actor.GetProperty().SetOpacity(0.50)
	actor.SetMapper(mapper)
	
	plane = vtk.vtkPlane()
	plane.SetOrigin(4, 0, 0)
	plane.SetNormal(1, 0, 0)
	cutter = vtk.vtkCutter()
	cutter.SetCutFunction(plane)
	cutter.SetInputData(actor.GetMapper().GetInput())
	cutter.Update()
 
	cutterMapper = vtk.vtkPolyDataMapper()
	cutterMapper.SetInputConnection(cutter.GetOutputPort())
	planeActor = vtk.vtkActor()
	planeActor.GetProperty().SetColor(colors.GetColor3d("Red"))
	planeActor.GetProperty().SetLineWidth(2)
	planeActor.SetMapper(cutterMapper)

	ren = vtk.vtkRenderer()
	ren.SetBackground(colors.GetColor3d('DarkGreen'))
	ren.AddActor(actor)
	ren.AddActor(planeActor)

	renderWin = vtk.vtkRenderWindow()
	renderWin.AddRenderer(ren)
	renderWin.SetSize(600, 450)

	iren = vtk.vtkRenderWindowInteractor()
	iren.SetRenderWindow(renderWin)
	iren.Initialize()
	iren.Start()


if __name__ == '__main__':
	main()
