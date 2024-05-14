from vtk import *

coneSource = vtkConeSource()
coneSource.Update()

cone = coneSource.GetOutput()

nPts = cone.GetNumberOfPoints()
nCells = cone.GetNumberOfCells()

print(f'points: {nPts}, cells: {nCells}')
