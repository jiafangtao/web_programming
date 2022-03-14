package net.brucejia;

import java.io.File;
import java.io.IOException;
import java.nio.charset.Charset;

public class Application {

    private static void testLong() {
        long n = 1024L * 10240 * 1024;
        System.out.println(n > 0 ? "positive" : "negative");
        System.out.println(String.format("%d", n));
    }

    public static void main(String [] argv) {

        testLong();

        /*
        System.out.println("Default charset: " + Charset.defaultCharset());

        File folder = new File("/Users/jiab/temp/测试");
        final String absPath = folder.getAbsolutePath();
        System.out.println("Absolute path: " + absPath);

        try {
            final String canPath = folder.getCanonicalPath();
            System.out.println("Canonical path: " + canPath);
        } catch (IOException e) {
            e.printStackTrace();
        }*/
    }
}
