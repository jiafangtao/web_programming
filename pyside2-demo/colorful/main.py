import sys
import random
from PySide2 import QtCore, QtWidgets, QtGui

class MyWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Colorful")

        self.button = QtWidgets.QPushButton("Pick a color")
        self.text = QtWidgets.QLabel("Hello colors",
                                     alignment=QtCore.Qt.AlignCenter)

        self.layout = QtWidgets.QVBoxLayout()
        self.layout.addWidget(self.text)
        self.layout.addWidget(self.button)
        self.setLayout(self.layout)

        self.button.clicked.connect(self.pickColor)

    @QtCore.Slot()
    def pickColor(self):
        #self.dialog.exec()
        color = QtWidgets.QColorDialog.getColor()
        if color.isValid():
            s = f'R: {color.red()}, G: {color.green()}, B: {color.blue()}'
            self.text.setText(s)
            self.setBkgroundColor(color)

            reversedColor = QtGui.QColor.fromRgb(255 - color.red(), 255 - color.green(), 255 - color.blue())
            self.setTextColor(reversedColor)
        else:
            self.text.setText("Please select a color again")

    def setBkgroundColor(self, color):
        pal = QtGui.QPalette()
        pal.setColor(QtGui.QPalette.Window, color)

        self.setAutoFillBackground(True)
        self.setPalette(pal)

    def setTextColor(self, color):
        pal = QtGui.QPalette()
        pal.setColor(QtGui.QPalette.WindowText, color)
        self.text.setPalette(pal)


if __name__ == "__main__":
    app = QtWidgets.QApplication([])

    widget = MyWidget()
    widget.resize(800, 600)
    widget.show()

    sys.exit(app.exec_())
