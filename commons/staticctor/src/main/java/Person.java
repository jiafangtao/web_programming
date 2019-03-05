/**
 * You are free to use this piece of code at no restriction.
 * If it works, it's written by jiab; Otherwise I don't know who wrote it.
 * The day 2019/3/5 is another beautiful day. Happy coding.
 */
public class Person {
    private String name;
    private int age;
    private String org;

    {
        this.org = "autodesk";
        System.out.println("Constructing a new instance of Person");
    }

    public Person(String name, int age, String org) {

        this.name = name;
        this.age = age;
        this.org = org;
    }

    public Person(String name, int age) {
        this(name, age, null);
    }

    public Person(String name) {
        this(name, -1, null);
    }


    public static void main(String [] args) {
        Person p1 = new Person("john");
        Person p2 = new Person("doe", 20);
        Person p3 = new Person("zac", 30, "legal");

        System.out.println(p1);
        System.out.println(p2);
        System.out.println(p3);
    }
}
