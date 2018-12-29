
class Auth:

	def __init__(self, func):
		self._func = func

	def __call__(self):
		print "authenticate the user before calling the function {}".format(self._func.__name__)
		print "......"
		return self._func()


@Auth
def get_my_balance():
	return 99999999999

if __name__ == '__main__':
	print "I'm rich that I have {} dollars".format(get_my_balance())

