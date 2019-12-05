
class SomeType(object):
    typeName = "Some Fancy Type"

    @classmethod
    def change_type_name(cls, new_type_name):
        print("<debug> I want to know the original class variable '{}'".format(
            cls.typeName))
        cls.typeName = new_type_name
        print('typeName was changed to "{}"'.format(cls.typeName))

    def __init__(self, sku="unknown"):
        self._sku = sku
        print(self.typeName)
        print(SomeType.typeName)


if __name__ == '__main__':
    print('start hacking...')
    print(SomeType.typeName)

    print("creating object st......")
    st = SomeType("iphonex_256_black")

    st.change_type_name("ugly type")

    print("creting object another st......")
    another_st = SomeType("jeep2019_4x")
