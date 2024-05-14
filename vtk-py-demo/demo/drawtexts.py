#
# draw texts in vtk
#

from vtk import *

def drawText(s, position=None, actor=None):
    if actor is None:
        actor = vtkTextActor()

    actor.SetInput(s)
    if position is None:
    	position = [10, 40]
    #actor.SetPosition2(position[0], position[1])
    actor.SetPosition(position)

    actor.GetTextProperty().SetFontSize(24)
    #actor.GetTextProperty().SetColor(colors->GetColor3d("Gold").GetData());
    
    return actor 

def init():
    # create a renderer
    renderer = vtkRenderer()

    #Create a render window.
    renderWindow = vtkRenderWindow()
    renderWindow.AddRenderer(renderer)
    renderWindow.SetWindowName("DrawText")

    # Create an interactor.
    renderWindowInteractor = vtkRenderWindowInteractor()
    renderWindowInteractor.SetRenderWindow(renderWindow)

    return renderWindow, renderWindowInteractor, renderer


if __name__ == '__main__':
	renWin, interactor, renderer = init()
	textActor = drawText('hello world')
	renderer.AddActor2D(textActor)

	renWin.Render()
	interactor.Start()

#
# NEXT
#   1. show x,y value in text when mouse is moving
#   2. 3d text?
#
