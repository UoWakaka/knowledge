#[cfg(feature = "search")]
fn func0() {
    println!("search");
}

#[cfg(not(feature = "search"))]
fn func0() {
    println!("not search");
}

fn main() {
    func0();
}
