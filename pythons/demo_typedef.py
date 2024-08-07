# demo_typealias.py
# CopyLeft by "Bruce Jia" if it works; Otherwise I don't know who wrote it, :)
#

type Point = tuple[float, float]

class Rectangle:
	def __init__(self, min: Point, max: Point):
		self._min = min
		self._max = max

	def area(self) -> float:
		# ignore ...
		return 0


def calc_distance(p1: Point, p2: Point) -> float:
	# ignore the implementation ...
	return 3.14159


print(type(Point))
print(type(Rectangle))
