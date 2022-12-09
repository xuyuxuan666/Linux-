#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

#include <fcntl.h>

//On crée un fichier test.txt :  Cest un fichier texte-xu et Stephane 

int main() {

    struct stat buf;
    int fd=open("test.txt", O_RDWR);    //Ouvre ce fichier
    stat("test.txt", &buf);

    //Afficher la taille du fichier  en octets.
    printf("\nsize=%ld octets\n",buf.st_size);
    char string1[buf.st_size]; //Définir le string du fichier original

    //
    char* addr = mmap(NULL, buf.st_size, PROT_WRITE|PROT_READ,MAP_SHARED, fd,0);    //Mapping
    printf("\nAddress = %p \n",addr);
    for(int i=0;i<buf.st_size;i++){
        printf("%c",*(addr+i));
        string1[i] = *(addr+i);        
    }

    printf("\n");  

    char string[buf.st_size];   //Définir le string du fichier après la transformation(inverser)
    for(int i=0;i<buf.st_size/2;i++){ 
        char buffer=*(addr+i);
        *(addr+i)=*(addr+buf.st_size-1-i); 
        *(addr+buf.st_size-1-i)=buffer;
    }
    for(int i=0;i<buf.st_size;i++){
        printf("%c",*(addr+i)); 
        string[i] = *(addr+i);    
    }
 
    //Puisque nous sommes sûrs que les initiales sont différentes, nous déterminons par les initiales si elles sont transformées
     
    if(string[0] != string1[0]){
        
        printf(" \nbien été inversé");
    }
    else{
        printf(" \nne été pas inversé");
    }
    

    munmap(addr,buf.st_size);
    return 0;
}