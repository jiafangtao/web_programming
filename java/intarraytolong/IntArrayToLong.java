package com.company;

import java.util.List;
import java.util.ArrayList;

public class IntArrayToLong {
    public static Long convert(List<Integer> array) throws IllegalArgumentException {
        if (array.size() != 2) {
            throw new IllegalArgumentException("array should contain 2 integers");
        }

        Long low = (long)array.get(0);
        Long high = (long)array.get(1);

        return low + (high << 32);
    }

    public static void main(/*String[] args*/) {

        ArrayList<Integer> a = new ArrayList<>();
        Long result = convert(a);
        a.add(0);
        a.add(1);

        System.out.println(String.format("Result is %l", result));
    }
}
