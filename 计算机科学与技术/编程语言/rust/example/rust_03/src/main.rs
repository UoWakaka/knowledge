use futures::executor;

async fn hello1() {
    println!("h1");
}

async fn hello2() {
    hello1().await; // 等待它完成
    println!("h2");
}

fn main() {
    executor::block_on(hello2());
}
