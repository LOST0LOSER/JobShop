#include<stdio.h>//���Դ 2017211390 
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
	minChromosome.time=9999;//��ʼʱ�� 
	memset(tempChromosome2.message,-1,sizeof(tempChromosome2.message));
	memset(minChromosome.message,-1,sizeof(minChromosome.message));
	translate(machineamount,tempChromosome);
	do{// �����˻����޿��� 
		tmptime=(*tempChromosome).time;
		anneal(tempChromosome,&tempChromosome2);//�˻�õ�������ͬ���������� 
		if(tempChromosome2.time<minChromosome.time)
		{
			minChromosome.time=tempChromosome2.time;
			k=0;
			while(tempChromosome2.message[k]!=-1){
				minChromosome.message[k]=tempChromosome2.message[k];
				k++;
			}//���Ƶ�min�� 
			minChromosome.message[k+1]=-1;
		}
	}while(tmptime!=tempChromosome2.time);
	while(minChromosome.message[k]!=-1){
		(*tempChromosome).message[k]=minChromosome.message[k];
		k++;
	}
} 
