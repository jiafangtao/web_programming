pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_should_work() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }

    # [test]
    fn another_test() {
        panic!("fail this test");
    }
}