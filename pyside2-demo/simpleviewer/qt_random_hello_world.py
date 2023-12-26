#! /usr/bin/env python3


import sys
import random
from PySide6 import QtCore, QtWidgets, QtGui


class MyWidget(QtWidgets.QWidget):
	def __init__(self):
		super().__init__()
		self.greetings = ["Hello", "Hallo Welt"]
		self.button = QtWidgets.QPushButton("Click")
		self.text = QtWidgets.QLabel("Hello World", 
			alignment=QtCore.Qt.AlignCenter)

		self.layout = QtWidgets.QVBoxLayout(self)
		self.layout.addWidget(self.text)
		self.layout.addWidget(self.button)

		self.button.clicked.connect(self.onClicked)

	@QtCore.Slot()
	def onClicked(self):
		self.text.setText(random.choice(self.greetings))


if __name__ == '__main__':
	app = QtWidgets.QApplication([])

	widget = MyWidget()
	widget.resize(1024, 768)
	widget.show()

	sys.exit(app.exec())
