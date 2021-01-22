## 为何需要 #[cfg(...)]

一个直观的作用当然是为了隐藏不同平台细节的代码，或者称为在不同平台下的具体实现。

在 C/C++ 语言中也有对应的功能, `#define` 指令。

其最终的目的是为了跨平台。

当然，也可用于测试代码与正式代码的切换，例如接口 `mock` 化。

`example/rust_01` 是一个识别平台的代码, `target_os` 是内置的变量。

```rust
// This function only gets compiled if the target OS is linux
#[cfg(target_os = "linux")]
fn are_you_on_linux() {
    println!("You are running linux!");
}

// And this function only gets compiled if the target OS is *not* linux
#[cfg(not(target_os = "linux"))]
fn are_you_on_linux() {
    println!("You are *not* running linux!");
}

fn main() {
    are_you_on_linux();

    println!("Are you sure?");
    if cfg!(target_os = "linux") {
        println!("Yes. It's definitely linux!");
    } else {
        println!("Yes. It's definitely *not* linux!");
    }
}
```

## 是否可以自定义?

答案是: **可以**，利用编译器的 `feature` 属性。

`example/rust_02` 是完整的测试项目

#### 第一步

```rust
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
```

#### 第二步

在 `Cargo.toml` 文件中注入默认特性

```c
[features]
default = ["search"] // 默认 search 存在

search = [] // 必须
insert = []
```

#### 第三步

编译时注入

```
cargo build --features "search"
// 多个特性以空格区分
cargo build --features "search insert"
// 如果需要打开依赖包的特性
cargo build --features "<依赖包名>/<特性名> ..."
```

实际上对应的编译器行为

```
rustc --cfg feature="${feature_name}"
```