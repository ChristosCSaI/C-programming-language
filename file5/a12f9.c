#include <stdio.h>
#include <string.h>
#include "simpio.h"

#define N 30
#define M 100

typedef struct{
    long AFM;
    char name[28];
    float salary;
}InfoT;

int readDataFromFile(InfoT taxPayers[],FILE *infile);
float calcTaxes(InfoT taxPayers[], int count, float taxArray[]);
void writeToFile(InfoT taxPayers[], int count, float taxArray[],float sum,FILE *outfile);
int main(){

    InfoT taxPayers[M];

    FILE *infile;
    FILE *outfile;
    char inName[N] = "i12f9.dat";


    infile = fopen(inName,"r");
    if(infile == NULL){
        printf("File %s not found",inName);
        exit(1);
    }

    int count = readDataFromFile(taxPayers,infile);
    float taxArray[count],sum;

    outfile = fopen("Foro12f9.dat","w");
    sum = calcTaxes(taxPayers,count,taxArray);

    writeToFile(taxPayers,count,taxArray,sum,outfile);


    fclose(infile);
    fclose(outfile);

    return 0;
}


int readDataFromFile(InfoT taxPayers[],FILE *infile){
    int nscan,line=0,i=0;
    char termch;

    while(TRUE){
        nscan = fscanf(infile,"%ld,%28[^,],%f%c",
                       &taxPayers[i].AFM,taxPayers[i].name,
                       &taxPayers[i].salary,&termch);
        line++;

        if(nscan == EOF){break;}
        if(nscan != 4 || termch != '\n'){
            printf("Problem on line %d",line);
            exit(1);
        }
        i++;
    }

    return i;
}

float calcTaxes(InfoT taxPayers[], int count, float taxArray[]){
    float sum=0;

    for(int i=0; i<count; i++){
            taxArray[i]=0;
        if(taxPayers[i].salary<=10000){
            taxArray[i] = taxPayers[i].salary*0.14;
        }
        if(taxPayers[i].salary>10000 && taxPayers[i].salary<=23000 ){
            taxArray[i] = taxPayers[i].salary*0.19;
        }
        if(taxPayers[i].salary>23000 && taxPayers[i].salary<=50000 ){
            taxArray[i] = taxPayers[i].salary*0.23;
        }
        if(taxPayers[i].salary>50000){
            taxArray[i] = taxPayers[i].salary*0.28;
        }
        sum+=taxArray[i];
    }
    return sum;
}

void writeToFile(InfoT taxPayers[], int count, float taxArray[],float sum,FILE *outfile){

    fprintf(outfile,"%-10s %-28s %+9s\n","AFM","ONOMATEPWNYMO","FOROS");
    for(int i=0; i<50; i++){
        fprintf(outfile,"-");
    }
    fprintf(outfile,"\n");

    for(int i=0; i<count; i++){
       fprintf(outfile,"%ld %-28s %10.2f\n",taxPayers[i].AFM,taxPayers[i].name,taxArray[i]);
    }

    for(int i=0; i<50; i++){
        fprintf(outfile,"-");
    }
    fprintf(outfile,"\n");
    fprintf(outfile,"%-38s %10.2f","SYNOLO FOROY",sum);

}





