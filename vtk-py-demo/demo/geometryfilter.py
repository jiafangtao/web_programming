import sys
import vtk

colors = vtk.vtkNamedColors()

def main():
	uGrid = vtk.vtkUnstructuredGrid()

	points = vtk.vtkPoints()
	id1 = points.InsertNextPoint(6, 6, 10)
	id2 = points.InsertNextPoint(10, 10, 0)
	id3 = points.InsertNextPoint(0, 8, 0)
	id4 = points.InsertNextPoint(8, 0, 0)
	id5 = points.InsertNextPoint(6, 6, -10)
	uGrid.SetPoints(points)
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

	ca = vtk.vtkCellArray()
	ca.InsertNextCell(tet)
	ca.InsertNextCell(tet2)

	uGrid.SetCells(vtk.VTK_TETRA, ca)
	save_ugrid_to_file("out/geomfilter_out.vtu", uGrid)
 
	show_ui(uGrid)
	
def save_ugrid_to_file(path, data):
	writer = vtk.vtkUnstructuredGridWriter()
	writer.SetFileName(path)
	writer.SetInputData(data)
	writer.Write()
	print(f"#1. data is saved to file")

def save_pdata_to_file(path, pdata):
	writer = vtk.vtkPolyDataWriter()
	writer.SetFileName(path)
	writer.SetInputDataObject(pdata)

	writer.Write()


def show_ui(uGrid):
	#filter = vtk.vtkDataSetSurfaceFilter()
	filter = vtk.vtkGeometryFilter()
	filter.SetInputData(uGrid)
	filter.Update()
	pdata = filter.GetOutput()
	save_pdata_to_file("out/geomfilter_pdata.vtp", pdata) # I know this is ...

	mapper = vtk.vtkDataSetMapper()
	mapper.SetInputConnection(filter.GetOutputPort())

	actor = vtk.vtkActor()
	actor.GetProperty().SetColor(colors.GetColor3d('Yellow'))
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


if __name__ == '__main__':
	main()
