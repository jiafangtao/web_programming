#
# draw texts in vtk
#

from vtk import *


def init():
    axes = vtkAxes()
    axes.SetOrigin(0, 0, 0)

    axesMapper = vtkPolyDataMapper()
    axesMapper.SetInputConnection(axes.GetOutputPort())

    axesActor = vtkActor()
    axesActor.SetMapper(axesMapper)

    #mapper = vtkPolyDataMapper()
    lut = vtkLookupTable()
    lut.SetTableRange(0, 10)
    lut.SetAlphaRange(0.5, 0.5)
    lut.SetHueRange(0.2, 0.7)
    lut.SetNumberOfTableValues(256)
    lut.Build()

    scalarBar = vtkScalarBarActor()
    #scalarBar.SetLookupTable(mapper.GetLookupTable())
    scalarBar.SetLookupTable(lut)
    scalarBar.SetTitle("Temperature")
    scalarBar.GetPositionCoordinate().SetCoordinateSystemToNormalizedViewport()
    scalarBar.GetPositionCoordinate().SetValue(0.1, 0.01)
    scalarBar.SetOrientationToHorizontal()
    scalarBar.SetWidth(0.8)
    scalarBar.SetHeight(0.1)
    
    # create a renderer
    renderer = vtkRenderer()

    #Create a render window.
    renderWindow = vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindow.SetWindowName("Draw 3D Text")

    renderer.AddActor(axesActor)

    renderer.AddActor(scalarBar)

    # Create an interactor.
    renderWindowInteractor = vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    return renderWindow, renderWindowInteractor, renderer


if __name__ == '__main__':
	renWin, interactor, renderer = init()
	
	renWin.Render()
	interactor.Start()
