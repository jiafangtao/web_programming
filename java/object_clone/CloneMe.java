/**
 *
 *
 */

package net.brucejia.cloneme;

public class CloneMe {

    public CloneMe (String name) {
        this.name = name;
    }
     public Object clone () {
         CloneMe cloned = new CloneMe(this.name + "_cloned");
         return cloned;
     }

     public String toString () {
         return this.name;
     }

     private String name;
}
