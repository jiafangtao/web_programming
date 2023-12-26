#! /usr/bin/env python3


import sys
from PySide6.QtCore import QObject, QPropertyAnimation, Property, Signal
from PySide6.QtGui import QGuiApplication, QVector3D, QQuaternion, QMatrix4x4
from PySide6.Qt3DCore import Qt3DCore 
from PySide6.Qt3DExtras import Qt3DExtras
from PySide6.Qt3DRender import Qt3DRender

class OrbitTransformController(QObject):
	def __init__(self, parent):
		super().__init__(parent)
		self._target = None
		self._matrix = QMatrix4x4()
		self._radius = 1
		self._angle = 0

	def setTarget(self, t):
		self._target = t

	def getTarget(self):
		return self._target

	def setRadius(self, r):
		if self._radius != r:
			self._radius = r
			self.updateMatrix()
			self.radiusChanged.emit()

	def getRadius(self):
		return self._radius

	def setAngle(self, a):
		if self._angle != a:
			self._angle = a
			self.updateMatrix()
			self.angleChanged.emit()

	def getAngle(self):
		return self._angle

	def updateMatrix(self):
		self._matrix.setToIdentity()
		self._matrix.rotate(self._angle, QVector3D(0, 1, 0))
		self._matrix.translate(self._radius, 0, 0)
		if self._target is not None:
			self._target.setMatrix(self._matrix)

	angleChanged = Signal()
	radiusChanged = Signal()
	angle = Property(float, getAngle, setAngle, notify=angleChanged)
	radius = Property(float, getRadius, setRadius, notify=radiusChanged)


class Window(Qt3DExtras.Qt3DWindow):
	def __init__(self):
		super().__init__()

		# camera
		self.camera().lens().setPerspectiveProjection(45, 16/9, 0.1, 1000)
		self.camera().setPosition(QVector3D(0, 0, 40))
		self.camera().setViewCenter(QVector3D(0, 0, 0))

		# for camera controls
		self.createScene()
		self.camController = Qt3DExtras.QOrbitCameraController(self.rootEntity)
		self.camController.setLinearSpeed(50)
		self.camController.setLookSpeed(180)
		self.camController.setCamera(self.camera())

		self.setRootEntity(self.rootEntity)
	
	def createScene(self):
		self.rootEntity = Qt3DCore.QEntity()
		
		self.material = Qt3DExtras.QPhongMaterial(self.rootEntity)

		# torus
		self.torusEntity = Qt3DCore.QEntity(self.rootEntity)
		self.torusMesh = Qt3DExtras.QTorusMesh()
		self.torusMesh.setRadius(5)
		self.torusMesh.setMinorRadius(1)
		self.torusMesh.setRings(100)
		self.torusMesh.setSlices(20)

		self.torusTransform = Qt3DCore.QTransform()
		self.torusTransform.setScale3D(QVector3D(1.5, 1, 0.5))
		self.torusTransform.setRotation(QQuaternion.fromAxisAndAngle(QVector3D(1, 0, 0), 45.0))

		self.torusEntity.addComponent(self.torusMesh)
		self.torusEntity.addComponent(self.torusTransform)
		self.torusEntity.addComponent(self.material)

		# sphere
		self.sphereEntity = Qt3DCore.QEntity(self.rootEntity)
		self.sphereMesh = Qt3DExtras.QSphereMesh()
		self.sphereMesh.setRadius(3)
		#self.sphereMesh.setGenerateTangents(True)

		self.sphereTransform = Qt3DCore.QTransform()
		self.sphereController = OrbitTransformController(self.sphereTransform)
		self.sphereController.setTarget(self.sphereTransform)
		self.sphereController.setRadius(20)

		self.sphereRotateTransformAnimation = QPropertyAnimation(self.sphereTransform)
		self.sphereRotateTransformAnimation.setTargetObject(self.sphereController)
		self.sphereRotateTransformAnimation.setPropertyName(b'angle')
		self.sphereRotateTransformAnimation.setStartValue(0)
		self.sphereRotateTransformAnimation.setEndValue(360)
		self.sphereRotateTransformAnimation.setDuration(10000)
		self.sphereRotateTransformAnimation.setLoopCount(-1)
		self.sphereRotateTransformAnimation.start()

		self.sphereEntity.addComponent(self.sphereMesh)
		self.sphereEntity.addComponent(self.sphereTransform)
		self.sphereEntity.addComponent(self.material)


if __name__ == '__main__':
	app = QGuiApplication(sys.argv)

	#view = Qt3DExtras.Qt3DWindow()
	#scene = createScene()

	# camera
	"""
	camera = view.camera()
	camera.lens().setPerspectiveProjection(45.0, 16 / 9, 0.1, 1000)
	camera.setPosition(QVector3D(0, 0, 40.0))
	camera.setViewCenter(QVector3D(0, 0, 0))
	"""
	
	#view.setRootEntity(scene)
	#view.show()

	view = Window()
	view.show()

	sys.exit(app.exec())
