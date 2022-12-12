#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

#define MAGIC_NUMBER 0x01234567890ABCDEF
#define DEBUG 1

typedef struct HEADER_TAG {
	struct HEADER_TAG* ptr_next; /* pointe sur le prochain bloc libre */
	size_t bloc_size; /* taille du memory bloc en octets*/
	long magic_number; /* 0x0123456789ABCDEFL */
} 
HEADER;


void* malloc_3is(size_t size){
	void *bloc = NULL, *mem_bloc = NULL;
	const size_t size_total = sizeof(HEADER) + size + sizeof(MAGIC_NUMBER);
	HEADER* h = NULL;

	if (bloc == NULL){ 
		if (DEBUG)
			printf("[malloc] nouvelle allocation avec sbrk \n");
		if ((bloc = sbrk(size_total)) == (void *)-1)
			return NULL;
	}

	h = (HEADER*) bloc;
	h->ptr_next = NULL;
	h->bloc_size = size;
	h->magic_number = MAGIC_NUMBER;
	mem_bloc = bloc + sizeof(HEADER);

	if (DEBUG){
		printf("[malloc] size            : %ld\n", size);
		printf("[malloc] mem_bloc        : %p\n", mem_bloc);
		printf("[malloc] h/bloc          : %p\n", h);
		printf("[malloc] h->bloc_size    : %ld\n", h->bloc_size);
		printf("[malloc] h->magic_number : %lx\n", h->magic_number);
	}
	return mem_bloc;
}
/*La fonction free est utilisée pour libérer la mémoire ouverte dynamiquement.
- Si l'espace pointé par l'argument ptr n'est pas ouvert dynamiquement, le comportement de la fonction free est indéfini.
- Si l'argument ptr est un pointeur NULL, la fonction ne fait rien.*/
void free_3is(void *ptr){
	
}
