```shell
[root@localhost File03_Thread]# ./a.out 
No task now! Thread 2190952192 is waiting!
No task now! Thread 2182559488 is waiting!
No task now! Thread 2174166784 is waiting!
    
// 分配一个任务只有 2190952192 抢到
I am Boss, I assigned 1 tasks, I notify all coders!
Have task now! Thread 2190952192 is grabing the task !
Thread 2190952192 has a task A now!
Have task now! Thread 2182559488 is grabing the task !
No task now! Thread 2182559488 is waiting!
Have task now! Thread 2174166784 is grabing the task !
No task now! Thread 2174166784 is waiting!
Thread 2190952192 finish the task A!
No task now! Thread 2190952192 is waiting!
    
// 分配两个任务，    2182559488 抢到B；2174166784抢到C
I am Boss, I assigned 2 tasks, I notify all coders!
Have task now! Thread 2182559488 is grabing the task !
Thread 2182559488 has a task B now!
Have task now! Thread 2174166784 is grabing the task !
Thread 2174166784 has a task C now!
Have task now! Thread 2190952192 is grabing the task !
No task now! Thread 2190952192 is waiting!
Thread 2182559488 finish the task B!
No task now! Thread 2182559488 is waiting!
Thread 2174166784 finish the task C!
No task now! Thread 2174166784 is waiting!
    
   
// 分配三个任务，一人一个
I am Boss, I assigned 3 tasks, I notify all coders!
Have task now! Thread 2190952192 is grabing the task !
Thread 2190952192 has a task D now!
Have task now! Thread 2182559488 is grabing the task !
Thread 2182559488 has a task E now!
Have task now! Thread 2174166784 is grabing the task !
Thread 2174166784 has a task F now!
Thread 2190952192 finish the task D!
No task now! Thread 2190952192 is waiting!
Thread 2182559488 finish the task E!
No task now! Thread 2182559488 is waiting!
Thread 2174166784 finish the task F!
No task now! Thread 2174166784 is waiting!


// 分配4个任务，2182559488抢到两个任务，其他的两个人一人一个
I am Boss, I assigned 4 tasks, I notify all coders!
Have task now! Thread 2190952192 is grabing the task !
Thread 2190952192 has a task G now!
Have task now! Thread 2182559488 is grabing the task !
Thread 2182559488 has a task H now!
Have task now! Thread 2174166784 is grabing the task !
Thread 2174166784 has a task I now!
Thread 2182559488 finish the task H!
Thread 2182559488 has a task J now!
Thread 2190952192 finish the task G!
No task now! Thread 2190952192 is waiting!
Thread 2174166784 finish the task I!
No task now! Thread 2174166784 is waiting!
Thread 2182559488 finish the task J!
No task now! Thread 2182559488 is waiting!
Have task now! Thread 2174166784 is grabing the task !
Have task now! Thread 2190952192 is grabing the task !
Have task now! Thread 2182559488 is grabing the task !
```