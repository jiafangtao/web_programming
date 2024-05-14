from vtk import *

def demo_cell_vertex():
    vertex = vtkVertex()
    print(vertex)

    print("Dimension", vertex.GetCellDimension())
    print("Number of edges:", vertex.GetNumberOfEdges())
    print("Number of faces:", vertex.GetNumberOfFaces())

    """
    # vtkVertex doesn't verify if the user sets the underlying points correctly.
    # Instead field points and point ids are exposed by class vtkCell directly
    # for performance considerations and access convinence. So that means it's
    # the users' responsibility to use it correctly.
    pt = vtkPoints()
    pt.SetNumberOfPoints(1)
    pt.InsertNextPoint(1.0, 1.0, 1.0)
    pt.InsertNextPoint(2.0, 2.0, 2.0)
    vertex.Initialize(2, pt)
    """

    vertex.GetPoints().SetPoint(0, 3.0, 3.0, 3.0)
    
    print("after setting coordinates of the vertex ......")
    print(vertex)


def demo_cell_triangle():
    tri = vtkTriangle()
    print(tri)

    tri.GetPoints().SetPoint(1, 1.0, 0.0, 0.0)
    tri.GetPoints().SetPoint(2, 0.0, 1.0, 0.0)

    tri.GetPointIds().SetId(1, 1)
    tri.GetPointIds().SetId(2, 2)
    print(tri)

    print("area: ", tri.ComputeArea())

if __name__ == '__main__':
    #demo_cell_vertex()

    demo_cell_triangle()
    print("done")
