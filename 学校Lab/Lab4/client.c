/*#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>  // shared memory
#include<sys/sem.h>  // semaphore
#include<sys/msg.h>  // message queue
#include<string.h>   // memcpy

// 联合体，用于semctl初始化
union semun
{
    int              val; 
    struct semid_ds *buf;
    unsigned short  *array;
};
*/
#include "segdef.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct sembuf sop ;
int semid;
int shmid;
segment* ptshm;

void myWait_sem(int semid, int sem){
    struct sembuf sops;
    sops.sem_num=sem;
    sops.sem_op=0;
    sops.sem_flg=0;
    if(semop(semid,&sops,1)==-1){
        perror("wait failed");
        exit(1);
    }
}

void myAcq_sem(int semid, int sem){
    struct sembuf sops;
    sops.sem_num=sem;
    sops.sem_op=-1;
    sops.sem_flg=SEM_UNDO;
    if(semop(semid,&sops,1)==-1){
        perror("acquire failed");
        exit(1);
    }
    
}

void myLib_sem(int semid, int sem){
    struct sembuf sops;
    sops.sem_num=sem;
    sops.sem_op=1;
    sops.sem_flg=SEM_UNDO;
    if(semop(semid,&sops,1)==-1){
        perror("release failed");
        exit(1);
    }
}

void init(){ //ipcs to check
    semid=semget(cle,0,0);
    if(semid==-1){
        perror("semget");
        exit(1);
    }
    shmid=shmget(cle,0,0);
    if(shmid==-1){
        perror("shmget");
        exit(1);
    }
    ptshm=shmat(shmid,NULL,0); //attach segment
    if(ptshm==(void *) -1 ){
        perror("shmat");
        exit(1);    
    }
    //init_rand();
}


int main(){
    
    fork();
    long sum=0;
    //0
    init();
    //printf("semid=%d\n",semid);
    //printf("shmid=%d\n",shmid);
    //1
    myAcq_sem(semid,seg_dispo);
    //2
    ptshm->pid=getpid();
    ptshm->req=1;
    ptshm->result=0;
    for(int i=0;i<maxval;i++){
        (ptshm->tab[i])=getrand();
        sum=sum+ptshm->tab[i];
    }
    sum=sum/maxval;   
    myAcq_sem(semid,seg_init);
    //3
    myWait_sem(semid,res_ok);
    //4
    long res=ptshm->result;
    myLib_sem(semid,seg_init);
    //5
    myAcq_sem(semid,res_ok); //check if res_ok is free
    myLib_sem(semid,res_ok);
    //6
    myLib_sem(semid,seg_dispo);
    //7
    if(sum!=res){
        printf("ERROR: the result is wrong \n");
    }
    shmdt(ptshm);   
    return 0;
}