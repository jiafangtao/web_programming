/**
 * You are free to use this piece of code at no restriction.
 * If it works, it's written by jiab; Otherwise I don't know who wrote it.
 * The day 2019/3/7 is another beautiful day. Happy coding.
 */
package net.brucejia.learning.demo;

import org.springframework.stereotype.Component;

@Component
public class DogToy implements Toy {

    public void play(){
        System.out.println("dog woolf");
    }
}

