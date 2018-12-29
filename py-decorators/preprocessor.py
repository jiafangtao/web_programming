#
# Demonstrate calling chain of preprocessor
# About Python's class-based decorators, here ia a good reading.
# https://www.artima.com/weblogs/viewpost.jsp?thread=240845


class Preprocessor:
	"""
	A decorator to be called before a function is run
	"""
	def __init__(self, preprocessor):
		self._preprocessor = preprocessor

	def __call__(self, func):
		def func_wrapper(*args, **kwargs):
			#print "going to call the preprocessor {}".format(self._preprocessor.__name__)
			self._preprocessor()

			return func(*args, **kwargs)

		return func_wrapper


def show_ad_renrenche():
	print "[AD] ren ren che"

def show_ad_58tongcheng():
	print "[AD] a magic web site"

@Preprocessor(show_ad_58tongcheng)
@Preprocessor(show_ad_renrenche)
def watch_movie():
	print "Gosh, now I'm able to watch a movie."


def chained_call_1():
	print "chanined call #1"

@Preprocessor(chained_call_1)
def chained_call_2():
	print "chanined call #2"

@Preprocessor(chained_call_2)
def chained_call_3():
	print "chained call #3"

if __name__ == '__main__':
	watch_movie()

	print ""

	chained_call_3()
