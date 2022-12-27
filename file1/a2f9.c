#include <stdio.h>
#include <string.h>
#include "simpio.h"

#define M 100
#define N 30

typedef struct{
    char name[30];
    int absences;
    char rand_info[68];
}InfoT;

int readInput(InfoT students[],FILE *infile, int *studentSum,int *abs);
void writeToFile(InfoT students[],FILE *outfile,int sum, int abs);

int main(){

    int sum,absences;

    InfoT students[M];

    FILE *infile;
    FILE *outfile;
    char inName[N] = "i2f9.dat";

    infile = fopen(inName,"r");
    if(infile == NULL){
        printf("File %s not found",inName);
        exit(1);
    }

    readInput(students,infile,&sum,&absences);

    outfile=fopen("o2f9.dat","w");
    writeToFile(students,outfile,sum,absences);

    fclose(infile);
    fclose(outfile);

    return 0;
}

int readInput(InfoT students[],FILE *infile, int *studentSum,int *abs){
    int nscan,i=0,line=0,absence;
    char termch,sName[30],rInfo[68];
    *studentSum=0;
    *abs=0;

    while(TRUE){
        nscan = fscanf(infile,"%30[^,],%ld,%68[^\n]%c",sName,&absence,rInfo,&termch);
        line++;
        if(nscan == EOF){break;}
        if(nscan != 4 || termch !='\n'){
            printf("Problem on line %d",line);
            exit(1);
        }
        if(absence>100){
            strcpy(students[*abs].name,sName);
            strcpy(students[*abs].rand_info,rInfo);
            students[*abs].absences = absence;
            (*abs)++;
        }
        (*studentSum)++;
    }
}

void writeToFile(InfoT students[],FILE *outfile,int sum, int abs){

     fprintf(outfile,"%-30s %+9s\n","ONOMATEPWNYMO","APOYSIES");
     for(int i=0; i<40; i++){fprintf(outfile,"-");}
     fprintf(outfile,"\n");
     for(int i=0; i<abs; i++){
         fprintf(outfile,"%-30s %9d\n",students[i].name,students[i].absences);
     }
     for(int i=0; i<40; i++){fprintf(outfile,"-");}
     fprintf(outfile,"\n");
     fprintf(outfile,"%-30s %9d\n","SYNOLO MATHITWN:",sum);
     fprintf(outfile,"%-30s %9d\n","SYNOLO APONTWN:",abs);

}


