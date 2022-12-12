#include "fonctions.h"
#include<stdlib.h>


int main(){
    /*Segment du code de test malloc_3is , Peut-il sortir avec succès ou pas*/
	int *ptr_0 = NULL, N = 100;  
	ptr_0 = (int*) malloc_3is(N * sizeof(int));  
	if (ptr_0 == NULL){  //Si l'ouverture échoue, un pointeur NULL est renvoyé, il faut donc vérifier la valeur de retour de malloc.
		printf("ERROR : malloc_3is returned NULL\n"); //Imprimer le message d'erreur
		return EXIT_FAILURE;
	}
	else{
		printf("\n");
		//return EXIT_SUCCESS;    
	}

    /*Segment de code de test : allocation et libération de la mémoire*/
    int* p = (int*)malloc_3is(40);//40 espace demandé à la mémoire
    int* ptr = p;   //Si cette étape n'est pas effectuée, le free(p); suivant est erroné, car p pointe à l'origine vers le début de l'espace, mais la boucle précédente fait pointer p vers la seconde moitié de l'espace, ce qui rend impossible la libération complète de l'espace.
    //Vérifiez
    if (p == NULL)  //Si l'ouverture échoue, un pointeur NULL est renvoyé, il faut donc vérifier la valeur de retour de malloc.
    {
        printf("ERROR : malloc_3is returned NULL\n");   //Imprimer le message d'erreur
        return 1;
    }

    for (int i = 0; i < 10; i++){        
        ptr++;
        *ptr = i;
        printf("%p %d %d\n", ptr,*ptr,i); 
    }    
    free_3is(p);//Libération de la mémoire
    p = NULL;//Pour éviter tout accès illégal à l'espace libéré via p, p est défini comme un pointeur nul ici.
    return 1;
}