#
# Some function decorators 
#

def increase(func):
	"""
	increase is a function decorator which adds 1 to the result of the callee
	"""
	def decorated_func(*args, **kwargs):
		result = func(*args, **kwargs)
		return result + 1

	return decorated_func

@increase
def get_dimensions():
	return 3

@increase
def plus(x, y):
	return x + y

##########################################################
def ignore(func):
	"""A decorator makes the callee being ignored"""
	def no_op(*args, **kwargs):
		return None
	return no_op

@ignore
def say_hello(greetings):
	print "hello, {}".format(greetings)


@ignore
def plus3(x, y, z):
	return x + y + z


#########################################################
# utility to log function durations
#########################################################
from datetime import datetime

def duration(func):
	def func_wrapper(*args, **kwargs):
		print "before calling function " + func.__name__
		startTime = datetime.now()
		ret = func(*args, **kwargs)
		endTime = datetime.now()
		d = endTime - startTime
		print "after calling function " + func.__name__
		print "duration is {} seconds".format(d.seconds + d.microseconds / 1000000.0)
	return func_wrapper


import time
import random

@duration
def a_time_consuming_func():
	timeout = 5 * random.random()
	time.sleep(timeout)


#
# decorations with parameters
#

def repeat(n):
	if (n <= 1):
		n = 1
	def repeat_decorator(func):
		def func_wrapper(*args, **kwargs):
			for i in range(n):
				func(*args, **kwargs)
		
		return func_wrapper

	return repeat_decorator

@repeat(3)
def draw_line():
	print "--------------------------------------"

if __name__ == '__main__':

	print get_dimensions()
	print plus(500, 500)

	say_hello('bruce.jia')

	print plus3(1, 2, 3)

	a_time_consuming_func()

	draw_line()
