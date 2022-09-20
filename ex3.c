/*HUANG Roger 11807555*/

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

/*Fonctions*/
int minimum(int a, int b){
    if(a<b){
        return a;
    }
    return b;
}

int maximum(int a, int b){
    if(a>b){
        return a;
    }
    return b;
}

int main(){

    /*Création de deux tubes*/
    int tube2[2],tube1[2];
    pipe(tube2);
    pipe(tube1);

    /*Le fils*/
    int pid1;

    if( (pid1 = fork()) < 0 ){
        printf("Erreur de création processus");
        return EXIT_FAILURE;
    }

    if(pid1 !=0){
        /*Code du pere*/
        close(tube2[0]); /*Ferme la sortie du pipe 2 = Ecrire sur pipe 2*/
        close(tube1[1]); /*Ferme l'entree du pipe 1 = Lire sur pipe 1*/

        int a=0, donnee;
        
        /*Demande à l'utilisateur la serie d'entiers qu'il veut envoyer et les envoie au fils*/
        printf("Entrer une serie de nombres positifs(pour arrêter la demande d'entrée, entrer un nombre negatif), ces données seront envoyées au fils qui calculera dans l'ordre la somme, le minimum puis le maximum et l'enverra au pere qui le lira et l'affichera sur la sortie standard\n\n");
        while(a>=0){
            printf("Entrer un nombre\n");
            scanf("%d", &a);
            if(a>=0){
                write(tube2[1], &a, sizeof(int));
            }
        }
        close(tube2[1]);

        /*Lit les calculs du fils*/
        wait(NULL);
        while( read(tube1[0], &donnee, sizeof(int)) != 0 ){
            printf("Donnée reçue par le pere : %d\n", donnee);
        }
        close(tube1[0]);
        
        return EXIT_FAILURE;
    }

    else{
        /*Code du fils 1*/
        close(tube2[1]);    /*Ferme l'entree du pipe 2 = lire sur pipe 2*/
        close(tube1[0]);    /*Ferme la sortie du pipe 1 = ecrire sur pipe 1*/
        int b, somme =0, min= 1000000, max = 0;

        /*Lit les données que lui envoie le pere et fait les calculs*/
        while( read(tube2[0], &b, sizeof(int)) != 0 ){
            somme = somme + b;
            min = minimum(min, b);
            max = maximum(max, b);
        }
        close(tube2[0]);

        /*Envoie au pere les calculs qu'il a fait*/
        write(tube1[1], &somme, sizeof(int));
        write(tube1[1], &min, sizeof(int));
        write(tube1[1], &max, sizeof(int));
        close(tube1[1]);

        return EXIT_SUCCESS;
    }   

}
