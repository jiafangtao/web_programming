import java.util.Iterator;
import java.util.TreeSet;

public class Application {
    public static void main(String[] args) {

        System.out.println("Sorting the set");
        Application app = new Application();
        TreeSet<Integer> ts = app.prepareTreeSet();
        Iterator<Integer> it = ts.iterator();
        while (it.hasNext()) {
            System.out.printf("%d ", it.next());
        }

        System.out.println("\nDescending output the numbers:");
        Iterator<Integer> dit = ts.descendingIterator();
        while (dit.hasNext()) {
            System.out.printf("%d ", dit.next());
        }
    }

    private TreeSet<Integer> prepareTreeSet() {
        TreeSet<Integer> ts = new TreeSet<Integer>();
        ts.add(3);
        ts.add(2);
        ts.add(5);
        ts.add(7);
        ts.add(4);

        return ts;
    }
}
