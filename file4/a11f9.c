#include <stdio.h>
#include <string.h>
#include "simpio.h"

#define N 30
#define M 100

typedef struct{
    int playerNum;
    char name[28];
    int points;
}InfoT;

int readInfo(InfoT scores[],FILE *infile,int *pointSum, int *over10);
void writeToFile(InfoT scores[],FILE *outfile,int sum, int over10,int count);

int main(){

    InfoT scores[M];

    FILE *infile;
    FILE *outfile;
    char inName[N] = "i11f9.dat";

    infile = fopen(inName,"r");
    if(infile == NULL){
        printf("File %s not found",inName);
        exit(1);
    }

    int sum,over10;
    int playerCount = readInfo(scores,infile,&sum,&over10);

    outfile=fopen("baso11f9.dat","w");

    writeToFile(scores,outfile,sum,over10,playerCount);

    fclose(infile);
    fclose(outfile);

    return 0;
}

int readInfo(InfoT scores[],FILE *infile,int *pointSum, int *over10){
    int nscan,i=0,line=0;
    char termch;
    *pointSum=0;
    *over10=0;

    while(TRUE){
        nscan = fscanf(infile,"%d,%28[^,],%d%c",&scores[i].playerNum,
                       scores[i].name,&scores[i].points,&termch);
         line++;

        if(nscan == EOF){break;}
        if(nscan != 4 || termch !='\n'){
            printf("Problem on line %d",line);
            exit(1);
        }
        i++;
    }

    for(int j=0; j<i; j++){
        *pointSum+=scores[j].points;
        if(scores[j].points>10){
            (*over10)++;
        }
    }

    return i;
}

void writeToFile(InfoT scores[],FILE *outfile,int sum, int over10, int count){

     fprintf(outfile,"%-28s %+11s\n","ONOMATEPWNYMO","PONTOI");
     for(int j=0; j<40; j++){fprintf(outfile,"-");}
     fprintf(outfile,"\n");
     for(int j=0; j<count; j++){
         fprintf(outfile,"%-28s %11d\n",scores[j].name,scores[j].points);
     }
     for(int j=0; j<40; j++){fprintf(outfile,"-");}
     fprintf(outfile,"\n");
     fprintf(outfile,"%-28s %11d\n","SYNOLO PONTWN",sum);
     fprintf(outfile,"%-28s %11d\n","SYNOLO PAIKTVN >= 10",over10);

}
