/**
 *
 *
 */
package net.brucejia.cloneme;

class Program {

    public static void main (String [] args) {

        CloneMe obj = new CloneMe("first");
        CloneMe obj_2 = (CloneMe)obj.clone();

        System.out.println(obj.toString());
        System.out.println(obj_2.toString());
    }
}
