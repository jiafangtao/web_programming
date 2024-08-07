# demo_3_12.py - demonstrate type variables in generics
# CopyLeft by "Bruce Jia" if it works; Otherwise I don't know who wrote it, :)
#

import sys
print(sys.version) # just showing which version we're using


from collections.abc import Sequence


def min[T](l: Sequence[T]) -> T:
	# ignore the logic ...
	return l[0]


def max[T](l: Sequence[T]) -> T:
	# ignore the logic ...
	return l[1]


def avg(l: Sequence[T]) -> T:
	# ...
	return l[2]


print(avg([1, 3, 2, 2]))


print(min([1,2]))
print(max([1,2]))

