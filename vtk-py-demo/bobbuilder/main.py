import sys
from PySide6 import QtCore, QtWidgets, QtGui
from vtk import *


def main():
    print("under construction ...")

def start_vtk_app():
    cylinder = vtkCylinderSource()
    print(f"cylinder center: {cylinder.GetCenter()}")

    cylinderMapper = vtkPolyDataMapper()
    cylinderMapper.SetInputConnection(cylinder.GetOutputPort())

    cone = vtkConeSource()
    cone.SetRadius(1.5)

    print(f"cone center: {cone.GetCenter()}")

    cone.SetCenter(-2, 0, 0)
    print(f"cone center: {cone.GetCenter()}")

    coneMapper = vtkPolyDataMapper()
    coneMapper.SetInputConnection(cone.GetOutputPort())
    
    #vtkActor
    cylinderActor = vtkActor()
    cylinderActor.SetMapper(cylinderMapper)

    coneActor = vtkActor()
    coneActor.SetMapper(coneMapper)

    colors = vtkNamedColors()
    c = colors.GetColor3d("Bisque")
    coneActor.GetProperty().SetColor(c.GetRed(), c.GetGreen(), c.GetBlue())
    coneActor.GetProperty().SetOpacity(0.8)

    # vtkRenderer
    ren1 = vtkRenderer()
    ren1.AddActor(cylinderActor)
    ren1.AddActor(coneActor)

    renWin = vtkRenderWindow()
    renWin.SetWindowName("demo@2024.1")
    renWin.AddRenderer(ren1)

    # vtkRenderWindowInteractor 
    iren = vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)

    # add the custom style
    style = MouseInteractorHighLightActor()
    style.SetDefaultRenderer(ren1)
    iren.SetInteractorStyle(style)

    renWin.Render()
    iren.Start()



class MouseInteractorHighLightActor(vtkInteractorStyleTrackballCamera):

    def __init__(self, parent=None):
        self.AddObserver("LeftButtonPressEvent", self.leftButtonPressEvent)

        self.LastPickedActor = None
        self.LastPickedProperty = vtkProperty()

    def leftButtonPressEvent(self, obj, event):
        clickPos = self.GetInteractor().GetEventPosition()

        picker = vtkPropPicker()
        picker.Pick(clickPos[0], clickPos[1], 0, self.GetDefaultRenderer())

        # get the new
        self.NewPickedActor = picker.GetActor()

        # If something was selected
        if self.NewPickedActor:
            # If we picked something before, reset its property
            if self.LastPickedActor:
                self.LastPickedActor.GetProperty().DeepCopy(self.LastPickedProperty)

            # Save the property of the picked actor so that we can
            # restore it next time
            self.LastPickedProperty.DeepCopy(self.NewPickedActor.GetProperty())
            # Highlight the picked actor by changing its properties
            colors = vtkNamedColors()
            self.NewPickedActor.GetProperty().SetColor(colors.GetColor3d('Red'))
            self.NewPickedActor.GetProperty().SetDiffuse(1.0)
            self.NewPickedActor.GetProperty().SetSpecular(0.0)
            self.NewPickedActor.GetProperty().EdgeVisibilityOn()

            # save the last picked actor
            self.LastPickedActor = self.NewPickedActor
        else:
        	# clean the last selection if any - not so sweet, I'd remove it.
        	#if self.LastPickedActor:
        	#	self.LastPickedActor.GetProperty().DeepCopy(self.LastPickedProperty)
        	#	self.LastPickedActor = None
        	pass

        self.OnLeftButtonDown()
        return

if __name__ == '__main__':
    if len(sys.argv) >= 2:
        app_name = sys.argv[1]
        if app_name == 'vtk':
            start_vtk_app()
            sys.exit(0)

    main()

