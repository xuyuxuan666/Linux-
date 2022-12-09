#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

//Étape 1: Créez la structure d'une liste chaînée (Nombre entier)
typedef struct Entier Entier;
struct Entier{
    int nombre;
    Entier *suivant;
    Entier *precedent; //Étape 10:  On a ajouté un attribut qui pointe vers l'adresse du noeud précédent.
};

typedef struct Liste Liste;
struct Liste{
    Entier *premier;
    Entier *dernier;    //Étape 10:  On a ajouté un attribut qui pointe vers l'adresse du noeud précédent.

};

// Initialisation de la liste chaînée;
Liste *initialisation(int valeur){
    Entier *entier = malloc(sizeof(*entier));
    Liste *liste = malloc(sizeof(*liste));
    
    entier->nombre = valeur;
    entier->suivant = NULL;
    entier->precedent = NULL; 
    
    liste->premier = entier;
    liste->dernier = entier;
    return liste;
}

void append(Liste *liste, int new){
    Entier *nouveau = malloc(sizeof(*nouveau)); //on crée le nouvel élément
    nouveau->nombre = new;
    nouveau->suivant = NULL; // ajout à la fin
    nouveau->precedent = liste->dernier;
    liste->dernier->suivant=nouveau;
    liste->dernier= nouveau;
}

void push(Liste *liste, int new){
    Entier *nouveau = malloc(sizeof(*nouveau));//Création du nouvel élément 
    nouveau->nombre = new;
    liste->premier->precedent=nouveau;
    nouveau->suivant = liste->premier; //Insertion de l'élément au début de la liste
    nouveau->precedent = NULL;
    liste->premier = nouveau;
}

// Créer une fonction pour afficher une liste chaînée;
void afficher(Liste *liste){
    Entier *actuel = liste->premier;
    while (actuel != NULL){
        printf("%d | ", actuel->nombre);
        actuel = actuel->suivant;
    }
    printf("\n");
}

//Étape 2: Affichage de la longueur
void length(Liste *liste){
    Entier *actuel = liste->premier;
    int length1 = 0;
    while (actuel != NULL){
        length1++;
        actuel = actuel->suivant;
    }
    printf("length = %d \n",length1);     
    
}

//Étape 3: Affichage <adresse du maillon>
void maillon(Liste *liste){
    Entier *actuel = liste->premier;
    int count = 1;
    printf("Address%d = %p \n",count,actuel);
    while (actuel != NULL){
        //int address = &(*actuel);
        actuel = actuel->suivant;
        count++;
        printf("Address%d = %p \n",count,actuel);
    }
}

//Étape 4:Retirez le premier élément d’une liste
void RetierPremier(Liste *liste){
    if (liste->premier->suivant==NULL){
        Entier *premier=liste->premier;
        free(premier);
    }
    else{
        Entier *premier=liste->premier;
        liste->premier=liste->premier->suivant;
        liste->premier->precedent=NULL;
        free(premier);   //on libère la memoire
    }
}

//Étape 5: Retirez le dernier élément d’une liste
void RetierDernier(Liste *liste){
    if (liste->premier->suivant==NULL){
        Entier *premier=liste->premier;
        free(premier);
    }
    else{
        Entier *actuel = liste->premier;
        Entier *suivant = liste->premier->suivant;
        while (suivant->suivant != NULL){
            actuel = actuel->suivant;
            suivant = suivant->suivant;
        }
        actuel->suivant=NULL;
        liste->dernier=actuel;
        free(suivant);
    }
}

//Étape 8: concatène deux listes
Liste* concatenate(Liste *liste1,Liste *liste2){
    Entier *actuel = liste1->premier;
    if (actuel != NULL){
        Liste *listeConcatenate = initialisation(actuel->nombre);
        actuel = actuel->suivant;
        while (actuel != NULL){
            append(listeConcatenate,actuel->nombre);
            actuel = actuel->suivant;
        }
        actuel = liste2->premier;
        while (actuel != NULL){
            append(listeConcatenate,actuel->nombre);
            actuel = actuel->suivant;
        }
        return listeConcatenate;
    }
} 

//Étape 9: concatène deux listes
Liste* carre(Liste *liste){
    Entier *actuel = liste->premier;
    if (actuel != NULL){
        Liste *listeCarre = initialisation(actuel->nombre*actuel->nombre);
        actuel = actuel->suivant;
        while (actuel != NULL){
            append(listeCarre,actuel->nombre*actuel->nombre);
            actuel = actuel->suivant;
        }
        return listeCarre;
    }
    else{
        return liste;
    }
   
}

int main(int argc,char **argv)
{
    int n = 5; 
    Liste *listeChainee = initialisation(0);  // Initialisation de la liste chaînée;
    for(int i=1;i<n;i++){
        append(listeChainee, i); // Attribution des valeurs à liste chaînée;
    } 
    printf("Étape 1: Créez une liste chaînée (Nombre entier)\n");
    afficher(listeChainee);

    printf("Étape 2: Affichage de la longueur\n");
    length(listeChainee);

    printf("Étape 3: Affichage <adresse du maillon>\n");
    maillon(listeChainee);

    printf("Étape 4: Retirez le premier élément d’une liste\n");
    RetierPremier(listeChainee);
    afficher(listeChainee); 

    printf("Étape 5: Retirez le dernier élément d’une liste\n");
    RetierDernier(listeChainee);
    afficher(listeChainee); 

    printf("Étape 6: Ajoutez un élément à la fin d’une liste\n");
    append(listeChainee,4);
    afficher(listeChainee);

    printf("Étape 7: Ajoutez un élément au début d’une liste\n");
    push(listeChainee,0);
    afficher(listeChainee);

    printf("Étape 8:concatène deux listes\n");
    Liste *listeConcatenate=concatenate(listeChainee,listeChainee);
    afficher(listeConcatenate);

    printf("Étape 9:élévation au carré\n");
    Liste *listecarre = carre(listeChainee);
    afficher(listecarre);

//Étape 10:  On a ajouté un attribut qui pointe vers l'adresse du noeud précédent.Comme celle présentée ci-dessusComme montre 
//Étape 11:  On adapte les fonctions précédentes

    return 0;
}

