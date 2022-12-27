#include <stdio.h>
#include <string.h>
#include "simpio.h"

#define N 30
#define M 100

typedef struct{
    char lastName[40];
    long balance;
    float interest;
    int year;
}AccountT;

int readInput(char inFileName[N], AccountT newData[]);
int findMissing(AccountT nData[],AccountT oData[],AccountT mData[],int nCount,int oCount);
void after2000(AccountT nData[],int nCount);
float sum40percent(AccountT data[],int count);
void maxDeposit(AccountT data[],int count,int *year, char nameMax[]);

int main(){

    AccountT newData[M],oldData[M],missingData[M];

    int newCount = readInput("bank_new.dat",newData);
    int oldCount = readInput("bank_old.dat",oldData);

    int mCount = findMissing(newData,oldData,missingData,newCount,oldCount);
     printf("Clients in List New not in Old\n");
        for(int i=0; i<mCount; i++){
            printf("--%s %ld\n",missingData[i].lastName,missingData[i].balance);
        }

    after2000(newData,newCount);
    after2000(oldData,oldCount);

    float newSum = sum40percent(newData,newCount);
    float oldSum = sum40percent(oldData,oldCount);
    printf("Expected Tax New %.2f\nExpected Tax Old %.2f\n",newSum,oldSum);


    int yearNew,yearOld;
    char nameNew[40],nameOld[40];
    maxDeposit(newData,newCount,&yearNew,nameNew);
    printf("Max in New: %s %d\n",nameNew,yearNew);

    maxDeposit(oldData,oldCount,&yearOld,nameOld);
    printf("Max in Old: %s %d\n",nameOld,yearOld);

    return 0;
}


int readInput(char inFileName[N], AccountT data[]){
    int nscan,line=0,i=0;
    char termch;
    FILE *infile;

    infile = fopen(inFileName,"r");
    if(infile == NULL){
        printf("File %s not found",inFileName);
        exit(1);
    }


    while(TRUE){
        nscan = fscanf(infile,"%40[^,], %ld, %f, %d%c",
                       data[i].lastName,&data[i].balance,
                       &data[i].interest,&data[i].year,&termch);
        line++;

        if(nscan == EOF){break;}
        if(nscan != 5 || termch != '\n'){
            printf("Problem on line %d",line);
            exit(1);
        }
        i++;
    }
    fclose(infile);
    return i;
}

int findMissing(AccountT nData[],AccountT oData[],AccountT mData[],int nCount,int oCount){
    int mCount=0,flag;

    for(int i=0; i<nCount; i++){
        flag=0;
        for(int j=0; j<oCount; j++){
            if(strcmp(nData[i].lastName,oData[j].lastName)==0){
                flag=1;
                break;
            }
        }
        if(flag==0){mData[mCount++]=nData[i];}
    }

    return mCount;
}

void after2000(AccountT nData[],int nCount){
    FILE *outfile;
    outfile = fopen("mztfgm.dat","w");

    for(int i=0; i<nCount; i++){
       fprintf(outfile,"%s, %ld, %f, %d\n",
               nData[i].lastName,nData[i].balance,
               nData[i].interest,nData[i].year);
    }

    fclose(outfile);
}

float sum40percent(AccountT data[],int count){
    int sum=0;

    for(int i=0; i<count; i++){
        sum+=data[i].balance;
    }


    return sum*0.4;
}

void maxDeposit(AccountT data[],int count,int *year, char nameMax[]){
    int max;
    max = data[0].balance;
    *year=data[0].year;

    for(int i=0; i<count; i++){
        if(max<data[i].balance){
             max = data[i].balance;
            *year = data[i].year;
            strcpy(nameMax,data[i].lastName);
        }
    }
}
