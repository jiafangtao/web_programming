package net.brucejia.bookstore;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Random;

@RestController
@RequestMapping("/magazines")
public class MagazineController {

    @GetMapping
    public String getAll(){
        if (new Random().nextFloat() < .5) {
            try {
                Thread.sleep(5000);
            }
            catch(InterruptedException e){

            }
        }
        return "C++ Journal, The Apple World";
    }
}
