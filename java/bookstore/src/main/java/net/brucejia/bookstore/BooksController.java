package net.brucejia.bookstore;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class BooksController {

    @RequestMapping(value="/books")
    public String getBooks(){
        return "Thinking in C++, Code Complete, PHP is the best language";
    }
}
