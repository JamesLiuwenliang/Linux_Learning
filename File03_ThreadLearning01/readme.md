即使没有创建线程，进程也是存在一个主线程的。
编译执行
```shell
gcc -o main main.c -lpthread  # 多线程文件的编译要依赖于libpthread.so

[root@localhost File03_Thread]# ./main
creating thread 0, please help me to download file1.avi
creating thread 1, please help me to download file2.rmvb
I am downloading the file file1.avi!
creating thread 2, please help me to download file3.mp4
I am downloading the file file2.rmvb!
creating thread 3, please help me to download file4.wmv
I am downloading the file file3.mp4!
creating thread 4, please help me to download file5.flv
I am downloading the file file4.wmv!
----------主线程输出------------
I am downloading the file file5.flv! # 这个地方之后，各个线程进入sleep()模式下
I finish downloading the file within 83 minutes!
I finish downloading the file within 86 minutes!
I finish downloading the file within 77 minutes!
Thread 0 downloads the file file1.avi in 83 minutes.
Thread 1 downloads the file file2.rmvb in 86 minutes.
Thread 2 downloads the file file3.mp4 in 77 minutes.
I finish downloading the file within 15 minutes!
I finish downloading the file within 93 minutes!
Thread 3 downloads the file file4.wmv in 15 minutes.
Thread 4 downloads the file file5.flv in 93 minutes.
```

