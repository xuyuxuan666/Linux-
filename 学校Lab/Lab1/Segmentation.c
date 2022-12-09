#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>

int Data =  256;
int BSS;
char string[] = "cest un string";

int main(int argc, char *argv[]){    
    int pid, status;
    int child_pid;
    child_pid= fork();
    
    if(child_pid != 0){        
        printf("Address Data = %p \n",&Data);     
        printf("Address BSS = %p \n",&BSS);     
        printf("Address String = %p \n",&string[0]);
        printf("Address Heap = %p \n",malloc(sizeof(int)));      
        printf("Address Stack = %p \n",&pid);
         
        struct stat buf;
        int fd=open("test.txt", O_RDWR);
    
        void* address_Mmap = mmap(NULL, buf.st_size, PROT_READ,MAP_SHARED, fd,0);
        void (*address_Main) = &main; 
        void (*address_Libc) = &printf;       
        
        printf("Address Mmap = %p \n",address_Mmap);
        printf("Address main function = %p \n",address_Main);
        printf("Address Libc = %p \n\n",address_Libc);

        wait(&status); //on attend la mort du fils, sinon le père meurt avant
    }
    else{
        pid=getppid(); 
        printf("child process \n");        
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "%d", pid);
        execlp("pmap", "pmap","-X",buffer,(char*)NULL);
        execl("/bin/ls", "ls", NULL); //child process code mort
    }
}
