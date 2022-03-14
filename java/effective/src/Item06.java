public class Item06 {


    private static void autoboxing_with_long_wrapper() {
        long startTime = System.currentTimeMillis();
        Long sum = 0L;
        for (long i=0; i<Integer.MAX_VALUE; i++) {
            sum += i;
        }

        long endTime = System.currentTimeMillis();
        long duration = endTime - startTime;

        System.out.println(String.format("Result is %d", sum));
        System.out.println(String.format("Duration is %d", duration));
    }

    private static void autoboxing_with_long_wrapper_2() {
        long startTime = System.currentTimeMillis();
        Long sum = 0L;
        for (Long i=0L; i<Integer.MAX_VALUE; i++) {
            sum += i;
        }

        long endTime = System.currentTimeMillis();
        long duration = endTime - startTime;

        System.out.println(String.format("Result is %d", sum));
        System.out.println(String.format("Duration is %d", duration));
    }

    private static void autoboxing_with_long_raw() {
        long startTime = System.currentTimeMillis();
        long sum = 0L;
        for (long i=0; i<Integer.MAX_VALUE; i++) {
            sum += i;
        }

        long endTime = System.currentTimeMillis();
        long duration = endTime - startTime;

        System.out.println(String.format("Result is %d", sum));
        System.out.println(String.format("Duration is %d", duration));
    }

    public static void main(String [] args) {
        autoboxing_with_long_wrapper();

        autoboxing_with_long_raw();

        autoboxing_with_long_wrapper_2();
    }
}
