class Base {

    @Override
    public String toString() {
        return "I'm a BASE";
    }
}

class Derived extends Base{
    @Override
    public String toString () {
        return "I'm a DERIVED class";
    }
}


class Main {

    public static void main (String args []) {
        Integer x = new Integer(100);
        int y = 200;

        System.out.println(x instanceof Integer);

        /**
         * Below line will cause compilation error.
         * error: unexpected type
        System.out.println(y instanceof Integer);
                           ^
        required: reference
        found:    int
         */
        //System.out.println(y instanceof Integer);

        test();
    }

    private static void test () {
        
        Base b = new Base();
        Derived d = new Derived();
        Base bd = new Derived();

        boolean result = b instanceof Base;
        System.out.println(b instanceof Base);
        System.out.println(d instanceof Derived);
        System.out.println(d instanceof Base);
        System.out.println(bd instanceof Base);
        System.out.println(bd instanceof Derived);

        System.out.println(b.toString());
        System.out.println(d.toString());
        System.out.println(bd.toString());
    }

}
