package net.brucejia.learning.demo;

import org.springframework.context.annotation.Bean;

/**
 * You are free to use this piece of code at no restriction.
 * If it works, it's written by jiab; Otherwise I don't know who wrote it.
 * The day 2019/3/7 is another beautiful day. Happy coding.
 */
public class ToyFactory {

    @Bean
    public Toy createByName(final String name){
        if (name.compareToIgnoreCase("dog") == 0){
            return new DogToy();
        }

        return null;
    }
}
