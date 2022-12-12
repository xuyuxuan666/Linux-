#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>  // shared memory
#include<sys/sem.h>  // semaphore
#include<sys/msg.h>  // message queue
#include<string.h>   // memcpy
#include<semaphore.h>

/*
 *功能：
 *  创建一个信号量并初始化它的值
 *参数：
 *  sem: 信号量的地址
 *  pshared:
 *    = 0，信号量在线程间共享
 *    != 0，信号量在进程间共享
 *  value：信号量的初始值
 *return：
 *  成功：0
 *  失败：-1
 */
int sem_init(sem_t *sem, int pshared, unsigned int value);
