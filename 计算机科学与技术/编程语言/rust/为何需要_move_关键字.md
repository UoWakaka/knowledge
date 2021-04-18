## 为何需要 `move` 关键字

为了在闭包环境下显示指定所有权的转移。

由于变量赋值或传参默认所有权转移，而闭包语境下没有转移的特征，所以需要关键字显示注明。

```rust
let capture = "hello".to_string();
let closure = move || {
    println!("rust says {}", capture);
};
closure();
// 编译后会报错 因为 capture 的所有权已经转移至 closure 无法继续使用
println!("rust says {}", capture);
```

### async

```rust
let capture = "hello".to_string();
let block = async move {
    println!("rust says {} from async block", capture);
};
```

### 闭包作为返回值

```rust
fn create_fn() -> impl Fn() {
    let text = "Fn".to_owned();
    move || println!("This is a: {}", text)
}
let fn_plain = create_fn();
fn_plain();
```
