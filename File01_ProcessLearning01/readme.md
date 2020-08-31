两个程序的目的是为了创建子进程运行命令`ls -l`。
#### 静态链接实现

编译这两个文件
```shell
gcc -c -fPIC process.c
gcc -c -fPIC main.c
```
编译文件的目的就是做预处理，例如将头文件嵌入到正文中，将定义的宏展开，然后是真正的编译过程，最终生成.o文件，这也算是ELF文件的一种，叫做可重定位文件。

会生成两个.o文件，但.o文件下其实都并不知道彼此的存在，所以还需要注册。要让`create_process`这个函数作为库文件被重用，不能以.o文件的形式存在，而是形成库文件，最简单的类型就是静态链接库.a文件(`libstaticprocess.a`)

```shell
ar cr libstaticprocess.a process.o
```
当有程序要使用这个静态链接库的时候，会将.o文件提取出来，链接到程序中。

```shell
gcc -o staticcreateprocess main.o -L. -lstaticprocess
```
在这个命令里，-L表示在当前目录下找.a文件，`-lstaticprocess`会自动补全文件名，比如加前缀lib，后缀.a， 变成`libstaticprocess.a`，找到这个.a文件后，将里面的`process.o`取出来，和`createprocess.o`做一个链接，形 成二进制执行文件`staticcreateprocess`。
简单来讲，这个命令就是将.a文件里面的`process.o`取出来，和`main.c`做链接，形成二进制可执行文件`staticcreateprocess`，这种文件的格式是ELF文件的第二种格式，不同于上文的格式。

运行程序
```shell
[root@localhost File01]# ./staticcreateprocess 
[root@localhost File01]# 总用量 52
-rw-r--r--. 1 root root 1664 4月   8 06:01 CentOS-Base.repo
-rw-r--r--. 1 root root 1309 4月   8 06:01 CentOS-CR.repo
-rw-r--r--. 1 root root  649 4月   8 06:01 CentOS-Debuginfo.repo
-rw-r--r--. 1 root root  314 4月   8 06:01 CentOS-fasttrack.repo
......
```
至此，进程的创建到执行就全部完成了。

---
#### 动态链接实现

静态链接库（.a文件通过`ar`操作后变成的.a文件）一旦链接进去，代码和变量的section都合并了，因而程序运行的时候，就不依赖于这个库是否存在。但是这样有一个缺点，就是相同的代码段，如果被多个程序使用的话，在内存里面就有多份，而且一旦静态链接库更新了，如果二进制执行文件不重新编译，也不随着更新。 因而就出现了另一种，动态链接库（Shared Libraries），不仅仅是一组对象文件的简单归档，而是多个对象文件的重新组合，可被多个程序共享。

```shell
gcc -shared -fPIC -o libdynamicprocess.so process.o
```

当一个动态链接库被链接到一个程序文件中的时候，**最后的程序文件并不包括动态链接库中的代码，而仅仅包括对动态链接库的引用，并且不保存动态链接库的全路径，仅仅保存动态链接库的名称。**

```shell
[root@localhost File01]# gcc -o dynamiccreateprocess main.o -L. -ldynamicprocess
[root@localhost File01]# ls
dynamiccreateprocess  libdynamicprocess.so  libstaticprocess.a  main.c  main.o  process.c  process.o  staticcreateprocess

```

当运行这个程序的时候，首先寻找动态链接库，然后加载它。默认情况下，系统在`/lib`和`/usr/lib`文件夹下寻 找动态链接库。如果找不到就会报错，我们可以设定`LD_LIBRARY_PATH`环境变量，程序运行时会在此环境变量指定的文件夹下寻找动态链接库。

```shell
[root@localhost File01]# export LD_LIBRARY_PATH=.
[root@localhost File01]# ./dynamiccreateprocess 
[root@localhost File01]# 总用量 52
-rw-r--r--. 1 root root 1664 4月   8 06:01 CentOS-Base.repo
......
```

动态链接库本质上就是ELF文件的第三种文件类型，共享对象文件（Shared Object）。
这次的ELF文件和之前的相比文件又有增加，多了一个`ld-linux.so`（动态链接器），此外还多了两个section，一个`.plt`-（过程链接表），一个是`.got.plt`，全局偏移量。这些文件的目的简单来说，就是为了`main.c`文件调`create_process`函数时，知道去哪里调。

如果地址是存在的，那么一系列的过程就是`dynamiccreateprocess`调用PLT[x]里面的代理代码，代理代码调用GOT表中对应项 GOT[y]，调用的就是加载到内存中的`libdynamicprocess.so`里面的`create_process`函数了。