/*HUANG Roger 11807555*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

for (int a= 0; a<10; a++){
    printf("%d ", a);
}
printf("\n");

int pid, pid2;

//création du fils f1
pid = fork();

//code du fils f1
if (pid == 0){
    sleep(1);
    for (int i= 10; i<20; i++){
        printf("%d ", i);
    }
    printf("\n");

}

//code du père
else{
    //le père attend la terminaison de f1 avant de passer à f2
    wait(NULL);

    //création du fils f2
    pid2 = fork();
    
    //code du fils f2
    if(pid2 == 0){
        sleep(1);
        for( int j = 20; j<30; j++){
            printf("%d ", j);
        }
        printf("\n");
    }

    //code du père
    else {
        //le père attend la terminaison de f2 avant de faire son action
        wait(NULL);
        sleep(1);
        for( int k = 30; k<40; k++){
            printf("%d ", k);
        }
        printf("\n");
    }

}

}
