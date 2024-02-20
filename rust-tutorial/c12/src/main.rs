use std::env;
use std::fs;
use std::process;


// str vs String
//


fn main() {

    let args: Vec<String> = env::args().collect();
    let config = Config::build(&args).unwrap_or_else(|err| {
        println!("Problem parsing arguments: {err}");
        process::exit(1);
    });
    

    println!("(info) We've got arguments - {}, {}", config.query, config.file_path);
    let contents = fs::read_to_string(config.file_path).expect("A valid text file is expected");   
    
    println!("{}", contents);
}

//TODO: the parameter type can be &[String] or &Vec<String>,
//  is there any difference?
//


struct Config {
    query: String,
    file_path: String,
}

impl Config {
    fn build(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("not enough arguments");
        }
        let query = args[1].clone();
        let file_path = args[2].clone();
    
        Ok(Config {query, file_path})
    }
}
