# 官方网站

[www.kernel.org](https://www.kernel.org/)

[KERNEL-文档](https://www.kernel.org/doc/html/latest/)

文档描述了如何编译、支持的设备等内核全部功能与兼容问题。

### 如何阅读版本号

- `stable` : 稳定版本
- `longterm` : 长期支持版本

格式:

```<base-kernel-version>.<ABI-number>.<upload-number>-<flavour>```

# 内核架构

### 内核组成

- system call interface (SCI - POSIX/SUS)

    系统调用, 允许用户空间程序与内核交互。

- process scheduling (SCHED)

    进程调度器, 负责控制对CPU的进程访问。调度程序执行一项调度策略，以确保进程可以公平地访问CPU，同时确保内核按时执行必要的硬件操作。

    相关词: `SMP`, `NUMA`, `调度(算法)`

- ipc (IPC)

    进程间通信, 实现在单个Linux系统上进行进程间通信的多种机制。

    相关词: `unix-socket`, `信号量`

- memory management (MM)

    内存管理器, 允许多个进程安全地共享机器的主内存系统。此外，内存管理器还支持虚拟内存，该虚拟内存允许Linux支持使用的内存量超过系统可用内存的进程。使用文件系统将未使用的内存换出到持久性存储，然后在需要时交换回来。

    相关词: `虚拟内存`, `内存映射`, `物理内存`, `页表`, `swap`, `slab`

- virtual files (VFS)

    虚拟文件系统, 通过为所有设备提供通用文件接口来抽象化各种硬件设备的详细信息。

    相关词: `缓存`, `文件系统`, `VFS`, `inode`, `bio`, `设备子系统`, `device-mapper`, `io-scheduler`

- network (NET)

    网络接口, 提供对几种网络标准和各种网络硬件的访问。

    相关词: `netfilter`, `linux-network-scheduler`, `socket`

- linux security

    内核安全模块, 提供审计等企业需求。

    相关词: `SELinux`, `TOMOYO`, `AppArmor`, `Smack`

- os-level virtualization

    操作系统级虚拟化。

    相关词: `cgroups`, `linux-namespaces`

- hardware-assisted virtualization

    硬件及虚拟化。

    相关词: `kvm`, `qeum`
