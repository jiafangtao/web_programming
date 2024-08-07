# demo.py - demonstrate type variables in generics
# CopyLeft by "Bruce Jia" if it works; Otherwise I don't know who wrote it, :)
#

import sys
print(sys.version) # just showing which version we're using


from typing import TypeVar
from collections.abc import Sequence


T = TypeVar("T")

def min(l: Sequence[T]) -> T:
	# ignore the logic ...
	return l[0]


def max(l: Sequence[T]) -> T:
	# ignore the logic ...
	return l[1]


print(min([1,2]))
print(max([1,2]))
