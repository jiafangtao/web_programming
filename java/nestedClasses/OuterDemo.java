package net.brucejia.learning;

private class OuterDemo {

    private String _name;

    public OuterDemo (String name) {
        this._name = name;
    }

    @Override
    public String toString() {

        return "I am OuterDemo - " + this._name;
    }
}
