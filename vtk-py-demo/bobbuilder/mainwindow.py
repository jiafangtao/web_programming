import sys
from PySide6 import QtWidgets, QtCore

# noinspection PyUnresolvedReferences
import vtkmodules.vtkInteractionStyle
# noinspection PyUnresolvedReferences
import vtkmodules.vtkRenderingOpenGL2

from vtkmodules.qt.QVTKRenderWindowInteractor import QVTKRenderWindowInteractor
from vtkmodules.vtkFiltersSources import vtkCubeSource, vtkCylinderSource, vtkSphereSource
from vtkmodules.vtkRenderingCore import (
    vtkActor,
    vtkPolyDataMapper,
    vtkRenderer
)


class DataModel(QtCore.QObject):

    class Event:
        def __init__(self, source, id, type, action):
            self._source = source
            self._id = id
            self._type = type
            self._action = action

        def __str__(self):
            return f"<id: {self._id}, type: {self._type}, action: {self._action}>"
        
        @property
        def source(self):
            return self._source
        
        @property
        def id(self):
            return self._id
        
        @property
        def type(self):
            """type of the part changed - str (cube, cylinder, sphere, etc.)"""
            return self._type
        
        @property
        def action(self):
            """action - str (add, remove, modify, etc.)"""
            return self._action

    partChanged = QtCore.Signal(Event)

    def __init__(self, parent=None):
        super().__init__(parent)

        self._cubes = []
        self._cylinders = []
        self._spheres = []

    def addCube(self, cube):
        self._cubes.append(cube)

        event = self.Event(source=cube, id=cube.id, action='add', type='cube')
        self.onDataChanged(event)

    def addCylinder(self, cylinder):
        self._cylinders.append(cylinder)

        event = self.Event(source=cylinder, id=cylinder.id, action='add', type='cylinder')
        self.onDataChanged(event)

    def addSphere(self, sphere):
        self._spheres.append(sphere)

        event = self.Event(source=sphere, id=sphere.id, action='add', type='sphere')
        self.onDataChanged(event)

    def removeCube(self, cube):
        self._cubes.remove(cube)

        event = self.Event(id=cube.id, source=cube, type='cube', action='remove')
        self.onDataChanged(event)

    def removeCylinder(self, cylinder):
        self._cylinders.remove(cylinder)

        event = self.Event(id=cylinder.id, source=cylinder, type='cylinder', action='remove')
        self.onDataChanged(event)

    def removeSphere(self, sphere):
        self._spheres.remove(sphere)

        event = self.Event(id=sphere.id, source=sphere, type='sphere', action='remove')
        self.onDataChanged(event)

    def onDataChanged(self, event):
        self.partChanged.emit(event)


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(603, 553)
        self.centralWidget = QtWidgets.QWidget(MainWindow)
        self.gridlayout = QtWidgets.QGridLayout(self.centralWidget)
        self.vtkWidget = QVTKRenderWindowInteractor(self.centralWidget)
        self.gridlayout.addWidget(self.vtkWidget, 0, 0, 1, 1)
        MainWindow.setCentralWidget(self.centralWidget)
        MainWindow.statusBar().showMessage("Ready")
        self._setupDockWidget(MainWindow)

    def _setupDockWidget(self, mainWnd):
        self.dockWidget = QtWidgets.QDockWidget("Dock Widget", mainWnd)
        self.dockWidget.setAllowedAreas(QtCore.Qt.LeftDockWidgetArea | QtCore.Qt.RightDockWidgetArea)
        self.dockWidget.setWidget(self._createPanel(mainWnd))
        mainWnd.addDockWidget(QtCore.Qt.LeftDockWidgetArea, self.dockWidget)

    def _createPanel(self, parentWnd):
        wnd = QtWidgets.QWidget(parentWnd)
        btnCube = QtWidgets.QPushButton("Cube")
        btnCylinder = QtWidgets.QPushButton("Cylinder")
        btnSphere = QtWidgets.QPushButton("Sphere")

        layout = QtWidgets.QVBoxLayout(wnd)
        layout.addWidget(btnCube)
        layout.addWidget(btnCylinder)
        layout.addWidget(btnSphere)

        btnCube.clicked.connect(parentWnd.onCreateCube)
        btnCylinder.clicked.connect(parentWnd.onCreateCylinder)
        btnSphere.clicked.connect(parentWnd.onCreateSphere)

        return wnd


class SimpleView(QtWidgets.QMainWindow):

    def __init__(self, controller, model, parent=None):
        QtWidgets.QMainWindow.__init__(self, parent)

        # hooks up the mvc stuff
        self._controller = controller
        self._model = model
        
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ren = vtkRenderer()
        self.ui.vtkWidget.GetRenderWindow().AddRenderer(self.ren)
        self.iren = self.ui.vtkWidget.GetRenderWindow().GetInteractor()

        self._model.partChanged.connect(self.onEvents)

    def onCreateCube(self):
        self._controller.createCube(None, None)

    def onCreateCylinder(self):
        self._controller.createCylinder()

    def onCreateSphere(self):
        self._controller.createSphere()
    
    @QtCore.Slot(DataModel.Event)
    def onEvents(self, event):
        print('(debug) we got an event ...')

        if event.action == 'add':
            self._addComponent(event.source)
        elif event.action == 'remove':
            self._removeComponent(event.source)

    def onCreateCylinder(self):
        self._controller.createCylinder()

    def onCreateSphere(self):
        self._controller.createSphere()

    def _addComponent(self, source):
        # Create a mapper
        mapper = vtkPolyDataMapper()
        mapper.SetInputConnection(source.GetOutputPort())

        # Create an actor
        actor = vtkActor()
        actor.SetMapper(mapper)

        self.ren.AddActor(actor)
        self.ren.Render()

    def _removeComponent(self, source):
        pass


class Controller(QtCore.QObject):
    def __init__(self, model):
        self._model = model
        self._id = 1

    def createCube(self, loc, size):
        source = vtkCubeSource()
        source.SetCenter(0, 0, 0)
        setattr(source, 'id', self._nextId())

        self._model.addCube(source)

    def createSphere(self):
        source = vtkSphereSource()
        source.SetCenter(0, 0, 0)
        source.SetRadius(1.0)
        setattr(source, 'id', self._nextId())

        self._model.addSphere(source)

    def createCylinder(self):
        source = vtkCylinderSource()
        source.SetCenter(0, 0, 0)
        setattr(source, 'id', self._nextId())

        self._model.addCylinder(source)

    def _nextId(self):
        id = self._id
        self._id += 1

        return id


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    
    model = DataModel()
    controller = Controller(model)
    
    window = SimpleView(controller, model)
    window.show()
    window.iren.Initialize()  # Need this line to actually show the render inside Qt

    sys.exit(app.exec())
