#include<stdio.h>//刘昊源 2017211390 
#include<string.h>
#include"jobshop.h"
void translate(int,struct chromosome*);
extern int machineamount;
extern void anneal(struct chromosome *tempChromosome,struct chromosome *minChromosome)
{
	int i,j,k;
	int tmp;
	int change=0;
	i=0;
	j=0;
	k=0;
	memset((*minChromosome).message,-1,sizeof((*minChromosome).message));//清空 
	while((*tempChromosome).message[k]!=-1){
		(*minChromosome).message[k]=(*tempChromosome).message[k];
		k++;
	}//初始化，min和temp相同 
	translate(machineamount,tempChromosome);//翻译 
	(*minChromosome).time=(*tempChromosome).time;
	i=0;
	while((*tempChromosome).message[i+1]!=-1){  //每个数字和它后面所有数字交换，如果时间变短则保留 
		j=i;
		while((*tempChromosome).message[j]!=-1){
			if((*tempChromosome).message[i]!=(*tempChromosome).message[j]){//不相同的情况下交换temp 
				change=(*tempChromosome).message[i];
				(*tempChromosome).message[i]=(*tempChromosome).message[j];
				(*tempChromosome).message[j]=change;
				translate(machineamount,tempChromosome);//算出时间 
				if((*minChromosome).time>=(*tempChromosome).time){//时间变短了，就交换min 
					change=(*minChromosome).message[i];
					(*minChromosome).message[i]=(*minChromosome).message[j];
					(*minChromosome).message[j]=change;
					(*minChromosome).time=(*tempChromosome).time;
				}
				else{//否则，既不交换min，还把之前在temp中交换的交换回来（劣势交换不保留） 
					change=(*tempChromosome).message[i];
					(*tempChromosome).message[i]=(*tempChromosome).message[j];
					(*tempChromosome).message[j]=change;
				}
			}
			j++;
		}
		i++;
	}
	return;
}
