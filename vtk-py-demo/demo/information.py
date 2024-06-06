from vtk import *

info = vtkInformation()

k = vtkInformationIntegerKey()
k = vtkInformationIntegerKey.MakeKey("test", "level_1")
