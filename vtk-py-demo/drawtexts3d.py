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

    atext = vtkVectorText()
    atext.SetText("Origin")
    textMapper = vtkPolyDataMapper()
    textMapper.SetInputConnection(atext.GetOutputPort())

    textActor = vtkFollower()
    textActor.SetMapper(textMapper)
    textActor.SetScale(0.2, 0.2, 0.2)
    textActor.AddPosition(0, -0.1, 0)
    
    # create a renderer
    renderer = vtkRenderer()

    #Create a render window.
    renderWindow = vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindow.SetWindowName("Draw 3D Text")

    textActor.SetCamera(renderer.GetActiveCamera())
    renderer.AddActor(textActor)
    renderer.AddActor(axesActor)

    # Create an interactor.
    renderWindowInteractor = vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    return renderWindow, renderWindowInteractor, renderer


if __name__ == '__main__':
	renWin, interactor, renderer = init()
	
	renWin.Render()
	interactor.Start()
