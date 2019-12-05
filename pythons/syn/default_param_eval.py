
class DefaultConfiguration(object):
    def __init__(self):
        print("calling DefaultConfiguration.__init__ ......")


class AppConfig(object):
    @classmethod
    def get(cls):
        print("calling AppConfig.get ......")
        return DefaultConfiguration()


def do_some_work(config=AppConfig.get()):
    print("do some work ......")
