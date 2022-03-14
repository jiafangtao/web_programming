import sys


class MyBucket:
    def __init__(self):
        pass

    def __sizeof__(self):
        return 1000


class MyNoopClass:
    pass


class MyPlainClass:
    name = "plain object"
    def __init__(self):
        self.x = 100
        self.y = 200


if __name__ == '__main__':
    bucket = MyBucket()
    print(f"bucket.__sizeof__ is {bucket.__sizeof__()}")
    print(f"sys.getsizeof(bucket) is {sys.getsizeof(bucket)}")

    noop = MyNoopClass()
    print(f"noop.__sizeof__ is {noop.__sizeof__()}")
    print(f"sys.getsizeof(noop) is {sys.getsizeof(noop)}")

    plain = MyPlainClass()
    print(f"plain.__sizeof__ is {plain.__sizeof__()}")
    print(f"sys.getsizeof(plain) is {sys.getsizeof(plain)}")
