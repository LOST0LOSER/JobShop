#include<stdio.h> //��ҫ�� 2017211378 
#include<stdlib.h>
#include<time.h>
#include"jobshop.h"
extern int itemamount;
extern int machineamount;
extern double start;
extern double finish;
extern void output1(struct chromosome *minChromosome)
{
    FILE *fptr;
    if((fptr=fopen("jobshop_output1.txt","a"))==NULL)//׷�Ӹ������� 
    {
        printf("can't not write into the file");
    }
    else
    {
        translate(machineamount,minChromosome);
        int i=0;
        int j;
        while(workMachine[i][0].number!=-1)
        {
            fprintf(fptr,"M%d ",i);
            j=0;
            {
                while(workMachine[i][j].item!=-1){
                    fprintf(fptr,"(%d",workMachine[i][j].begintime);
                    if(workMachine[i][j].item!=-2){ 
                    fprintf(fptr,",%d",workMachine[i][j].item);
                    fprintf(fptr,"-%d",workMachine[i][j].process);
                    } 
                    else
                    fprintf(fptr,",����");
                    fprintf(fptr,",%d)",workMachine[i][j].endtime);
                    j++;
                }
            }
            fprintf(fptr,"\n");
            i++;
        }
        i=0;
        fprintf(fptr,"Time Used:%.3lfs\n",(finish-start)/CLOCKS_PER_SEC);
        fprintf(fptr,"End time:%d\n",(*minChromosome).time);
    }
    fclose(fptr);
	return;
}
