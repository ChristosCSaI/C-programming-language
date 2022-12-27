#include <stdio.h>
#include <string.h>
#include "simpio.h"

#define N 30
#define M 100

typedef struct{
    int sellerCode;
    char name[25];
    long price;
}InfoT;

int readInfo(InfoT sellers[],FILE *infile);
void calcCommission(InfoT sellers[],int count,long comArray[]);
void writeToFile(InfoT sellers[],FILE *outfile,int count,long comArray[]);

int main(){

    InfoT sellers[M];

    FILE *infile;
    FILE *outfile;
    char inName[N] = "i4f9.dat";

    infile = fopen(inName,"r");
    if(infile == NULL){
        printf("File %s not found",inName);
        exit(1);
    }

    int sellerCount = readInfo(sellers,infile );

    long comArray[sellerCount];
    calcCommission(sellers,sellerCount,comArray);

    outfile=fopen("o4f9.dat","w");
    writeToFile(sellers,outfile,sellerCount,comArray);


    fclose(infile);
    fclose(outfile);

    return 0;
}

int readInfo(InfoT sellers[],FILE *infile){
    int nscan,i=0,line=0;
    char termch;


    while(TRUE){
        nscan = fscanf(infile,"%d,%25[^,],%ld%c",&sellers[i].sellerCode,
                       sellers[i].name,&sellers[i].price,&termch);
         line++;

        if(nscan == EOF){break;}
        if(nscan != 4 || termch !='\n'){
            printf("Problem on line %d",line);
            exit(1);
        }
        i++;
    }
    return i;
}

void calcCommission(InfoT sellers[],int count,long comArray[]){

    for(int i=0; i<count; i++){
        comArray[i] = 0;
        if(sellers[i].sellerCode == 11){
            comArray[i]=sellers[i].price*0.03;
        }
        else if(sellers[i].sellerCode == 12){
            comArray[i]=sellers[i].price*0.05;
        }
        else if(sellers[i].sellerCode == 13){
            comArray[i]=sellers[i].price*0.08;
        }
        else if(sellers[i].sellerCode == 14){
            comArray[i]=sellers[i].price*0.11;
        }
    }

}

void writeToFile(InfoT sellers[],FILE *outfile,int count,long comArray[]){

     fprintf(outfile,"%-24s %7s\n","ONOMATEPWNYMO","POSO PROMITHIAS");
     for(int i=0; i<39; i++){fprintf(outfile,"-");}
     fprintf(outfile,"\n");
     for(int i=0; i<count; i++){
         fprintf(outfile,"%-24s %14ld\n",sellers[i].name,comArray[i]);
     }

}
