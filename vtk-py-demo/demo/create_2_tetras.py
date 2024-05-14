import sys
import vtk

g_show_ui = False
g_save_to_file = True



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
	id5 = points.InsertNextPoint(6, 6, -10)

	data.SetPoints(points)

	'''
	ids = vtk.vtkIdList()
	ids.InsertNextId(id1)
	ids.InsertNextId(id2)
	ids.InsertNextId(id3)
	ids.InsertNextId(id4)
	'''

	print("Ids of points are prepared")

	tet = vtk.vtkTetra()
	tet.GetPointIds().SetId(0, id1)
	tet.GetPointIds().SetId(1, id2)
	tet.GetPointIds().SetId(2, id3)
	tet.GetPointIds().SetId(3, id4)

	tet2 = vtk.vtkTetra()
	tet2.GetPointIds().SetId(0, id5)
	tet2.GetPointIds().SetId(1, id2)
	tet2.GetPointIds().SetId(2, id3)
	tet2.GetPointIds().SetId(3, id4)


	ary = vtk.vtkCellArray()
	ary.InsertNextCell(tet)
	ary.InsertNextCell(tet2)

	data.SetCells(vtk.VTK_TETRA, ary)
	

	if g_save_to_file:
		save_data_to_file_1("tet_2_out.vtu", data)

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


def save_data_to_file_1(path, data):
	writer = vtk.vtkUnstructuredGridWriter()
	writer.SetFileName(path)
	writer.SetInputData(data)
	writer.Write()
	print(f"#1. data is saved to file")


if __name__ == '__main__':
	main()
