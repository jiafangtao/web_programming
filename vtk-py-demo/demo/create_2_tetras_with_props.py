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
	save_data_to_file_1("tet_2_out.vtu", data)

	
def save_data_to_file_1(path, data):
	writer = vtk.vtkUnstructuredGridWriter()
	writer.SetFileName(path)
	writer.SetInputData(data)
	writer.Write()
	print(f"#1. data is saved to file")


if __name__ == '__main__':
	main()
