#include <stdio.h>
#include "simpio.h"
#include <string.h>

#define size 50

typedef struct{
    char firstName[15];
    char lastName[25];
    float g1;
    float g2;
    float g3;
    float g4;
    float g5;
    float g6;
    char gender;
    float avg;
}StudentsT;


int readInput(StudentsT array[]){
    FILE *infile;

    infile = fopen("lyceum_1.dat","r");
    if(infile == NULL){
        printf("file not found");
        exit(1);
    }

    int i=0,line=0,nscan;
    char termch;

    while(TRUE){
        nscan = fscanf(infile,"%15[^,], %25[^,], %f, %f, %f, %f, %f, %f, %c%c",
                                 array[i].firstName,array[i].lastName,
                                 &array[i].g1,&array[i].g2,&array[i].g3,
                                 &array[i].g4,&array[i].g5,&array[i].g6,
                                 &array[i].gender,&termch);
        line++;

        if(nscan == EOF){break;}
        if(nscan != 10 || termch!='\n'){
            printf("Problem on line %d",line);
            exit(1);
        }
        i++;
    }

    return i;
}

int calculations(StudentsT array[],int count,int *countA, int *countG, StudentsT over10[]){

    *countA = 0;
    *countG = 0;

    int count10=0;

    for(int i=0; i<count; i++){
         array[i].avg =  (array[i].g1 + array[i].g2 +
                          array[i].g3 + array[i].g4 +
                          array[i].g5 + array[i].g6)/6;

        if(array[i].avg>=10){
            over10[count10] = array[i];
            if(array[i].gender == 'A' ){
              (*countA)++;
            }
            if(array[i].gender == 'G'){
              (*countG)++;
            }
            count10++;
        }
    }

    return count10;
}

void writeToFile(int countA, int countG, StudentsT over10[],int count10){
    FILE *outfile;
    outfile = fopen("results_1.dat","w");

    fprintf(outfile,"% -12s %-8s %-12s %-8s\n","EPITIXOUSES","POSOSTO","EPITXONTES","POSOSTO");
    fprintf(outfile,"% -12d %-8.1f %-12d %-8.1f\n",
            countA,(countA/(double)countA)*100,
            countG,(countG/(double)countG)*100);

     for(int i=0; i<80; i++){fprintf(outfile,"-");}
     fprintf(outfile,"\n");

    for(int i=0; i<count10; i++){
        fprintf(outfile,"%-15s %-25s %4.1f %4.1f %4.1f %4.1f %4.1f %4.1f %4.1f %+5c\n",
                over10[i].firstName,over10[i].lastName,
                over10[i].g1,over10[i].g2,over10[i].g3,
                over10[i].g4,over10[i].g5,over10[i].g6,
                over10[i].avg,over10[i].gender);
        }

}


int main(){

    StudentsT array[size],over10[size];
    int countA,countG;
    int count = readInput(array);
    int count10 = calculations(array,count,&countA,&countG,over10);
    writeToFile(countA,countG,over10,count10);

    return 0;
}
