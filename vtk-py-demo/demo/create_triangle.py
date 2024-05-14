import sys
import vtk

g_show_ui = False
g_save_to_file = True


def main():
	script_name = sys.argv[0]
	ver = vtk.vtkVersion().GetVTKVersionFull()

	colors = vtk.vtkNamedColors()
	
	data = vtk.vtkPolyData()

	points = vtk.vtkPoints()
	id1 = points.InsertNextPoint(5, 5, 0)
	id2 = points.InsertNextPoint(10, 10, 0)
	id3 = points.InsertNextPoint(0, 10, 0)

	data.SetPoints(points)

	ids = vtk.vtkIdList()
	ids.InsertNextId(id1)
	ids.InsertNextId(id2)
	ids.InsertNextId(id3)

	print("Ids of points are prepared")

	tri = vtk.vtkTriangle()
	tri.GetPointIds().InsertNextId(id1)
	tri.GetPointIds().InsertNextId(id2)
	tri.GetPointIds().InsertNextId(id3)


	ary = vtk.vtkCellArray()
	ary.InsertNextCell(tri)

	data.SetPolys(ary)

	ptColors = vtk.vtkUnsignedCharArray()
	ptColors.SetNumberOfComponents(3)
	ptColors.InsertNextTuple3(255, 0, 0)
	ptColors.InsertNextTuple3(0, 255, 0)
	ptColors.InsertNextTuple3(0, 0, 255)
	data.GetPointData().SetScalars(ptColors)

	cellColors = vtk.vtkUnsignedCharArray()
	cellColors.SetNumberOfComponents(3)
	cellColors.InsertNextTuple3(0, 225, 0)

	data.GetCellData().SetScalars(cellColors)

	if g_save_to_file:
		save_polydata_to_file("triangle_out.vtp", data)

	if not g_show_ui:
		print("Not going to show UI. Quit now.")
		return

	mapper = vtk.vtkPolyDataMapper()
	mapper.SetInputData(data)

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


def save_polydata_to_file(path, polydata):
	print(f"going to save data to {path}...")
	writer = vtk.vtkPolyDataWriter()
	writer.SetFileName(path)
	writer.SetInputData(polydata)
	writer.Write()
	print(f"data is saved to file")


if __name__ == '__main__':
	main()
