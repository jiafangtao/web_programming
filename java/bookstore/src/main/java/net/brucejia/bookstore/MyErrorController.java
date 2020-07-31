package net.brucejia.bookstore;

import org.springframework.boot.web.servlet.error.ErrorController;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class MyErrorController implements ErrorController {

    private static final String PATH = "/error";
    @RequestMapping(value = PATH)
    public String on404(){
        return "404 = 202 + 202";
    }

    @Override
    public String getErrorPath() {
        return PATH;
    }
}
