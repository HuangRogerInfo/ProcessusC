/*HUANG Roger 11807555*/

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex2.h"

int et_read(int fd, etudiant_t *pr){
    int n;
    n = read(fd, pr, sizeof(etudiant_t));

    if(n == -1 || n == 0){
        return 0;
    }
    else{
        return 1;
    }
}

int et_write(int fd, etudiant_t *pr){
    int n;
    n= write(fd, pr, sizeof(etudiant_t));

    if(n==-1 || n==0){
        return 0;
    }
    else{
        return 1;
    }
}

int et_pos(int fd){ 

    off_t a = lseek(fd, 0, SEEK_CUR);
    if(a == -1){
        return -1;
    }
    int b = a / sizeof(etudiant_t);
    return b;

}

int et_seek(int fd, int n){

    off_t a = lseek(fd, n * sizeof(etudiant_t), SEEK_SET);
    if (a == (off_t) -1){
        return -1;
    }
    return n;

}

int et_end(int fd){
    off_t a = lseek(fd, 0, SEEK_END);
    if(a == (off_t) -1){
        return -1;
    }
    int b = a / sizeof(etudiant_t);
    return b;
}

int et_search(int fd, int num_etud){

    etudiant_t rec;
    for(int i = 0 ; i<et_end(fd) ; i++){
	et_seek(fd, i);
        read(fd, &rec , sizeof(etudiant_t) );
        if(rec.num_etud == num_etud){
            return i;
        }
    }
    return -1;
}
