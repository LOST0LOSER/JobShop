#include<stdio.h>//刘昊源 2017211390 
#include<string.h>
#include<stdlib.h>
#include"jobshop.h"
extern int machineamount;
void superAnneal(struct chromosome *tempChromosome)
{
	int tmptime;
	int k;
	struct chromosome tempChromosome2;
	struct chromosome minChromosome;
	minChromosome.time=9999;//初始时间 
	memset(tempChromosome2.message,-1,sizeof(tempChromosome2.message));
	memset(minChromosome.message,-1,sizeof(minChromosome.message));
	translate(machineamount,tempChromosome);
	do{// 反复退火到退无可退 
		tmptime=(*tempChromosome).time;
		anneal(tempChromosome,&tempChromosome2);//退火得到两个相同的最优序列 
		if(tempChromosome2.time<minChromosome.time)
		{
			minChromosome.time=tempChromosome2.time;
			k=0;
			while(tempChromosome2.message[k]!=-1){
				minChromosome.message[k]=tempChromosome2.message[k];
				k++;
			}//复制到min中 
			minChromosome.message[k+1]=-1;
		}
	}while(tmptime!=tempChromosome2.time);
	while(minChromosome.message[k]!=-1){
		(*tempChromosome).message[k]=minChromosome.message[k];
		k++;
	}
} 
